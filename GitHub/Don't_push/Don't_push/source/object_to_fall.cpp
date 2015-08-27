#include "object_to_fall.h"

object_to_fall_c::object_to_fall_c(const object_to_fall_c & o) : handle_(o.handle_), self_(o.self_), pixcel_per_frame_(o.pixcel_per_frame_){}
object_to_fall_c::object_to_fall_c(int x, int y, int pixcel_per_frame, const DxGHandle & handle) : handle_(handle), self_({x, y}), pixcel_per_frame_(pixcel_per_frame_) {}
object_to_fall_c::object_to_fall_c(INT2_t p, int pixcel_per_frame, const DxGHandle & handle) : handle_(handle), self_(p), pixcel_per_frame_(pixcel_per_frame_) {}

INT2_t object_to_fall_c::xy_move(){
	return INT2_t({this->self_.first, this->self_.second + this->pixcel_per_frame_});
}

bool object_to_fall_c::collision_detecter(INT2_t target){
	const auto pix_size = this->handle_.GetGraphSize();
	return false;
}
