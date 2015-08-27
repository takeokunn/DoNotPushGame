#include "game.h"
#include "Dxkeystate.h"
#include "DxLib.h"
void foo(){
	int x;
	keystate state;
	state.update();
	if (state.left())  x -= 1;
	if (state != KEY_INPUT_PGUP) x += 2;
}
int move_x(int current_x, keystate& state){
	constexpr int CHARACTER_MOVE_SPEED = 4;
	int re = current_x;
	state.update();
	if (state.left() ) re -= CHARACTER_MOVE_SPEED;
	if (state.right()) re += CHARACTER_MOVE_SPEED;
	return re;
}

Status game(img_arr_t& img_arr){
	ClearDrawScreen();
	img_arr["game"].DrawGraph(0, 0, false);
	ScreenFlip();
	keystate state;
	int x;
	while (1){
		x = move_x(x, state);
		img_arr["game"].DrawGraph(x, 0, false);
		ScreenFlip();
		ClearDrawScreen();
	}

	while (CheckHitKey(KEY_INPUT_D) != 1);
	return Status::END;
}