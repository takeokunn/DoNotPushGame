#include "power_bar.h"
#include "DxLib.h"
#include "DxHandleException.h"

power_bar_c::power_bar_c(INT2_t base_point, INT2_t whole_bar_size, size_t frame_num_to_fill, unsigned int color) NOEXCEPT : base_point_(base_point), whole_bar_size_(whole_bar_size), draw_pixcel_num_(0), color_(color) {
	this->pixcel_per_frame_ = static_cast<double>(whole_bar_size.first) / frame_num_to_fill;
}

power_bar_c::power_bar_c(const power_bar_c & o) NOEXCEPT : base_point_(o.base_point_), whole_bar_size_(o.whole_bar_size_), pixcel_per_frame_(o.pixcel_per_frame_), draw_pixcel_num_(o.draw_pixcel_num_), color_(o.color_) {}

void power_bar_c::update() NOEXCEPT {
	this->draw_pixcel_num_ += this->pixcel_per_frame_;
	if (this->whole_bar_size_.first < this->draw_pixcel_num_) this->draw_pixcel_num_ = 0.0;//バーが一杯になったら0に戻す
}

int power_bar_c::draw() const DxHANDLE_NOEXCEPT {
	const auto re = DrawBox(this->base_point_.first, this->base_point_.second, this->draw_pixcel_num_ + 1, this->whole_bar_size_.second, this->color_, TRUE);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxDraw_runtime_error("DrawBox failed.");
#endif
	return re;
}

double power_bar_c::get_percent() const NOEXCEPT {
	return 100.0 * this->draw_pixcel_num_ / this->whole_bar_size_.first;
}

