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
int ver(int current_x, keystate& state){
	constexpr int CHARACTER_MOVE_SPEED = 4;
	int re = current_x;
	state.update();
	if (state.left() || state == KEY_INPUT_A) re -= CHARACTER_MOVE_SPEED;

}

Status game(img_arr_t& img_arr){
	ClearDrawScreen();
	img_arr["game"].DrawGraph(0, 0, false);
	ScreenFlip();

	while (CheckHitKey(KEY_INPUT_D) != 1);
	return Status::END;
}