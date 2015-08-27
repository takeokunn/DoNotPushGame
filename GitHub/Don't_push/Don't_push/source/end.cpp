#include "end.h"
#include "DxLib.h"
Status end(img_arr_t& img_arr){

	/////////////

	//フォントの定義
	int Font_title;		//タイトルロゴ
	int Font_1;			//「Xキーを押してね」の奴
	Font_title = CreateFontToHandle(NULL, 100, 5, DX_FONTTYPE_EDGE);
	Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);
	ClearDrawScreen();
	do{
		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(200, 200, 100), TRUE);	//背景

		DrawStringToHandle(100, WINDOW_HEIGHT / 4, "やったぜ。", GetColor(250, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Xキーを押してね -", GetColor(0, 0, 0), Font_1);//Xキー押してね

		ScreenFlip();
		ClearDrawScreen();
	} while (1 != CheckHitKey(KEY_INPUT_X));

	///////////// by yuchu

	return Status::TITLE;
	
}