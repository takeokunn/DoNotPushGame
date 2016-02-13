#include "object_to_fall.h"

object_to_fall_c::object_to_fall_c(const object_to_fall_c & o) : handle_(o.handle_), self_(o.self_), pixcel_per_frame_(o.pixcel_per_frame_){}
object_to_fall_c::object_to_fall_c(int x, int y, int pixcel_per_frame, const DxGHandle & handle) : handle_(handle), self_({x, y}), pixcel_per_frame_(pixcel_per_frame) {}
object_to_fall_c::object_to_fall_c(const dxle::pointi& p, int pixcel_per_frame, const DxGHandle & handle) : handle_(handle), self_(p), pixcel_per_frame_(pixcel_per_frame) {}

dxle::pointi object_to_fall_c::xy_move(){
	return {this->self_.x, this->self_.y + this->pixcel_per_frame_};
}

bool object_to_fall_c::collision_detecter(int target_x, int target_y, const DxGHandle & target_handle){
	return this->collision_detecter({ target_x, target_y }, target_handle);
}

bool object_to_fall_c::collision_detecter(const dxle::pointi& target, const DxGHandle& target_handle){
	const auto self_center = this->handle_.GetRelativeGraphCenter() + this->self_;
	const auto tareget_pic_size = target_handle.GetGraphSize() + target;
	return (target.y < self_center.y && self_center.y < tareget_pic_size.height && target.x < self_center.x && self_center.x < tareget_pic_size.width);
}
