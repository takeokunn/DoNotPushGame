#include "game.h"
#include "Dxkeystate.h"
#include "DxLib.h"
#include "define.h"
#include "power_bar.h"
#include <cmath>

game_c::game_c(const dxle::pointi & p) : m_first_(p), m_window_s_(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)),
m_p_(p), m_state_(), m_back_img_(dxle::Graph2D::MakeScreen(m_window_s_.x, m_window_s_.y))
{
	this->m_img_ = make_image_array();
	this->m_status_img_ = make_status_image_array();
	this->m_sound_ = make_sound_array();
	this->m_back_img_.DrawnOn([this]() {m_img_["gake"].DrawExtendGraph({}, m_window_s_, false); });
	this->m_bouninngennA_ = dxle::Graph2D::MakeScreen(this->m_img_["bouninngennA"].GetGraphSize().x / 3, this->m_img_["bouninngennA"].GetGraphSize().y / 3, true);
	this->m_bouninngennB_ = dxle::Graph2D::MakeScreen(this->m_img_["bouninngennB"].GetGraphSize().x / 3, this->m_img_["bouninngennB"].GetGraphSize().y / 3, true);
	this->m_bouninngennA_.DrawnOn([this]() {this->m_img_["bouninngennA"].DrawExtendGraph({}, { this->m_img_["bouninngennA"].GetGraphSize().x / 3, this->m_img_["bouninngennA"].GetGraphSize().y / 3 }, true); });
	this->m_bouninngennB_.DrawnOn([this]() {this->m_img_["bouninngennB"].DrawExtendGraph({}, { this->m_img_["bouninngennB"].GetGraphSize().x / 3, this->m_img_["bouninngennB"].GetGraphSize().y / 3 }, true); });
}

