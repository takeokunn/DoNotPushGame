#pragma once
#include "define.h"
#include "DxGraphicHandle.h"
class object_to_fall_c
{
public:
	explicit object_to_fall_c(const object_to_fall_c& o);
	object_to_fall_c(int x, int y, int pixcel_per_frame, const DxGHandle& handle);
	object_to_fall_c(INT2_t p, int pixcel_per_frame, const DxGHandle& handle);
	INT2_t xy_move();
	bool collision_detecter(int target_x, int target_y, const DxGHandle& target_handle);
	bool collision_detecter(const INT2_t&  target, const DxGHandle& target_handle);
private:
	INT2_t self_;
	int pixcel_per_frame_;
	DxGHandle handle_;
};
