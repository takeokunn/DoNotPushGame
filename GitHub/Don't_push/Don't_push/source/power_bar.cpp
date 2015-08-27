#include "power_bar.h"

power_bar_c::power_bar_c(INT2_t base_point, INT2_t whole_bar_size, size_t frame_num_to_fill) : base_point_(base_point), whole_bar_size_(whole_bar_size), percent_(0){
	this->pixcel_per_frame_ = static_cast<double>(whole_bar_size.first) / frame_num_to_fill;
}

power_bar_c::power_bar_c(const power_bar_c & o) : base_point_(o.base_point_), whole_bar_size_(o.whole_bar_size_), pixcel_per_frame_(o.pixcel_per_frame_), percent_(o.percent_) {}
