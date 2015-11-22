#pragma once
#include "define.h"
#include <dxlibex/basic_types.hpp>
#include <dxlibex/Graph2D.h>
#include <memory>

class game_c
{
public:
	game_c(const dxle::pointi& bouninngennA_p, const dxle::pointi& bouninngennB_p);
	~game_c();
	game_c(const game_c&) = delete;
	game_c(game_c&&) = delete;
	const img_arr_t& get_img() const NOEXCEPT;
	const sound_arr_t& get_sound() const NOEXCEPT;

	Status game_main();
	Status helicopter_event();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
