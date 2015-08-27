#pragma once
#include "load.h"
#include "util_constexpr.h"
CONSTEXPR_OR_STATICCONST size_t WINDOW_WIDTH = 640;
CONSTEXPR_OR_STATICCONST size_t WINDOW_HEIGHT = 480;
CONSTEXPR_OR_STATICCONST int FIRST_CHARA_X = WINDOW_WIDTH / 2;

//状態管理
enum class Status{
	TITLE,
	GAME,
	END,
	EXIT
};
using img_arr_t = std::unordered_map < std::string, DxGHandle >;
