#pragma once
#include "define.h"
#include <dxlibex/basic_types.hpp>
#include <dxlibex/Graph2D.h>
#include <array>
#include <cstdint>

class obj_info
{
public:
	obj_info(const dxle::pointi& first_p, const DxGHandle* img_normal, const DxGHandle* img_fall);
	obj_info(const obj_info& o) = delete;
	obj_info(obj_info&& o) NOEXCEPT;
	obj_info& operator=(const obj_info&) = delete;
	obj_info& operator=(obj_info&&) = delete;
	void change_img(int no = -1) NOEXCEPT;
	bool draw(bool Trans_flag = true) const NOEXCEPT;
	void state_init() NOEXCEPT;
	const dxle::Graph2D::screen& get_img() const NOEXCEPT;
	const dxle::pointi& get_fitst_pos() const NOEXCEPT;
	dxle::pointi& get_pos() NOEXCEPT;
	const dxle::pointi& get_pos() const NOEXCEPT;
	dxle::pointi calc_first_bottom_right_pos() const NOEXCEPT;
	dxle::pointi distance_from_first() const NOEXCEPT;
	bool is_fallen() const NOEXCEPT;

	size_t m_fall_frame;
private:
	const dxle::pointi m_first_pos_;
	dxle::pointi m_p_;
	std::array<const DxGHandle*, 2> m_img_;
	dxle::Graph2D::screen m_screen_;
	uint8_t m_current_img_no_;
};
int distance(const obj_info& l, const obj_info& r) NOEXCEPT;
int distance_first(const obj_info& l, const obj_info& r) NOEXCEPT;
class circular_motion
{
public:
	circular_motion() = delete;
	circular_motion(const dxle::pointi& center_pos, const dxle::pointi& first_pos, double angular_v, const DxGHandle& img_normal, const DxGHandle& img_fall) NOEXCEPT;
	circular_motion(const circular_motion&) = delete;
	circular_motion(circular_motion&&) = delete;
	circular_motion& operator=(const circular_motion&) = delete;
	circular_motion& operator=(circular_motion&&) = delete;
	bool update() NOEXCEPT;
	bool draw() const;
	dxle::pointi get_pos() const NOEXCEPT;
	const obj_info& get_obj() const NOEXCEPT;
private:
	const dxle::pointi m_center_;
	const double m_r_;
	const double m_first_rad_;
	double m_angular_v_;// rad./sec. Dextrorotation(âEâÒÇËÅByÇÕâ∫å¸Ç´ê≥)
	obj_info m_obj_;
	size_t m_t_;
};
