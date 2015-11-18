#include "game.h"
#include "Dxkeystate.h"
#include "DxLib.h"
#include "define.h"
#include "power_bar.h"

bool game_c::normal_con_f() const NOEXCEPT { return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); }

void game_c::move_x() NOEXCEPT{
	static CONSTEXPR_OR_CONST int CHARACTER_MOVE_SPEED = 4;
	this->m_state_.update();
	if (m_state_.left()) this->m_p_.x -= CHARACTER_MOVE_SPEED;
	if (m_state_.right()) this->m_p_.x += CHARACTER_MOVE_SPEED;
}

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status game_c::game_main(){
	m_state_.flush();
	this->m_sound_["flower garden"].play(DxSoundMode::LOOP);
	bool is_normal_state  =true;
	while ((is_normal_state = normal_con_f()) && m_state_.update() && !m_state_[KEY_INPUT_Z] && !m_state_.esc()) {
		this->move_x();
		this->m_img_["gake"].DrawGraph(0, 0, false);
		this->m_img_["bouninngennB"].DrawGraph(this->m_p_, true);
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (m_state_.esc()) throw normal_exit();
	return Status::END;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif

game_c::game_c(const dxle::pointi & p) : m_first_(p), m_p_(p), m_state_(){
	this->m_img_ = make_image_array();
	this->m_status_img_ = make_status_image_array();
	this->m_sound_ = make_sound_array();
}

game_c::~game_c(){
	for (auto& s : this->m_sound_) s.second.stop();
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
