#include "flying_mare.h"
#include "DxLib.h"
#include "define.h"

main_status fly_anime(img_arr_t& img_arr) {
	while (-1 != ProcessMessage()){
		ClearDrawScreen();
		img_arr[_T("seoinage")].DrawGraph(100, 100, true);

		if (CheckHitKey(KEY_INPUT_Z) == 1){
			return main_status::title;
		}
	}

	return main_status::title;

}

