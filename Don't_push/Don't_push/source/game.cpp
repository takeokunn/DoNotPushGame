#include "game.h"
#include "Dxkeystate.h"
#include "load.h"
#include "DxLib.h"
#include "define.h"
#include "power_bar.h"
#include <cmath>
#include <array>

class obj_info
{
public:
	obj_info(const dxle::pointi& first_p, const DxGHandle* img_normal, const DxGHandle* img_fall)
		: m_first_pos_(first_p), m_p_(first_p), m_img_({ img_normal, img_fall }), m_fall_frame(0), m_current_img_no_(0)
	{
		this->m_screen_ = dxle::Graph2D::MakeScreen(this->m_img_[0]->GetGraphSize().x / 3, this->m_img_[0]->GetGraphSize().y / 3, true);
		this->m_screen_.DrawnOn([this]() {this->m_img_[0]->DrawExtendGraph({}, { this->m_img_[0]->GetGraphSize().x / 3, this->m_img_[0]->GetGraphSize().y / 3 }, true); });
	}
	void change_img() NOEXCEPT {
		this->m_current_img_no_ ^= 1;//0, 1交互入れ替え
		this->m_screen_.DrawnOn([this]() {
			this->m_img_[0]->DrawExtendGraph({}, { this->m_img_[m_current_img_no_]->GetGraphSize().x / 3, this->m_img_[m_current_img_no_]->GetGraphSize().y / 3 }, true);
		});
	}
	bool draw(bool Trans_flag = true) const NOEXCEPT {
		return 0 == this->m_screen_.DrawGraph(this->m_p_, Trans_flag);
	}
	const dxle::Graph2D::Screen& get_img() const NOEXCEPT { return this->m_screen_; }
	const dxle::pointi& get_fitst_pos() const NOEXCEPT { return this->m_first_pos_; }
	dxle::pointi& get_pos() NOEXCEPT { return this->m_p_; }
	const dxle::pointi& get_pos() const NOEXCEPT { return this->m_p_; }
	bool is_fallen() const NOEXCEPT { return WINDOW_HEIGHT < this->m_p_.y; }

	size_t m_fall_frame;
private:
	const dxle::pointi m_first_pos_;
	dxle::pointi m_p_;
	std::array<const DxGHandle*, 2> m_img_;
	dxle::Graph2D::Screen m_screen_;
	uint8_t m_current_img_no_;
};
struct game_c::Impl {
	Impl() : m_window_s(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), m_state(), m_back_img(dxle::Graph2D::MakeScreen(m_window_s.x, m_window_s.y)),
		m_img(make_image_array()), m_status_img(make_status_image_array()), m_sound(make_sound_array()),
		m_bouninngennA({ WINDOW_WIDTH * 57 / 256 , WINDOW_HEIGHT * 2 / 7 }, &m_img["bouninngennA"], &m_img["bouninngennA_fall"]),//棒人形A
		m_bouninngennB({ WINDOW_WIDTH * 71 / 128 , WINDOW_HEIGHT * 2 / 7 }, &m_img["bouninngennB"], &m_img["bouninngennB_fall"]) //棒人形B
	{
		this->m_back_img.DrawnOn([this]() {m_img["gake"].DrawExtendGraph({}, m_window_s, false); });
	}
	const dxle::pointi m_window_s;
	keystate m_state;
	dxle::Graph2D::Screen m_back_img;
	img_arr_t m_img;
	img_arr_t m_status_img;
	sound_arr_t m_sound;
	obj_info m_bouninngennA;
	obj_info m_bouninngennB;
};
game_c::game_c() : pimpl(new game_c::Impl()){}

game_c::~game_c() {
	for (auto& s : this->pimpl->m_sound) s.second.stop();
}

const sound_arr_t & game_c::get_sound() const NOEXCEPT {
	return this->pimpl->m_sound;
}

const img_arr_t & game_c::get_status_img() const NOEXCEPT {
	return this->pimpl->m_status_img;
}

const img_arr_t & game_c::get_img() const NOEXCEPT {
	return this->pimpl->m_img;
}

bool game_c::normal_con_f() const NOEXCEPT { return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); }

