#pragma once
#include "util_INT2_t_calc.h"
#include "define.h"
#ifndef DISABLE_DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_WRAP_USE_EXCEPTION//throw‚·‚é
#endif
#include "util_noexcept.h"

class power_bar_c
{
public:
	power_bar_c(INT2_t base_point, INT2_t whole_bar_size_, size_t frame_num_to_fill, unsigned int color) NOEXCEPT;
	explicit power_bar_c(const power_bar_c& o) NOEXCEPT;
	void update() NOEXCEPT;
	int draw() const DxHANDLE_NOEXCEPT;
	double get_percent() const NOEXCEPT;
private:
	INT2_t base_point_;
	INT2_t whole_bar_size_;
	double pixcel_per_frame_;
	double draw_pixcel_num_;
	unsigned int color_;
};
