#if defined(_WIN32) || defined(_WIN64)
#if defined(_MSC_VER) && _MSC_VER >= 1400 && (!defined(DISABE_CRT_RAND_S))//Visual Studio 2005よりrand_sは実装された
#define _CRT_RAND_S//you must define before includeing stdlib.h
#include <stdlib.h> //rand_s, malloc
#endif //_MSC_VER >= 1400
#define MY_ARC_FOR_WINDWOS 1
#include <Windows.h>
#endif // defined(_WIN32) || defined(_WIN64)
#include "game_preprocess.h"
#include <random>
#include <cstdint>//uint_least32_t
#include <type_traits>
#include <memory>
#include <algorithm>//std::generate
#include <ctime>//clock(), time()
#include <functional>//std::ref in gcc
#include <vector>
#if !defined(__clang__) || !defined(_MSC_VER)//Clang with Microsoft CodeGenではなぜか__cpuidがつかえない
#ifndef __INTEL_COMPILER
#include <intrin.h>
#include <immintrin.h>
#endif
DXLE_STATIC_CONSTEXPR uint32_t RDRAND_MASK = 0x40000000;
typedef struct { uint32_t EAX, EBX, ECX, EDX; } regs_t;
regs_t get_cpuid(unsigned int level) {
	regs_t re = { 0 };
	static_assert(sizeof(re) == (sizeof(uint32_t) * 4), "illegal size of struct regs_t ");
#if ( defined(__INTEL_COMPILER) || defined(_MSC_VER) )
	__cpuid(reinterpret_cast<int*>(&re), static_cast<int>(level));
#elif defined(__GNUC__)
	__get_cpuid(level, &re.EAX, &re.EBX, &re.ECX, &re.EDX);//error: '__get_cpuid' was not declared in this scope
#endif
	return re;
}
bool IsIntelCPU() {
	const auto id = get_cpuid(0);
	uint32_t vender[4] = { id.EAX, id.ECX, id.EBX , 0 };
	return (0 == strcmp(reinterpret_cast<char*>(vender), "GenuineIntel"));
}
bool IsRDRANDsupport() {
	if (!IsIntelCPU()) return false;
	const auto reg = get_cpuid(1);
	return (RDRAND_MASK == (reg.ECX & RDRAND_MASK));
}
#endif// !defined(__clang__) || !defined(_MSC_VER)
using seed_v_t = std::vector<std::uint_least32_t>;
seed_v_t create_seed() {
	std::random_device rnd;// ランダムデバイス
	seed_v_t sed_v(10);// 初期化用ベクター
	std::generate(sed_v.begin(), sed_v.end(), std::ref(rnd));// ベクタの初期化
#if !defined(__clang__) || !defined(_MSC_VER)//Clang with Microsoft CodeGenではなぜか__cpuidがつかえない
	if (IsRDRANDsupport()) {//RDRAND命令の結果もベクターに追加
		for (std::size_t i = 0; i < 4; i++) {
			unsigned int rdrand_value = 0;
#ifndef __GNUC__
			_rdrand32_step(&rdrand_value);
#else
			__builtin_ia32_rdrand32_step(&rdrand_value);
#endif
			if (0 != rdrand_value) {
				sed_v.push_back(rdrand_value & i);
			}
		}
	}
#endif//!defined(__clang__) || !defined(_MSC_VER)
#ifdef _CRT_RAND_S
	unsigned int rand_s_value = 0;
	rand_s(&rand_s_value);
	if (0 != rand_s_value) {
		sed_v.push_back(rand_s_value);
	}
#endif //_CRT_RAND_S
#ifdef MY_ARC_FOR_WINDWOS
	POINT point;
	GetCursorPos(&point);
	sed_v.push_back(point.x);
	sed_v.push_back(point.y);
#endif //MY_ARC_FOR_WINDWOS
	sed_v.push_back(static_cast<std::uint_least32_t>(clock()));//clock関数の結果もベクターに追加
	sed_v.push_back(static_cast<std::uint_least32_t>(time(nullptr)));//time関数の結果もベクターに追加
	char* heap = static_cast<char*>(malloc(sizeof(char) * 2));
	sed_v.push_back(static_cast<std::uint_least32_t>(reinterpret_cast<std::uint_least64_t>(heap)));//ヒープ領域のアドレスもベクターに追加
	free(heap);
	return sed_v;
}
std::mt19937 create_engine() {
	auto sed_v = create_seed();
	std::seed_seq seq(sed_v.begin(), sed_v.end());
	return std::mt19937(seq);
}

Status game_preprocess()
{
	auto engine = create_engine();
	std::bernoulli_distribution dist(transition_rate_to_helicopter_animation);
	return (dist(engine))? Status::HELICOPTER_ANIMATION : Status::GAME;
}
