#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "game.h"
#include "Dxkeystate.h"
#include "load.h"
#include "DxLib.h"
#include "define.h"
#include "power_bar.h"
#include "circular_motion.h"
#include <cmath>
#include <array>
#include <algorithm>
#include <deque>


struct game_c::Impl {
	Impl(const dxle::pointi& bouninngennA_p, const dxle::pointi& bouninngennB_p)
		: m_window_s(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), m_state(), m_back_img(dxle::Graph2D::MakeScreen(m_window_s.x, m_window_s.y)),
		m_img(make_image_array()), m_sound(make_sound_array()), score(),
		m_bouninngenn{ {
			{ bouninngennA_p, &m_img["bouninngennA"], &m_img["bouninngennA_fall"]},//棒人形A
			{ bouninngennB_p, &m_img["bouninngennB"], &m_img["bouninngennB_fall"]} //棒人形B
		} }
	{
		this->m_back_img.DrawnOn([this]() {m_img["gake"].DrawExtendGraph({}, m_window_s, false); });
	}
	void state_init() NOEXCEPT;
	bool normal_con_f() const NOEXCEPT;
	void move_x(int limit_l_x, int limit_r_x) NOEXCEPT;
	void fadeout_prelude_masseage();
	void fall_bouninngenn(size_t bouninngenn_no, const std::deque<dxle::pointi>& pos_record);
	const dxle::pointi m_window_s;
	keystate m_state;
	dxle::Graph2D::screen m_back_img;
	img_arr_t m_img;
	sound_arr_t m_sound;
	uint8_t score;//0-100
	std::array<obj_info, 2>m_bouninngenn;
};
game_c::game_c(const dxle::pointi& bouninngennA_p, const dxle::pointi& bouninngennB_p) : pimpl(new game_c::Impl(bouninngennA_p, bouninngennB_p)){}

game_c::~game_c() {
	for (auto& s : this->pimpl->m_sound) s.second.stop();
}

const sound_arr_t & game_c::get_sound() const NOEXCEPT {
	return this->pimpl->m_sound;
}

const img_arr_t & game_c::get_img() const NOEXCEPT {
	return this->pimpl->m_img;
}

bool game_c::Impl::normal_con_f() const NOEXCEPT { return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); }