void game_c::move_x() NOEXCEPT{
	static CONSTEXPR_OR_CONST int CHARACTER_MOVE_SPEED = 4;
	this->pimpl->m_state.update();
	if (this->pimpl->m_state.left()) this->pimpl->m_bouninngennB.get_pos().x -= CHARACTER_MOVE_SPEED;
	if (this->pimpl->m_state.right()) this->pimpl->m_bouninngennB.get_pos().x += CHARACTER_MOVE_SPEED;
}

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
void game_c::fadeout_prelude_masseage() {
	constexpr int fadeout_time_frame = 200;
	bool is_normal_state = true;

	//fade out
	for (int i = 0; i < fadeout_time_frame && (is_normal_state = normal_con_f()) && pimpl->m_state.update() && !pimpl->m_state.esc(); ++i) {
		this->pimpl->m_back_img.DrawGraph({}, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>((fadeout_time_frame - i) * 256.0 / fadeout_time_frame));
		this->pimpl->m_img["back_str"].DrawGraph({}, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		this->pimpl->m_bouninngennA.draw();
		this->pimpl->m_bouninngennB.draw();
	}
	if (pimpl->m_state.esc()) throw normal_exit();
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status game_c::game_main() {
	this->pimpl->m_state.fllush();
	this->pimpl->m_sound["flower garden"].play(DxSoundMode::LOOP);
	this->fadeout_prelude_masseage();
	bool is_normal_state = true;
	while ((is_normal_state = normal_con_f()) && pimpl->m_state.update() && !pimpl->m_state[KEY_INPUT_Z] && !pimpl->m_state.esc()) {
		this->move_x();
		this->pimpl->m_back_img.DrawGraph({}, false);
		this->pimpl->m_bouninngennB.draw();
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (pimpl->m_state.esc()) throw normal_exit();
	return Status::CONTINUE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
class circular_motion
{
public:
	circular_motion() = delete;
	circular_motion(const dxle::pointi& center_pos, const dxle::pointi& first_pos, double angular_v, const DxGHandle& img_normal, const DxGHandle& img_fall) NOEXCEPT;
	circular_motion(const circular_motion&) = delete;
	circular_motion(circular_motion&&) = delete;
	circular_motion& operator=(const circular_motion&) = delete;
	circular_motion& operator=(circular_motion&&) = delete;
	bool update() NOEXCEPT;
	bool draw() const;
	dxle::pointi get_pos() const NOEXCEPT;
	const obj_info& get_obj() const NOEXCEPT;
private:
	const dxle::pointi m_center_;
	const double m_r_;
	const double m_first_rad_;
	double m_angular_v_;// rad./sec. Dextrorotation(右回り。yは下向き正)
	obj_info m_obj_;
	size_t m_t_;
};

circular_motion::circular_motion(const dxle::pointi & center_pos, const dxle::pointi& first_pos, double angular_v, const DxGHandle& img_normal, const DxGHandle& img_fall) NOEXCEPT
	: m_center_(center_pos), m_r_(std::hypot(first_pos.x - m_center_.x, first_pos.y - m_center_.y)), 
	m_first_rad_(std::acos((first_pos.x - m_center_.x) / m_r_) * (((first_pos.y - m_center_.y) < 0) ? -1 : 1)),
	m_angular_v_(angular_v), m_obj_(first_pos, &img_normal, &img_fall), m_t_()
{}

bool circular_motion::update() NOEXCEPT {
	++this->m_t_;
	this->m_obj_.get_pos() = static_cast<dxle::pointi>(dxle::pointd(m_center_.x + this->m_r_ * std::cos(m_first_rad_ + this->m_t_ * this->m_angular_v_), m_center_.y + this->m_r_ * std::sin(m_first_rad_ + this->m_t_ * this->m_angular_v_)));
	return true;
}

bool circular_motion::draw() const {
	return this->m_obj_.draw();
}

const obj_info & circular_motion::get_obj() const NOEXCEPT { return this->m_obj_; }

dxle::pointi circular_motion::get_pos() const NOEXCEPT {
	return this->m_obj_.get_pos();
}

static void extruded(obj_info& move_target, const obj_info& move_cause) {
	constexpr double g = 9.80665;
	if (move_target.get_pos().x + move_target.get_img().GetGraphSize().x < WINDOW_WIDTH / 4) {
		++move_target.m_fall_frame;
		move_target.get_pos().y = move_cause.get_fitst_pos().y + static_cast<int>(10.5 * g / 2 * move_target.m_fall_frame);//自由落下
		if (1 == move_target.m_fall_frame) {
			move_target.change_img();
		}
	}
	if (move_cause.get_pos().x < move_target.get_pos().x + move_target.get_img().GetGraphSize().x) {
		move_target.get_pos().x = move_cause.get_pos().x - move_target.get_img().GetGraphSize().x;
	}
}
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status game_c::helicopter_event() {
	this->pimpl->m_state.fllush();
	this->pimpl->m_sound["flower garden"].play(DxSoundMode::LOOP);
	this->fadeout_prelude_masseage();
	circular_motion helicopter(
		{ pimpl->m_window_s.x / 2, -100 }, { pimpl->m_window_s.x * 23 / 26, pimpl->m_window_s.y * 1 / 82 },
		1.0 / 30.0, this->pimpl->m_img["herikoputa-"], this->pimpl->m_img["herikoputa-"]
	);
	bool is_normal_state = true;
	while ((is_normal_state = normal_con_f()) && pimpl->m_state.update() && !pimpl->m_state[KEY_INPUT_Z] && !pimpl->m_state.esc() && helicopter.update()) {
		this->pimpl->m_back_img.DrawGraph({}, false);
		extruded(this->pimpl->m_bouninngennB, helicopter.get_obj());
		extruded(this->pimpl->m_bouninngennA, this->pimpl->m_bouninngennB);
		this->pimpl->m_bouninngennA.draw();
		this->pimpl->m_bouninngennB.draw();
		helicopter.draw();
		//WaitKey();
		if (this->pimpl->m_bouninngennA.is_fallen() && this->pimpl->m_bouninngennB.is_fallen()) break;//ふたりとも落ちたらゲーム終わり
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (pimpl->m_state.esc()) throw normal_exit();
	return Status::CONTINUE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
