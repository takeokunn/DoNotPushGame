#include "title.h"
#include "DxLib.h"
Status title(img_arr_t& img_arr) {
	ClearDrawScreen();
	img_arr["title"].DrawGraph(0, 0, false);
	ScreenFlip();

	/////////////



	///////////// by yuchu

	while (CheckHitKey(KEY_INPUT_Z) != 1);
	return Status::GAME;

}
