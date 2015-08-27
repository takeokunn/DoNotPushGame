#include "game.h"
#include "Dxkeystate.h"
#include "DxLib.h"
#include "define.h"
int move_x(int current_x, keystate& state){
	CONSTEXPR_OR_CONST int CHARACTER_MOVE_SPEED = 4;
	int re = current_x;
	state.update();
	if (state.left() ) re -= CHARACTER_MOVE_SPEED;
	if (state.right()) re += CHARACTER_MOVE_SPEED;
	return re;
}
#pragma warning(push)
#pragma warning(disable: 4127)
//C4127: 条件式が定数です。
Status game(img_arr_t& img_arr){
	ClearDrawScreen();
	img_arr["game"].DrawGraph(0, 0, false);
	ScreenFlip();
	keystate state;
	int x = FIRST_CHARA_X;
	while (1){
		x = move_x(x, state);
		img_arr["game"].DrawGraph(x, 0, false);
		ScreenFlip();
		ClearDrawScreen();
	}

	while (CheckHitKey(KEY_INPUT_D) != 1);
	return Status::END;
}
#pragma warning(pop)
