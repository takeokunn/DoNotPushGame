#include "continue.h"
#include "Dxkeystate.h"
#include "DxLib.h"
#include <array>
#include <algorithm>
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status continu(const img_arr_t&, const sound_arr_t& sound) {
	for (auto& s : sound) s.second.stop();//BGM全部停止
	const auto Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);//選択肢表示の文字
	DXLE_STATIC_CONSTEXPR int select0_x = 260;	//文字の座標（左上）
	DXLE_STATIC_CONSTEXPR int select0_y = 150;
	DXLE_STATIC_CONSTEXPR int select1_x = 260;
	DXLE_STATIC_CONSTEXPR int select1_y = 250;

	const std::array<unsigned int, 2>color = { { GetColor(0,0,0), GetColor(255,255,255) } };//選択している, 選択していない
	bool flag_no_continue = false;		//コンティニューするかどうか

	//メインループ
	keystate state;
	auto normal_con_f = []() -> bool { return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); };
	bool is_normal_state;
	while ((is_normal_state = normal_con_f()) && state.update() && !state[KEY_INPUT_Z] && !state.esc()) {
		//十字キー受付
		if ((state.up() & flag_no_continue) || (state.down() & !flag_no_continue)){
			flag_no_continue = !flag_no_continue;
		}
		//描画
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(180, 180, 180), TRUE);	//背景
		DrawStringToHandle(select0_x + !flag_no_continue*40, select0_y, "CONTINUE !!", color[flag_no_continue] , Font_1);//CONTINUE
		DrawStringToHandle(select1_x + flag_no_continue*40 , select1_y, "RETIRE. . .", color[!flag_no_continue], Font_1);//RETIRE
		DrawBox(180, 155 + flag_no_continue*100, 200, 175 + flag_no_continue*100, color[0], TRUE);	//選択してるのが分かるようにするやつ
		DrawStringToHandle(120, WINDOW_HEIGHT - (WINDOW_HEIGHT / 4), "- Zキーを押して決定だよ -", GetColor(0, 0, 0), Font_1);//Cキー押してね
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (state.esc()) throw normal_exit();
	return (flag_no_continue) ? Status::TITLE : Status::HELICOPTER_ANIMATION;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
