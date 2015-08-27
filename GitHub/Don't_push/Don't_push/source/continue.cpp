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
	int select0_y = 100;
	int select1_x = 200;
	int select1_y = 200;

	int color[2];
	color[0] = GetColor(255, 255, 255);		//選択している奴の色
	color[1] = GetColor(0,0,0);				//選択していない奴の色

	int answer = 0;		//コンティニューするかどうか（0:YES　1:NO）

	while (TRUE){
		ClearDrawScreen();

		//十字キー受付
		keystate state;
		state.update();
		if (state.up() || state.down()){
			answer = (answer + 1) % 2;
		}


		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景

		DrawStringToHandle(select0_x + ((answer+1)%2)*40, select0_y, "CONTINUE !!", color[answer], Font_1);				//CONTINUE
		DrawStringToHandle(select1_x + answer*40		, select1_y, "RETIRE. . .", color[(answer+1)%2], Font_1);		//RETIRE


		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_Z) == 1){		//Zキーで決定
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
