#include "end.h"
#include "DxLib.h"
Status end(img_arr_t& img_arr, sound_arr_t& sound) {
	for (auto& s : sound) s.second.stop();//BGM全部停止
	//フォントの定義
	const int Font_title = CreateFontToHandle(nullptr, 100, 5, DX_FONTTYPE_EDGE);//タイトルロゴ
	const int Font_1 = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Xキーを押してね」の奴
	ClearDrawScreen();
	do{
		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(200, 200, 100), TRUE);	//背景

		DrawStringToHandle(100, WINDOW_HEIGHT / 4, "やったぜ。", GetColor(250, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Xキーを押してね -", GetColor(0, 0, 0), Font_1);//Xキー押してね

		ScreenFlip();
		ClearDrawScreen();
	} while (1 != CheckHitKey(KEY_INPUT_X) && -1 != ProcessMessage());

	return Status::TITLE;	
}