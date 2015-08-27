#pragma once
#include "util_INT2_t_calc.h"
#include "define.h"
class power_bar_c
{
public:
	power_bar_c(INT2_t base_point, INT2_t whole_bar_size_, size_t frame_num_to_fill);
	explicit power_bar_c(const power_bar_c& o);
	void update();
	int draw() const;
	double get_percent() const;
private:
	INT2_t base_point_;
	INT2_t whole_bar_size_;
	double pixcel_per_frame_;
	double percent_;
};
