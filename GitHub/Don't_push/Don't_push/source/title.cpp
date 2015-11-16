#include "title.h"
#include "DxLib.h"
#include "define.h"
Status title(const img_arr_t&, const sound_arr_t& sound) {
	sound.at("title").play(DxSoundMode::LOOP);//p0052r0のscope_exitがほしい
	//フォントの定義
	const int Font_title = CreateFontToHandle(nullptr, 70, 5, DX_FONTTYPE_EDGE);        //タイトルロゴ
	const int Font_1     = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Zキーを押してね」の奴
	ClearDrawScreen();
	do{
		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景

		DrawStringToHandle(30 + 5, WINDOW_HEIGHT / 3 + 5, "D...DON'T PUSH!!", GetColor(255, 255, 255), Font_title);		//タイトル（影）
		DrawStringToHandle(30, WINDOW_HEIGHT / 3, "D...DON'T PUSH!!", GetColor(0, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Zキーを押してね -", GetColor(0, 0, 0), Font_1); //Zキー押してね

		ScreenFlip();
		ClearDrawScreen();
	} while (1 != CheckHitKey(KEY_INPUT_Z) && -1 != ProcessMessage());

	sound.at("title").stop();
	return Status::GAME;
}
