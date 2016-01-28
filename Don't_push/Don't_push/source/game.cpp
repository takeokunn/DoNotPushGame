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
#include <algorithm>
#include <deque>
#include <tuple>
#include <boost/optional.hpp>
struct game_c::Impl {
	Impl(const dxle::pointi& bouninngennA_p, const dxle::pointi& bouninngennB_p)
		: m_window_s(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), m_state(), m_back_img(dxle::graph2d::MakeScreen(m_window_s.x, m_window_s.y)),
		m_img(make_image_array()), m_sound(make_sound_array()), score(), game_end_img(),
		m_bouninngenn_a{ bouninngennA_p, &m_img["bouninngennA"], &m_img["bouninngennA_fall"] },//棒人形A
		m_bouninngenn_b{ bouninngennB_p, &m_img["bouninngennB"], &m_img["bouninngennB_fall"] } //棒人形B
	{
		this->m_back_img.drawn_on([this]() {m_img["gake"].DrawExtendGraph({}, m_window_s, false); });
	}
	Impl(const Impl&) = delete;
	Impl(Impl&&) = delete;
	Impl& operator=(const Impl&) = delete;
	Impl& operator=(Impl&&) = delete;
	bool bouninngen_draw() const NOEXCEPT;
	void state_init() NOEXCEPT;
	bool normal_con_f() const NOEXCEPT;
	int move_x(int limit_l_x, int limit_r_x) NOEXCEPT;
	void fadeout_prelude_masseage();
	template<std::size_t bouninngenn_no> void fall_bouninngenn(const std::deque<dxle::pointi>& pos_record, const power_bar_c& power_bar);
	const dxle::pointi m_window_s;
	keystate m_state;
	dxle::graph2d::screen m_back_img;
	img_arr_t m_img;
	sound_arr_t m_sound;
	std::uint8_t score;//0-100
	boost::optional<dxle::graph2d::screen> game_end_img;
	obj_info m_bouninngenn_a;
	obj_info m_bouninngenn_b;
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

int game_c::Impl::move_x(int limit_l_x, int limit_r_x) NOEXCEPT{
	if (limit_r_x < limit_l_x) std::swap(limit_l_x, limit_r_x);
	DXLE_STATIC_CONSTEXPR int CHARACTER_MOVE_SPEED = 4;
	this->m_state.update();
	auto& b_x_ref = this->m_bouninngenn_b.get_pos().x;
	const volatile auto pre = b_x_ref;
	if (this->m_state.left()) b_x_ref -= CHARACTER_MOVE_SPEED;
	if (this->m_state.right()) b_x_ref += CHARACTER_MOVE_SPEED;
	b_x_ref = std::min(limit_r_x, std::max(b_x_ref, limit_l_x));
	return b_x_ref - pre;
}

bool game_c::Impl::bouninngen_draw() const NOEXCEPT
{
	return m_bouninngenn_a.draw() && m_bouninngenn_b.draw();;
}

void game_c::Impl::state_init() NOEXCEPT {
	this->m_state.fllush();
	this->m_bouninngenn_a.state_init();
	this->m_bouninngenn_b.state_init();
	this->bouninngen_draw();
	this->score = 0;
	this->game_end_img = boost::none_t{};
}
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
void game_c::Impl::fadeout_prelude_masseage() {
	DXLE_STATIC_CONSTEXPR int fadeout_time_frame = 200;
	bool is_normal_state = true;

	//fade out
	for (int i = 0; i < fadeout_time_frame && (is_normal_state = normal_con_f()) && m_state.update() && !m_state.esc(); ++i) {
		this->m_back_img.DrawGraph({}, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>((fadeout_time_frame - i) * 256.0 / fadeout_time_frame));
		this->m_img["back_str"].DrawGraph({}, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		this->bouninngen_draw();
	}
	if (m_state.esc()) throw normal_exit();
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif

namespace detail {
	int	DrawBox_kai_impl(dxle::pointi p, dxle::sizei size, unsigned int border_color, unsigned int border_width) {
		if (1U == border_width) return DxLib::DrawBox(p.x - 1, p.y - 1, p.x + size.width, p.y + size.height, border_color, false);
		else {
			const int b_w = static_cast<int>(border_width);
			const auto f_rshift_roundup = [](unsigned int n) DXLE_NOEXCEPT_OR_NOTHROW -> int{ return static_cast<int>((n >> 1) + (n & 1)); };
			const auto f_rshift = [](unsigned int n) DXLE_NOEXCEPT_OR_NOTHROW -> int{ return static_cast<int>(n >> 1); };
			//第一引数で指定された部分の外に枠線を引く。
			//DxLib::DrawLineの座標指定は太さが例えば7なら4のところ、6なら3のところの座標を指定する
			auto re = DxLib::DrawLine(p.x - b_w, p.y - f_rshift_roundup(border_width), p.x + size.width + b_w, p.y - f_rshift_roundup(border_width), border_color, b_w);//上
			if (-1 == re) return re;
			re = DxLib::DrawLine(p.x + size.width + f_rshift(border_width), p.y - b_w, p.x + size.width + f_rshift(border_width), p.y + size.height + b_w, border_color, b_w);//右
			if (-1 == re) return re;
			re = DxLib::DrawLine(p.x - b_w, p.y + size.height + f_rshift(border_width), p.x + size.width + b_w, p.y + size.height + f_rshift(border_width), border_color, b_w);//下
			if (-1 == re) return re;
			return DxLib::DrawLine(p.x - f_rshift_roundup(border_width), p.y - b_w, p.x - f_rshift_roundup(border_width), p.y + size.height + b_w, border_color, b_w);//左
		}
	}
}
int	DrawBox_kai(dxle::pointi p, dxle::sizei size, unsigned int border_color, unsigned int border_width) {
	if (static_cast<unsigned int>(std::abs(std::min(size.width, size.height))) < border_width) return -1;
	return detail::DrawBox_kai_impl(p, size, border_color, border_width);
}
int	DrawBox_kai(dxle::pointi p, dxle::sizei size, unsigned int border_color, unsigned int border_width, unsigned int back_ground_color) {
	const auto smaller_size = std::min(size.width, size.height);
	if (static_cast<unsigned int>(std::abs(smaller_size)) < border_width) return -1;
	const int b_w = static_cast<int>(border_width);
	if (smaller_size < b_w) return -1;
	else if (smaller_size / 2 < b_w) return DxLib::DrawBox(p.x - b_w, p.y - b_w, p.x + size.width + b_w - 1, p.y + size.height + b_w - 1, back_ground_color, true);
	else {
		if (2048 < size.height * size.width) {
			auto re = DxLib::DrawBox(p.x, p.y, p.x + size.width - 1, p.y + size.height - 1, back_ground_color, true);//back_ground
			if (-1 == re) return re;
			return detail::DrawBox_kai_impl(p, size, border_color, border_width);//border
		}
		else {
			auto re = DxLib::DrawBox(p.x - b_w, p.y - b_w, p.x + size.width + b_w, p.y + size.height + b_w, border_color, true);//border
			if (-1 == re) return re;
			return DxLib::DrawBox(p.x, p.y, p.x + size.width - 1, p.y + size.height - 1, back_ground_color, true);//back_ground
		}
	}
}
static int calc_v_from_pos_rec(const std::deque<dxle::pointi>& pos_record) 
{
	DXLE_STATIC_CONSTEXPR int default_v = 4;
	if (pos_record.size() < 2) return default_v;
	int64_t sum = 0;
	int t = 0;
	for (auto it = pos_record.begin(); it != pos_record.end() - 1; ++it) {
		const auto tmp = it[1].x - it->x;
		if (0 <= tmp) {
			sum += tmp;
			++t;
		}
	}
	return t ? std::max(default_v, static_cast<int>(sum / t)) : default_v;//avoid div-zero exceptions
}
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
template<std::size_t bouninngenn_no> void game_c::Impl::fall_bouninngenn(const std::deque<dxle::pointi>& pos_record, const power_bar_c& power_bar) {
	const int v = calc_v_from_pos_rec(pos_record);
	bool is_normal_state = true;
	auto& bouninngenn = std::get<bouninngenn_no>(std::tie(this->m_bouninngenn_a, this->m_bouninngenn_b));
	while ((is_normal_state = this->normal_con_f()) && this->m_state.update() && !this->m_state.esc()) {
		extruder(bouninngenn, v);
		this->m_back_img.DrawGraph({}, false);
		this->bouninngen_draw();
		DrawBox_kai(POWER_BAR_BG_POS, POWER_BAR_BG_SIZE, DxLib::GetColor(4, 182, 182), 2, DxLib::GetColor(229, 255, 255));
		power_bar.draw();
		//WaitKey();
		if (bouninngenn.is_fallen()) break;
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
Status game_c::game_main() {
	this->pimpl->state_init();//状態初期化
	this->pimpl->m_sound["flower garden"].play(DxSoundMode::LOOP);
	this->pimpl->fadeout_prelude_masseage();
	power_bar_c power_bar({ WINDOW_WIDTH * 9 / 16, WINDOW_HEIGHT * 11 / 12 }, { WINDOW_WIDTH * 11 / 32, WINDOW_HEIGHT * 2 / 75 }, 20, GetColor(64, 142, 142));
	std::deque<dxle::pointi> pos_record;
	bool is_normal_state = true;
	while ((is_normal_state = this->pimpl->normal_con_f()) && this->pimpl->m_state.update() && !this->pimpl->m_state[KEY_INPUT_Z] && !this->pimpl->m_state.esc()) {
		power_bar.update();
		const int d = this->pimpl->move_x(this->pimpl->m_bouninngenn_a.calc_first_bottom_right_pos().x, this->pimpl->m_bouninngenn_b.get_fitst_pos().x);
		if (d < 0) pos_record.clear();//逆方向に進んだらflush
		if (POS_REC_NUM < pos_record.size()) pos_record.pop_front();
		pos_record.push_back(this->pimpl->m_bouninngenn_b.get_pos());
		this->pimpl->m_back_img.DrawGraph({}, false);
		this->pimpl->bouninngen_draw();
		DrawBox_kai(POWER_BAR_BG_POS, POWER_BAR_BG_SIZE, DxLib::GetColor(4, 182, 182), 2, DxLib::GetColor(229, 255, 255));
		this->pimpl->m_img["game_main_gauge_bg"].DrawExtendGraph(POWER_BAR_BG_POS, POWER_BAR_BG_POS + POWER_BAR_BG_SIZE, false);
		power_bar.draw();
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (this->pimpl->m_state.esc()) throw normal_exit();

	//save image
	auto tmp = dxle::graph2d::MakeScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
	tmp.drawn_on([this, &power_bar](){
		this->pimpl->m_back_img.DrawGraph({}, false);
		DrawBox_kai(POWER_BAR_BG_POS, POWER_BAR_BG_SIZE, DxLib::GetColor(4, 182, 182), 2, DxLib::GetColor(229, 255, 255));
		this->pimpl->m_img["game_main_gauge_bg"].DrawExtendGraph(POWER_BAR_BG_POS, POWER_BAR_BG_POS + POWER_BAR_BG_SIZE, false);
		power_bar.draw();
	});
	this->pimpl->game_end_img = std::move(tmp);

	const auto rate = bouninngenn_moving_distance(this->pimpl->m_bouninngenn_a, this->pimpl->m_bouninngenn_b);
	const auto p_rate = power_bar.get_percent();
	if (rate < 70.0 || p_rate < 60.0) {
		this->pimpl->fall_bouninngenn<1>(pos_record, power_bar);//落とそうとして落とされる、ゲームオーバー
		return Status::GAME_OVER;
	}
	else {
		this->pimpl->score = static_cast<uint8_t>((p_rate + rate) / 2);//0-100
		if (this->pimpl->score < 40) {
			this->pimpl->fall_bouninngenn<1>(pos_record, power_bar);//落とそうとして落とされる、ゲームオーバー
			return Status::GAME_OVER;
		}
		else {
			this->pimpl->fall_bouninngenn<0>(pos_record, power_bar);//落とす。成功！
			return Status::RESULT_ECHO;
		}
	}
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
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
		extruder(this->pimpl->m_bouninngenn_b, helicopter.get_obj());
		extruder(this->pimpl->m_bouninngenn_a, this->pimpl->m_bouninngenn_b);
		this->pimpl->bouninngen_draw();
		helicopter.draw();
		//WaitKey();
		if (this->pimpl->m_bouninngenn_a.is_fallen() && this->pimpl->m_bouninngenn_b.is_fallen()) break;//ふたりとも落ちたらゲーム終わり
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (pimpl->m_state.esc()) throw normal_exit();
	//save image
	auto tmp = dxle::graph2d::MakeScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
	tmp.drawn_on([this, &helicopter]() {
		this->pimpl->m_back_img.DrawGraph({}, false);
		helicopter.draw();
	});
	this->pimpl->game_end_img = std::move(tmp);
	return Status::CONTINUE;
}
Status game_c::echo_score()
{
	if (!this->pimpl->game_end_img) throw std::runtime_error("this->pimpl->game_end_img is empty.");

	return Status::CONTINUE;
}
Status game_c::echo_game_over()
{
	if (!this->pimpl->game_end_img) throw std::runtime_error("this->pimpl->game_end_img is empty.");
	this->pimpl->m_state.fllush();
	this->pimpl->game_end_img->DrawGraph(dxle::pointi{}, false);
	this->pimpl->m_state.fllush();
	this->pimpl->game_end_img->filter_HSB(0, 0, 0, -60);
	this->pimpl->game_end_img->DrawGraph(dxle::pointi{}, false);
	const auto font = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);
	DrawStringToHandle(260, 150, "GAME OVER!", DxLib::GetColor(255, 255, 255), font);
	DrawStringToHandle(260, 200, "Press Z to continue.", DxLib::GetColor(255, 255, 255), font);
	bool is_normal_state = this->pimpl->normal_con_f();
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	while ((is_normal_state = -1 != ProcessMessage()) && pimpl->m_state.update() && !pimpl->m_state[KEY_INPUT_Z] && !pimpl->m_state.esc()) std::this_thread::sleep_for(std::chrono::milliseconds(50));
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (pimpl->m_state.esc()) throw normal_exit();
	return Status::CONTINUE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
