#include "end.h"
#include "DxLib.h"
#include "Dxkeystate.h"
#include <chrono>
#include <thread>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status end(const img_arr_t&, const sound_arr_t& sound, const config_info::lang_table_t& lang_table) {
	for (auto& s : sound) s.second.stop();//BGM全部停止
	//フォントの定義
	const int font_title = CreateFontToHandle(nullptr, 100, 5, DX_FONTTYPE_EDGE);//タイトルロゴ
	const int font_1 = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Xキーを押してね」の奴
	keystate state;
	auto normal_con_f = []() -> bool {
		bool re = -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen();
		if (!re) throw std::runtime_error("ProcessMessage() return -1.");
		return re;
	};
	bool is_normal_state = normal_con_f();
	DrawBox(0, 0, WINDOW.width, WINDOW.height, GetColor(200, 200, 100), TRUE);	//背景
	DrawStringToHandle(WINDOW.width * 37 / 320, WINDOW.height / 4, (L"- " + lang_table.at(L"I did it!") + L" -").c_str(), GetColor(250, 0, 0), font_title);
	DrawStringToHandle(WINDOW.width * 13 / 40, WINDOW.height / 4 + 250, (L"- " + lang_table.at(L"Press X") + L" -").c_str(), GetColor(0, 0, 0), font_1);
	is_normal_state = normal_con_f();
	while ((is_normal_state = -1 != ProcessMessage()) && state.update() && !state[KEY_INPUT_X] && !state.esc()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (state.esc()) throw normal_exit();
	return Status::TITLE;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
