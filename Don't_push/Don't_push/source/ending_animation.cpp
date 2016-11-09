#include "ending_animation.h"
#include "define.h"
#include <dxlibex/graph2d.hpp>
#include <chrono>
#include <thread>
#include <future>

//#include <fstream>
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif

void ending(const sound_arr_t& sound)
{
	for (auto& s : sound) s.second.stop();//BGM全部停止
	std::thread sound_th([&sound]() {
		using namespace std::chrono_literals;
		sound.at(_T("Thank_you_for_playing_en")).play(DxSoundMode::NORMAL);
		std::this_thread::sleep_for(2ms);
		sound.at(_T("Thank_you_for_playing_ja")).play(DxSoundMode::NORMAL);
	});
	DXLE_STATIC_CONSTEXPR int test_height = 20;
	static const TCHAR* plain_text = _T("Thank you for playing");
	static const int font = CreateFontToHandle(nullptr, test_height, 1, DX_FONTTYPE_ANTIALIASING);//「Xキーを押してね」の奴
	auto text = dxle::MakeScreen(GetDrawStringWidthToHandle(plain_text, static_cast<int>(dxle::tstrlen(plain_text)), font), test_height);
	text.draw_on_this([]() {
		DxLib::DrawStringToHandle(0, 0, plain_text, DxLib::GetColor(255, 255, 255), font);
	});
	auto normal_con_f = []() -> bool {
		bool re = -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen();
		if (!re) throw std::runtime_error("ProcessMessage() return -1.");
		return re;
	};
	bool is_normal_state;
	DXLE_STATIC_CONSTEXPR int v = WINDOW.width / 170;
	//std::ofstream log("log.txt");
	//log << "text.size():" << text.size() << " v:" << v << std::endl;
	for (int text_pos = WINDOW.width; 
		(is_normal_state = normal_con_f()) && 0 <= text_pos + text.size().width + v + 1;
		text_pos -= v
	) {
		DxLib::DrawBox(0, 0, WINDOW.width, WINDOW.height, DxLib::GetColor(0, 0, 0), true);
		text.DrawGraph(text_pos, WINDOW.height / 3, true);
		//log << "text_pos:" << text_pos << " text_pos + text.size().width:" << text_pos + text.size().width << std::endl;
	}
	sound_th.join();
	for (auto& s : sound) s.second.stop();//BGM全部停止
	if(!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
