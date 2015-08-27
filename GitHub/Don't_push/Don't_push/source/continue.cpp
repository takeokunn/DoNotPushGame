#include "continue.h"
#include "Dxkeystate.h"
#include "DxLib.h"
Status continu(img_arr_t& img_arr) {

	/////////////

	//フォント
	int Font_1;			//選択肢表示の文字
	Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);

	//関数
	int select0_x = 200;	//文字の座標（左上）
	int select0_y = 150;
	int select1_x = 200;
	int select1_y = 250;

	int color[2];
	color[0] = GetColor(0,0,0);				//選択している奴の色
	color[1] = GetColor(255,255,255);		//選択していない奴の色

	int answer = 0;		//コンティニューするかどうか（0:YES　1:NO）

	//メインループ
	while (TRUE){
		ClearDrawScreen();

		//十字キー受付
		keystate state;
		state.update();
		if (state.up() && answer == 1){
			answer = 0;
		}
		else if (state.down() && answer == 0){
			answer = 1;
		}


		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景

		DrawStringToHandle(select0_x + ((answer+1)%2)*40, select0_y, "CONTINUE !!", color[answer], Font_1);				//CONTINUE
		DrawStringToHandle(select1_x + answer*40		, select1_y, "RETIRE. . .", color[(answer+1)%2], Font_1);		//RETIRE

		DrawBox(150, 155 + answer*100, 170, 175 + answer*100, color[0], TRUE);	//選択してるのが分かるようにするやつ


		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_A) == 1){		//Aキーで決定
			switch (answer){
			case 0:
				return Status::GAME;
			case 1:
				return Status::TITLE;
			}
		}
	}

	return Status::EXIT; //基本ここには来ないはず。例外処理で強制終了

	///////////// by yuchu
}
