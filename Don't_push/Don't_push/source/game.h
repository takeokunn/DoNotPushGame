#pragma once
#include "define.h"
#include <dxlibex/basic_types.hpp>
#include <dxlibex/Graph2D.h>
#include <memory>

class game_c
{
public:
	game_c();
	~game_c();
	game_c(const game_c&) = delete;
	game_c(game_c&&) = delete;
	const img_arr_t& get_img() const NOEXCEPT;
	const img_arr_t& get_status_img() const NOEXCEPT;
	const sound_arr_t& get_sound() const NOEXCEPT;

	bool normal_con_f() const NOEXCEPT;
	void move_x() NOEXCEPT;

	void fadeout_prelude_masseage();

	Status game_main();
	Status helicopter_event();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
