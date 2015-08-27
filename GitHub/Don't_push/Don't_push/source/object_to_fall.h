#pragma once
#include "define.h"
#include "DxGraphicHandle.h"
class object_to_fall_c
{
public:
	object_to_fall_c(int x, int y, const object_to_fall_c& handle);
	object_to_fall_c(INT2_t p, const object_to_fall_c& handle);
	INT2_t xy_move();
private:
	int x_;
	int y_;
	DxGHandle handle_;
};