void game_c::Impl::move_x(int limit_l_x, int limit_r_x) NOEXCEPT{
	if (limit_r_x < limit_l_x) std::swap(limit_l_x, limit_r_x);
	static CONSTEXPR_OR_CONST int CHARACTER_MOVE_SPEED = 4;
	this->m_state.update();
	if (this->m_state.left()) this->m_bouninngenn[1].get_pos().x -= CHARACTER_MOVE_SPEED;
	if (this->m_state.right()) this->m_bouninngenn[1].get_pos().x += CHARACTER_MOVE_SPEED;
	this->m_bouninngenn[1].get_pos().x = std::min(limit_r_x, std::max(this->m_bouninngenn[1].get_pos().x, limit_l_x));
}

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
void game_c::Impl::state_init() NOEXCEPT {
	this->m_state.fllush();
	for (auto& i : this->m_bouninngenn) i.state_init();
	this->score = 0;
}
void game_c::Impl::fadeout_prelude_masseage() {
	constexpr int fadeout_time_frame = 200;
	bool is_normal_state = true;

	//fade out
	for (int i = 0; i < fadeout_time_frame && (is_normal_state = normal_con_f()) && m_state.update() && !m_state.esc(); ++i) {
		this->m_back_img.DrawGraph({}, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>((fadeout_time_frame - i) * 256.0 / fadeout_time_frame));
		this->m_img["back_str"].DrawGraph({}, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		for (auto& im : this->m_bouninngenn) im.draw();
	}
	if (m_state.esc()) throw normal_exit();
}

static int calc_free_fall(int y, size_t t) ATT_PURE {
	constexpr double g = 9.80665;
	constexpr double correction_factor = 10.5;
	return y + static_cast<int>(correction_factor * g / 2 * t);
}
void game_c::Impl::fall_bouninngenn(size_t bouninngenn_no, const std::deque<dxle::pointi>& pos_record) {
	const int v = [&pos_record]() -> int {
		if (pos_record.size() < 2) return 10;
		int64_t sum = 0;
		int t = 0;
		for (auto it = pos_record.begin(); it != pos_record.end() - 1; ++it) {
			const auto tmp = it[1].x - it->x;
			if (0 <= tmp) {
				sum += tmp;
				++t;
			}
		}
		return static_cast<int>(sum / t);
	}();
	bool is_normal_state = true;
	while ((is_normal_state = this->normal_con_f()) && this->m_state.update() && !this->m_state.esc()) {
		this->m_bouninngenn[bouninngenn_no].get_pos().x -= v;
		this->m_back_img.DrawGraph({}, false);
		for (auto& i : this->m_bouninngenn) i.draw();
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (this->m_state.esc()) throw normal_exit();
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif

static double bouninngenn_moving_distance(const std::array<obj_info, 2>& bouninngenn) {
	const auto denominator = std::abs(distance_first(bouninngenn[0], bouninngenn[1]));
	return std::abs(denominator - bouninngenn[1].distance_from_first().x) * 100.0 / denominator;
}
Status game_c::game_main() {
	this->pimpl->state_init();//状態初期化
	this->pimpl->m_sound["flower garden"].play(DxSoundMode::LOOP);
	this->pimpl->fadeout_prelude_masseage();
	power_bar_c power_bar({ WINDOW_WIDTH * 7 / 16, WINDOW_HEIGHT * 11 / 12 }, { WINDOW_WIDTH * 11 / 32, WINDOW_HEIGHT * 2 / 75 }, 10, GetColor(229, 225, 225));
	std::deque<dxle::pointi> pos_record;
	bool is_normal_state = true;
	while ((is_normal_state = this->pimpl->normal_con_f()) && this->pimpl->m_state.update() && !this->pimpl->m_state[KEY_INPUT_Z] && !this->pimpl->m_state.esc()) {
		power_bar.update();
		this->pimpl->move_x(this->pimpl->m_bouninngenn[0].calc_first_bottom_right_pos().x, this->pimpl->m_bouninngenn[1].get_fitst_pos().x);
		if (4 < pos_record.size()) pos_record.pop_front();
		pos_record.push_back(this->pimpl->m_bouninngenn[1].get_pos());
		this->pimpl->m_back_img.DrawGraph({}, false);
		for (auto& i : this->pimpl->m_bouninngenn) i.draw();
		const dxle::pointi gauge_bg_p = { WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5 / 6 };
		this->pimpl->m_img["game_main_gauge_bg"].DrawExtendGraph(gauge_bg_p, gauge_bg_p + dxle::pointi{ WINDOW_WIDTH * 7 / 16, WINDOW_HEIGHT * 7 / 60 }, false);
		power_bar.draw();
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (this->pimpl->m_state.esc()) throw normal_exit();

	const int d = distance(this->pimpl->m_bouninngenn[0], this->pimpl->m_bouninngenn[1]);
	const auto rate = bouninngenn_moving_distance(this->pimpl->m_bouninngenn);
	const auto p_rate = power_bar.get_percent();
	bool is_game_over = false;
	if (d < 0 || rate < 80.0 || p_rate < 60.0) {
		this->pimpl->fall_bouninngenn(1, pos_record);//落とそうとして落とされる、ゲームオーバー
		is_game_over = true;
	}
	else {
		this->pimpl->score = static_cast<uint8_t>((p_rate + rate) / 2);//0-100
		if (this->pimpl->score < 40) {
			this->pimpl->fall_bouninngenn(1, pos_record);//落とそうとして落とされる、ゲームオーバー
			is_game_over = true;
		}
		else {
			this->pimpl->fall_bouninngenn(0, pos_record);//落とす。成功！
		}
	}
	return (is_game_over) ? Status::GAME_OVER : Status::RESULT_ECHO;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif

static void extruder(obj_info& move_target, const obj_info& move_cause) {
	if (move_target.get_pos().x + move_target.get_img().GetGraphSize().width < WINDOW_WIDTH / 4) {
		++move_target.m_fall_frame;
		move_target.get_pos().y = calc_free_fall(move_cause.get_fitst_pos().y, move_target.m_fall_frame);
		if (1 == move_target.m_fall_frame) {
			move_target.change_img();
		}
	}
	if (distance(move_target, move_cause) < 0) {
		move_target.get_pos().x = move_cause.get_pos().x - move_target.get_img().GetGraphSize().width;
	}
}
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status game_c::helicopter_event() {
	this->pimpl->state_init();//状態初期化
	this->pimpl->m_sound["flower garden"].play(DxSoundMode::LOOP);
	this->pimpl->fadeout_prelude_masseage();
	circular_motion helicopter(
		{ pimpl->m_window_s.x / 2, -100 }, { pimpl->m_window_s.x * 23 / 26, pimpl->m_window_s.y * 1 / 82 },
		1.0 / 30.0, this->pimpl->m_img["herikoputa-"], this->pimpl->m_img["herikoputa-"]
	);
	bool is_normal_state = true;
	while ((is_normal_state = this->pimpl->normal_con_f()) && pimpl->m_state.update() && !pimpl->m_state[KEY_INPUT_Z] && !pimpl->m_state.esc() && helicopter.update()) {
		this->pimpl->m_back_img.DrawGraph({}, false);
		extruder(this->pimpl->m_bouninngenn[1], helicopter.get_obj());
		extruder(this->pimpl->m_bouninngenn[0], this->pimpl->m_bouninngenn[1]);
		for (auto& i : this->pimpl->m_bouninngenn) i.draw();
		helicopter.draw();
		//WaitKey();
		if (std::all_of(this->pimpl->m_bouninngenn.begin(), this->pimpl->m_bouninngenn.end(), [](const obj_info& a) -> bool { return a.is_fallen(); }))break;//ふたりとも落ちたらゲーム終わり
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (pimpl->m_state.esc()) throw normal_exit();
	return Status::CONTINUE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
