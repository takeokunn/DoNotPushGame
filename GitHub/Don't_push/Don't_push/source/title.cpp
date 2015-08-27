#include "title.h"
#include "DxLib.h"
Status title(img_arr_t& img_arr) {
	ClearDrawScreen();
	img_arr["title"].DrawGraph(0, 0, false);
	ScreenFlip();

	/////////////

	int Font_title;
	Font_title = CreateFontToHandle(NULL, 20, 5, DX_FONTTYPE_EDGE);


	///////////// by yuchu

	while (CheckHitKey(KEY_INPUT_Z) != 1);
	return Status::GAME;

}