game_c::~game_c() {
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
Status game_c::game_main() {
	this->m_state_.fllush();
	this->m_sound_["flower garden"].play(DxSoundMode::LOOP);
	bool is_normal_state  =true;
	while ((is_normal_state = normal_con_f()) && m_state_.update() && !m_state_[KEY_INPUT_Z] && !m_state_.esc()) {
		this->move_x();
		this->m_back_img_.DrawGraph({}, false);
		this->m_img_["bouninngennB"].DrawGraph(this->m_p_, true);
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (m_state_.esc()) throw normal_exit();
	return Status::CONTINUE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
class circular_motion
{
public:
	circular_motion() = delete;
	circular_motion(const dxle::pointi& center_pos, const dxle::pointi& first_pos, double angular_v) NOEXCEPT;
	circular_motion(const circular_motion&) = delete;
	circular_motion(circular_motion&&) = delete;
	circular_motion& operator=(const circular_motion&) = delete;
	circular_motion& operator=(circular_motion&&) = delete;
	bool update() NOEXCEPT;
	bool draw(const dxle::Graph2D::Texture2D& img) const;
	dxle::pointd get_pos() const NOEXCEPT;
private:
	const dxle::pointi m_center_;
	const double m_r_;
	const double m_first_rad_;
	double m_angular_v_;// rad./sec. Dextrorotation(右回り。yは下向き正)
	dxle::pointd m_current_;
	size_t m_t_;
};

circular_motion::circular_motion(const dxle::pointi & center_pos, const dxle::pointi& first_pos, double angular_v) NOEXCEPT
	: m_center_(center_pos), m_r_(std::hypot(first_pos.x - m_center_.x, first_pos.y - m_center_.y)), 
	m_first_rad_(std::acos((first_pos.x - m_center_.x) / m_r_) * (((first_pos.y - m_center_.y) < 0) ? -1 : 1)),
	m_angular_v_(angular_v), m_current_(static_cast<dxle::pointd>(first_pos)), m_t_()
{}

bool circular_motion::update() NOEXCEPT {
	++this->m_t_;
	this->m_current_ = dxle::pointd(m_center_.x + this->m_r_ * std::cos(m_first_rad_ + this->m_t_ * this->m_angular_v_), m_center_.y + this->m_r_ * std::sin(m_first_rad_ + this->m_t_ * this->m_angular_v_));
	return true;
}

bool circular_motion::draw(const dxle::Graph2D::Texture2D& img) const {
	img.DrawGraph(static_cast<dxle::pointi>(this->m_current_), true);
	return true;
}

dxle::pointd circular_motion::get_pos() const NOEXCEPT {
	return this->m_current_;
}
static void extruded(size_t& fall_frame, dxle::pointi& move_target, const dxle::pointi& move_cause, const dxle::pointi& target_img_size, const int first_y) {
	constexpr double g = 9.80665;
	if (move_target.x + target_img_size.x < WINDOW_WIDTH / 4) {
		++fall_frame;
		move_target.y = first_y + static_cast<int>(g / 2 * fall_frame);
	}
	if (move_cause.x < move_target.x + target_img_size.x) move_target.x = move_cause.x - target_img_size.x;
}
Status game_c::helicopter_event() {
	this->m_state_.fllush();
	this->m_sound_["flower garden"].play(DxSoundMode::LOOP);
	bool is_normal_state = true;
	dxle::pointi ningenA = { WINDOW_WIDTH * 57 / 256 , WINDOW_HEIGHT * 2 / 7 };
	constexpr int fadeout_time_frame = 200;
	//fade out
	for (int i = 0; i < fadeout_time_frame && (is_normal_state = normal_con_f()) && m_state_.update() && !m_state_.esc(); ++i) {
		//this->m_img_["Presentation1"].DrawGraph({}, false);
		this->m_back_img_.DrawGraph({}, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>((fadeout_time_frame - i) * 256.0/ fadeout_time_frame));
		this->m_img_["back_str"].DrawGraph({}, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		this->m_bouninngennA_.DrawGraph(ningenA, true);
		this->m_bouninngennB_.DrawGraph(this->m_p_, true);
	}
	if (m_state_.esc()) throw normal_exit();

	circular_motion helicopter({ m_window_s_.x / 2, -100 }, { m_window_s_.x * 23 / 26, m_window_s_.y * 1 / 82 }, 1.0 / 30.0);
	auto helicopter_img = dxle::Graph2D::MakeScreen(this->m_img_["herikoputa-"].GetGraphSize().x / 3, this->m_img_["herikoputa-"].GetGraphSize().x / 3, true);
	helicopter_img.DrawnOn([this]() {this->m_img_["herikoputa-"].DrawExtendGraph({}, { this->m_img_["herikoputa-"].GetGraphSize().x * 1 / 3, this->m_img_["herikoputa-"].GetGraphSize().y * 1 / 3 }, true); });
	size_t fall_frameA = 0;
	size_t fall_frameB = 0;
	const int first_yA = ningenA.y;
	const int first_yB = m_p_.y;
	while ((is_normal_state = normal_con_f()) && m_state_.update() && !m_state_[KEY_INPUT_Z] && !m_state_.esc() && helicopter.update()) {
		this->m_back_img_.DrawGraph({}, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		this->m_img_["Presentation1"].DrawGraph({}, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		extruded(fall_frameB, m_p_, static_cast<dxle::pointi>(helicopter.get_pos()), this->m_bouninngennB_.GetGraphSize(), first_yB);
		extruded(fall_frameA, ningenA, m_p_, this->m_bouninngennA_.GetGraphSize(), first_yA);
		this->m_bouninngennA_.DrawGraph(ningenA, true);
		this->m_bouninngennB_.DrawGraph(this->m_p_, true);
		//helicopter_img.DrawGraph({ m_window_s_.x * 23 / 26, m_window_s_.y * 1 / 82}, true);
		helicopter.draw(helicopter_img);
		WaitKey();
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (m_state_.esc()) throw normal_exit();
	return Status::CONTINUE;
}
