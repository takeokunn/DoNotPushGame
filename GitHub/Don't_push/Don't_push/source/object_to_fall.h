#pragma once
#include "define.h"
#include "DxGraphicHandle.h"
class object_to_fall_c
{
public:
	explicit object_to_fall_c(const object_to_fall_c& o);
	object_to_fall_c(int x, int y, int pixcel_per_frame, const DxGHandle& handle);
	object_to_fall_c(const dxle::pointi& p, int pixcel_per_frame, const DxGHandle& handle);
	dxle::pointi xy_move();
	bool collision_detecter(int target_x, int target_y, const DxGHandle& target_handle);
	bool collision_detecter(const dxle::pointi&  target, const DxGHandle& target_handle);
private:
	dxle::pointi self_;
	int pixcel_per_frame_;
	DxGHandle handle_;
};
