#include "game.h"
#include "Dxkeystate.h"
#include "DxLib.h"
#include "define.h"
#include "power_bar.h"

int move_x(int current_x, keystate& state){
	CONSTEXPR_OR_CONST int CHARACTER_MOVE_SPEED = 4;
	int re = current_x;
	state.update();
	if (state.left() ) re -= CHARACTER_MOVE_SPEED;
	if (state.right()) re += CHARACTER_MOVE_SPEED;
	return re;
}
Status game(img_arr_t& img_arr, sound_arr_t& sound){
	ClearDrawScreen();
	img_arr["game"].DrawGraph(0, 0, false);
	ScreenFlip();
	keystate state;
	int x = FIRST_CHARA_X;
	while (-1 != ProcessMessage()){
		x = move_x(x, state);
		img_arr["game"].DrawGraph(x, 0, false);
		ScreenFlip();
		ClearDrawScreen();
	}

	while (CheckHitKey(KEY_INPUT_D) != 1 && -1 != ProcessMessage());
	return Status::END;
}
