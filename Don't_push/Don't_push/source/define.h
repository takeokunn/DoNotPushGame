#pragma once
#include <cstddef>
#include "util_constexpr.h"
#include "DxGraphicHandle.h"
#include "DxSoundHandle.h"
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <dxlibex/basic_types.hpp>

DXLE_STATIC_CONSTEXPR size_t WINDOW_WIDTH = 800;
DXLE_STATIC_CONSTEXPR size_t WINDOW_HEIGHT = 600;
DXLE_STATIC_CONSTEXPR int FIRST_CHARA_X = WINDOW_WIDTH / 2;
DXLE_STATIC_CONSTEXPR int GROUND_LEFT_X = WINDOW_WIDTH / 4;
DXLE_STATIC_CONSTEXPR dxle::pointi POWER_BAR_BG_POS = { WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5 / 6 };
DXLE_STATIC_CONSTEXPR dxle::sizei POWER_BAR_BG_SIZE = { WINDOW_WIDTH * 7 / 16, WINDOW_HEIGHT * 7 / 60 };

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

