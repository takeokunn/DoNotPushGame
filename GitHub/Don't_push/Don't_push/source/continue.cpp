#include "continue.h"
#include "Dxkeystate.h"
#include "DxLib.h"
Status continu(img_arr_t& img_arr, sound_arr_t& sound) {
	for (auto& s : sound) s.second.stop();//BGM全部停止
	const auto Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);//選択肢表示の文字
	CONSTEXPR_OR_STATICCONST int select0_x = 200;	//文字の座標（左上）
	CONSTEXPR_OR_STATICCONST int select0_y = 150;
	CONSTEXPR_OR_STATICCONST int select1_x = 200;
	CONSTEXPR_OR_STATICCONST int select1_y = 250;

	int color[2];
	color[0] = GetColor(0,0,0);				//選択している奴の色
	color[1] = GetColor(255,255,255);		//選択していない奴の色

	bool flag_no_continue = 0;		//コンティニューするかどうか

	//メインループ
	for (keystate state; -1 != ProcessMessage();) {
		ClearDrawScreen();

		//十字キー受付
		state.update();
		if ((state.up() && flag_no_continue) || (state.down() && !flag_no_continue)){
			flag_no_continue = !flag_no_continue;
		}

		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(180, 180, 180), TRUE);	//背景
		DrawStringToHandle(select0_x + !flag_no_continue*40, select0_y, "CONTINUE !!", color[flag_no_continue], Font_1);				//CONTINUE
		DrawStringToHandle(select1_x + flag_no_continue*40		, select1_y, "RETIRE. . .", color[!flag_no_continue], Font_1);		//RETIRE
		DrawBox(180, 155 + flag_no_continue*100, 200, 175 + flag_no_continue*100, color[0], TRUE);	//選択してるのが分かるようにするやつ
		DrawStringToHandle(120, WINDOW_HEIGHT - (WINDOW_HEIGHT / 4), "- Cキーを押して決定だよ -", GetColor(0, 0, 0), Font_1);//Cキー押してね

		ScreenFlip();

		if (state[KEY_INPUT_C]){		//Cキーで決定
			return (flag_no_continue) ? Status::TITLE : Status::GAME;
		}
	}

	return Status::EXIT; //for ProcessMessage(). 強制終了
}
