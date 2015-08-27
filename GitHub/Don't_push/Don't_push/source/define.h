#pragma once
#include <cstddef>
#include "util_constexpr.h"
#include "DxGraphicHandle.h"
#include "DxSoundHandle.h"
#include <unordered_map>
#include <string>
CONSTEXPR_OR_STATICCONST size_t WINDOW_WIDTH = 640;
CONSTEXPR_OR_STATICCONST size_t WINDOW_HEIGHT = 480;
CONSTEXPR_OR_STATICCONST int FIRST_CHARA_X = WINDOW_WIDTH / 2;

//状態管理
enum class Status{
	TITLE,
	GAME,
	END,
	FLYING_MARE_ANIMATION,
	CAR_ANIMATION,
	HELICOPTER_ANIMATION,
	CONTINUE,
	EXIT
};
using img_arr_t = std::unordered_map < std::string, DxGHandle >;
using sound_arr_t = std::unordered_map<std::string, DxSHandle>;
