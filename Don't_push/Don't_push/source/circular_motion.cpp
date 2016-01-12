#include "circular_motion.h"
#include "DxLib.h"
obj_info::obj_info(const dxle::pointi& first_p, const DxGHandle* img_normal, const DxGHandle* img_fall)
	: m_fall_frame(0), m_first_pos_(first_p), m_p_(first_p), m_img_({ { img_normal, img_fall } }), m_current_img_no_(0)
{
	this->m_screen_ = dxle::Graph2D::MakeScreen(this->m_img_[0]->GetGraphSize().x / 3, this->m_img_[0]->GetGraphSize().y / 3, true);
	this->m_screen_.DrawnOn([this]() {this->m_img_[0]->DrawExtendGraph({}, { this->m_img_[0]->GetGraphSize().x / 3, this->m_img_[0]->GetGraphSize().y / 3 }, true); });
}

obj_info::obj_info(obj_info&& o) NOEXCEPT
	: m_first_pos_(o.m_first_pos_), m_p_(o.m_p_), m_img_(o.m_img_),
	m_screen_(std::move(o.m_screen_)), m_current_img_no_(o.m_current_img_no_)
{}

dxle::pointi obj_info::calc_first_bottom_right_pos() const NOEXCEPT {
	auto re = this->m_p_ + this->m_screen_.GetGraphSize();
	return re;
}

dxle::pointi obj_info::distance_from_first() const NOEXCEPT {
	auto re = this->m_first_pos_ - this->m_p_;
	return re;
}

void obj_info::change_img(int no) NOEXCEPT {
	this->m_current_img_no_ = (no < 0 || this->m_img_.size() <= static_cast<size_t>(no)) ? this->m_current_img_no_ ^ 1 : static_cast<uint8_t>(no);
	this->m_screen_.DrawnOn([this]() {
		this->m_img_[0]->DrawExtendGraph({}, { this->m_img_[m_current_img_no_]->GetGraphSize().x / 3, this->m_img_[m_current_img_no_]->GetGraphSize().y / 3 }, true);
	});
}

bool obj_info::draw(bool Trans_flag) const NOEXCEPT {
	return 0 == this->m_screen_.DrawGraph(this->m_p_, Trans_flag);
}

void obj_info::state_init() NOEXCEPT {
	this->m_p_ = m_first_pos_;
	this->change_img(0);
}

const dxle::Graph2D::screen& obj_info::get_img() const NOEXCEPT { return this->m_screen_; }
const dxle::pointi& obj_info::get_fitst_pos() const NOEXCEPT { return this->m_first_pos_; }
dxle::pointi& obj_info::get_pos() NOEXCEPT { return this->m_p_; }
const dxle::pointi& obj_info::get_pos() const NOEXCEPT { return this->m_p_; }
bool obj_info::is_fallen() const NOEXCEPT { return WINDOW_HEIGHT < this->m_p_.y; }

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

int distance(const obj_info & l, const obj_info & r) NOEXCEPT {
	return r.get_pos().x - l.get_img().GetGraphSize().width - l.get_pos().x;
}

int distance_first(const obj_info & l, const obj_info & r) NOEXCEPT {
	return r.get_fitst_pos().x - l.get_img().GetGraphSize().width - l.get_fitst_pos().x;
}
