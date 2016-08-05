#pragma once
#include <cstddef>
#include "dxlibex/config/defines.h"
#include "DxGraphicHandle.h"
#include "DxSoundHandle.h"
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <dxlibex/basic_types.hpp>

DXLE_STATIC_CONSTEXPR dxle::sizei WINDOW = { 800, 600 };
DXLE_STATIC_CONSTEXPR int FIRST_CHARA_X = WINDOW.width / 2;
DXLE_STATIC_CONSTEXPR int GROUND_LEFT_X = WINDOW.width / 4;
DXLE_STATIC_CONSTEXPR dxle::pointi POWER_BAR_BG_POS = { WINDOW.width / 2, WINDOW.height * 5 / 6 };
DXLE_STATIC_CONSTEXPR dxle::sizei POWER_BAR_BG_SIZE = { WINDOW.width * 7 / 16, WINDOW.height * 7 / 60 };
DXLE_STATIC_CONSTEXPR dxle::pointi POWER_BAR_POS = { WINDOW.width * 9 / 16, WINDOW.height * 11 / 12 };
DXLE_STATIC_CONSTEXPR dxle::sizei POWER_BAR_SIZE = { WINDOW.width * 11 / 32, WINDOW.height * 2 / 75 };
DXLE_STATIC_CONSTEXPR std::size_t POS_REC_NUM = 1024;
DXLE_STATIC_CONSTEXPR dxle::pointi SCORE_SHOW_IMAGE_POS = static_cast<dxle::pointi>(WINDOW / 4);
DXLE_STATIC_CONSTEXPR double transition_rate_to_helicopter_animation = 0.1;

//状態管理
enum class main_status{
	title,
	game_preprocess,
	game_main,
	end,
	flying_mare_animation,
	car_animation,
	helicopter_animation,
	gameover,
	result_echo,
	game_continue,
	exit
};
using img_arr_t   = std::unordered_map<dxle::tstring, DxGHandle>;
using sound_arr_t = std::unordered_map<dxle::tstring, DxSHandle>;

class normal_exit : public std::runtime_error {
public:
	normal_exit() : std::runtime_error("normal_exit"){}
	explicit normal_exit(const std::string& what_arg) : std::runtime_error("normal_exit : " + what_arg) {}
	explicit normal_exit(const char* what_arg) : std::runtime_error(std::string("normal_exit : ") + what_arg) {}
};

