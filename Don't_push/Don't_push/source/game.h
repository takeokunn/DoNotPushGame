#pragma once
#include "define.h"
#include <dxlibex/basic_types.hpp>
#include <dxlibex/graph2d.hpp>
#include <memory>
#include "config.h"

class game_c
{
public:
	game_c(const dxle::pointi& bouninngennA_p, const dxle::pointi& bouninngennB_p, const config_info::lang_table_t& lang_table);
	~game_c();
	game_c(const game_c&) = delete;
	game_c(game_c&&) = delete;
	game_c& operator=(const game_c&) = delete;
	game_c& operator=(game_c&&) = delete;
	const img_arr_t& get_img() const NOEXCEPT;
	const sound_arr_t& get_sound() const NOEXCEPT;

	Status game_main();
	Status helicopter_event();
	Status echo_score();
	Status echo_game_over();
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
