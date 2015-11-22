#pragma once
#include <cstddef>
#include "util_constexpr.h"
#include "DxGraphicHandle.h"
#include "DxSoundHandle.h"
#include <unordered_map>
#include <string>
#include <stdexcept>
CONSTEXPR_OR_STATICCONST size_t WINDOW_WIDTH = 800;
CONSTEXPR_OR_STATICCONST size_t WINDOW_HEIGHT = 600;
CONSTEXPR_OR_STATICCONST int FIRST_CHARA_X = WINDOW_WIDTH / 2;

//状態管理
enum class Status{
	TITLE,
	GAME,
	END,
	FLYING_MARE_ANIMATION,
	CAR_ANIMATION,
	HELICOPTER_ANIMATION,
	GAME_OVER,
	RESULT_ECHO,
	CONTINUE,
	EXIT
};
using img_arr_t   = std::unordered_map<std::string, DxGHandle>;
using sound_arr_t = std::unordered_map<std::string, DxSHandle>;

class normal_exit : public std::runtime_error {
public:
	normal_exit() : std::runtime_error("normal_exit"){}
	explicit normal_exit(const std::string& what_arg) : std::runtime_error("normal_exit : " + what_arg) {}
	explicit normal_exit(const char* what_arg) : std::runtime_error(std::string("normal_exit : ") + what_arg) {}
};

