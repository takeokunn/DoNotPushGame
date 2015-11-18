#pragma once
#include "define.h"
#include "load.h"
#include "Dxkeystate.h"
#include <dxlibex/basic_types.hpp>
class game_c
{
public:
	explicit game_c(const dxle::pointi& p);
	~game_c();
	game_c(const game_c&) = delete;
	game_c(game_c&&) = delete;
	const img_arr_t& get_img() const NOEXCEPT;
	const img_arr_t& get_status_img() const NOEXCEPT;
	const sound_arr_t& get_sound() const NOEXCEPT;

	bool normal_con_f() const NOEXCEPT;
	void move_x() NOEXCEPT;

	Status game_main();
	//Status helicopter();
private:
	const dxle::pointi m_first_;
	dxle::pointi m_p_;
	keystate m_state_;
	img_arr_t m_img_;
	img_arr_t m_status_img_;
	sound_arr_t m_sound_;
};
