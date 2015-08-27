#include "title.h"
#include "DxLib.h"
#include "define.h"
Status title(img_arr_t& img_arr) {
	
	/////////////

	//フォントの定義
	int Font_title;		//タイトルロゴ
	int Font_1;			//「Zキーを押してね」の奴
	Font_title = CreateFontToHandle(NULL, 70, 5, DX_FONTTYPE_EDGE);
	Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	ClearDrawScreen();
	do{
		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景

		DrawStringToHandle(30 + 5, WINDOW_HEIGHT / 3 + 5, "D...DON'T PUSH!!", GetColor(255, 255, 255), Font_title);		//タイトル（影）
		DrawStringToHandle(30, WINDOW_HEIGHT / 3, "D...DON'T PUSH!!", GetColor(0, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Zキーを押してね -", GetColor(0, 0, 0), Font_1); //Zキー押してね

		ScreenFlip();
		ClearDrawScreen();
	} while (1 != CheckHitKey(KEY_INPUT_Z));

	///////////// by yuchu

	return Status::GAME;

}
