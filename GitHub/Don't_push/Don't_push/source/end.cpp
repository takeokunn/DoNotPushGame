#include "end.h"
#include "DxLib.h"
#include "Dxkeystate.h"

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status end(const img_arr_t&, const sound_arr_t& sound) {
	for (auto& s : sound) s.second.stop();//BGM全部停止
	//フォントの定義
	const int Font_title = CreateFontToHandle(nullptr, 100, 5, DX_FONTTYPE_EDGE);//タイトルロゴ
	const int Font_1 = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Xキーを押してね」の奴
	keystate state;
	state.flush();
	auto normal_con_f = []() -> bool { return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); };
	volatile bool is_normal_state;
	while ((is_normal_state = normal_con_f()) && state.update() && !state[KEY_INPUT_X] && !state.esc()) {
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(200, 200, 100), TRUE);	//背景

		DrawStringToHandle(100, WINDOW_HEIGHT / 4, "やったぜ。", GetColor(250, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Xキーを押してね -", GetColor(0, 0, 0), Font_1);//Xキー押してね
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (state.esc()) throw normal_exit();
	return Status::TITLE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
