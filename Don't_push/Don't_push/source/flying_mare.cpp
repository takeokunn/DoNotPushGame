#include "flying_mare.h"
#include "DxLib.h"
#include "define.h"

Status fly_anime(img_arr_t& img_arr) {
	while (-1 != ProcessMessage()){
		ClearDrawScreen();
		img_arr["seoinage"].DrawGraph(100, 100, true);

		if (CheckHitKey(KEY_INPUT_Z) == 1){
			return Status::TITLE;
		}
	}

	return Status::TITLE;

}

