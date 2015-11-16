#include "game.h"
#include "Dxkeystate.h"
#include "DxLib.h"
#include "define.h"
#include "power_bar.h"

int move_x(int current_x, keystate& state){
	CONSTEXPR_OR_CONST int CHARACTER_MOVE_SPEED = 4;
	int re = current_x;
	state.update();
	if (state.left() ) re -= CHARACTER_MOVE_SPEED;
	if (state.right()) re += CHARACTER_MOVE_SPEED;
	return re;
}

Status game_c::game_main(){
	ClearDrawScreen();
	this->m_img_["game"].DrawGraph(0, 0, false);
	ScreenFlip();
	keystate state;
	int x = FIRST_CHARA_X;
	while (-1 != ProcessMessage()) {
		x = move_x(x, state);
		this->m_img_["game"].DrawGraph(x, 0, false);
		ScreenFlip();
		ClearDrawScreen();
	}

	while (CheckHitKey(KEY_INPUT_D) != 1 && -1 != ProcessMessage());
	return Status::END;
}

game_c::game_c(const dxle::pointi & p) : m_first_(p), m_p_(p){
	this->m_img_ = make_image_array();
	this->m_status_img_ = make_status_image_array();
	this->m_sound_ = make_sound_array();
}

const sound_arr_t & game_c::get_sound() const NOEXCEPT {
	return this->m_sound_;
}

const img_arr_t & game_c::get_status_img() const NOEXCEPT {
	return this->m_status_img_;
}

const img_arr_t & game_c::get_img() const NOEXCEPT {
	return this->m_img_;
}
