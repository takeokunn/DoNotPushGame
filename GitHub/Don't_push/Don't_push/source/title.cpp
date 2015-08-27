#include "title.h"
#include "DxLib.h"
Status title(img_arr_t& img_arr) {
	
	//img_arr["title"].DrawGraph(0, 0, false);

	/////////////

	//画像の読み込み
	

	//カウンター
	int count = 0;

	//フォントの定義
	int Font_title;		//タイトルロゴ
	int Font_1;			//「Zキーを押してね」の奴
	Font_title = CreateFontToHandle(NULL, 70, 5, DX_FONTTYPE_EDGE);
	Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);

	while (TRUE){
		count++;
		ClearDrawScreen();

		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景

		//img_arr["red2"].DrawGraph(30, 10, TRUE);

		DrawStringToHandle(30 + 5, WINDOW_HEIGHT / 3 + 5, "D...DON'T PUSH!!", GetColor(255, 255, 255), Font_title);		//タイトル（影）
		DrawStringToHandle(30, WINDOW_HEIGHT / 3, "D...DON'T PUSH!!", GetColor(0, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Zキーを押してね -", GetColor(0, 0, 0), Font_1);//Zキー押してね

		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_Z) == 1){
			break;
		}
	}

	

	///////////// by yuchu

	return Status::GAME;

}
