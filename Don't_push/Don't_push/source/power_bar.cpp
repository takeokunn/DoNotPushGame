#include "power_bar.h"
#include "DxLib.h"
#include "DxHandleException.h"

power_bar_c::power_bar_c(const dxle::pointi& base_point, const dxle::sizei& whole_bar_size, size_t frame_num_to_fill, unsigned int color) NOEXCEPT
	: base_point_(base_point), whole_bar_size_(whole_bar_size), draw_pixcel_num_(0), 
	color_(color), spent_frame_(0), frame_num_to_fill_(frame_num_to_fill) {}

power_bar_c::power_bar_c(const power_bar_c & o) NOEXCEPT 
	: base_point_(o.base_point_), whole_bar_size_(o.whole_bar_size_), draw_pixcel_num_(o.draw_pixcel_num_), 
	color_(o.color_), spent_frame_(o.spent_frame_), frame_num_to_fill_(o.frame_num_to_fill_) {}

void power_bar_c::update() NOEXCEPT {
	++this->spent_frame_;
	if (this->spent_frame_ < this->frame_num_to_fill_) {
		this->draw_pixcel_num_ = static_cast<int>(this->whole_bar_size_.width * this->spent_frame_ / static_cast<double>(this->frame_num_to_fill_));
	}
	else {
		this->draw_pixcel_num_ = 0;//バーが一杯になったら0に戻す
		this->spent_frame_ = 0;
	}
}

int power_bar_c::draw() const DxHANDLE_NOEXCEPT {
	const auto re = DrawBox(this->base_point_.x, this->base_point_.y, this->base_point_.x + this->draw_pixcel_num_ + 1, this->base_point_.y + this->whole_bar_size_.height, this->color_, true);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxDraw_runtime_error("DrawBox failed.");
#endif
	return re;
}

double power_bar_c::get_percent() const NOEXCEPT {
	return 100.0 * this->draw_pixcel_num_ / this->whole_bar_size_.width;
}

