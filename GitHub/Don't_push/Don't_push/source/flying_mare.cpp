#include "flying_mare.h"
#include "DxLib.h"
#include "define.h"

Status fly_anime(img_arr_t& img_arr) {


	int img;
	img = LoadGraph("../Don't_push/assets/img/seoinage.png");
	while (-1 != ProcessMessage()){
		ClearDrawScreen();
		DrawGraph(100, 100, img, TRUE);

		if (CheckHitKey(KEY_INPUT_Z) == 1){
			return Status::TITLE;
		}
	}

	return Status::TITLE;

}

