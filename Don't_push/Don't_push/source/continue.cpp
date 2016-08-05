#include "continue.h"
#include "Dxkeystate.h"
#include <dxlibex/graph2d.hpp>
#include "DxLib.h"
#include <array>
#include <algorithm>
#include <thread>
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
main_status continu(const img_arr_t&, const sound_arr_t& sound, const config_info::lang_table_t& lang_table) {
	for (auto& s : sound) s.second.stop();//BGM全部停止
	const auto Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);//選択肢表示の文字
	DXLE_STATIC_CONSTEXPR std::array<dxle::pointi, 2> select = { {{WINDOW.width * 13 / 40, WINDOW.height / 4}, { WINDOW.width * 13 / 40, WINDOW.height / 4 + 100 }} };
	const std::array<dxle::screen, 2> screens = { { 
			std::move(dxle::MakeScreen(WINDOW).draw_on_this([Font_1, &lang_table]() {
				const auto color = GetColor(0, 0, 0);
				DrawBox(0, 0, WINDOW.width, WINDOW.height, GetColor(180, 180, 180), TRUE);	//背景
				DrawStringToHandle(select[0].x + 40, select[0].y, L"CONTINUE !!", color, Font_1);//CONTINUE
				DrawStringToHandle(select[1].x, select[1].y, L"RETIRE. . .", GetColor(255, 255, 255), Font_1);//RETIRE
				DrawBox(180, 155, 200, 175, color, TRUE);	//選択してるのが分かるようにするやつ
				DrawStringToHandle(120, WINDOW.height * 3 / 4, (L"- " + lang_table.at(L"Press Z when it is decided") + L" -").c_str(), GetColor(0, 0, 0), Font_1);//Zキー押してね
			})),
			std::move(dxle::MakeScreen(WINDOW).draw_on_this([Font_1, &lang_table]() {
				const auto color_black = GetColor(0, 0, 0);
				DrawBox(0, 0, WINDOW.width, WINDOW.height, GetColor(180, 180, 180), TRUE);	//背景
				DrawStringToHandle(select[0].x, select[0].y, L"CONTINUE !!", GetColor(255, 255, 255), Font_1);//CONTINUE
				DrawStringToHandle(select[1].x + 40, select[1].y, L"RETIRE. . .", color_black, Font_1);//RETIRE
				DrawBox(180, 255, 200, 275, color_black, TRUE);	//選択してるのが分かるようにするやつ
				DrawStringToHandle(120, WINDOW.height * 3 / 4, (L"- " + lang_table.at(L"Press Z when it is decided") + L" -").c_str(), GetColor(0, 0, 0), Font_1);//Zキー押してね
			}))
	} };
	bool flag_no_continue = false;		//コンティニューするかどうか

	//メインループ
	keystate state;
	auto normal_con_f = []() -> bool {
		bool re = -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen();
		if (!re) throw std::runtime_error("ProcessMessage() return -1.");
		return re;
	};
	bool is_normal_state = normal_con_f();
	screens[flag_no_continue].DrawGraph({}, false);
	is_normal_state = normal_con_f();
	while ((is_normal_state = -1 != ProcessMessage()) && state.update() && !state[KEY_INPUT_Z] && !state.esc()) {
		//十字キー受付
		if ((state.up() & flag_no_continue) || (state.down() & !flag_no_continue)){
			flag_no_continue = !flag_no_continue;
			screens[flag_no_continue].DrawGraph({}, false);//描画
			if (!(is_normal_state = normal_con_f())) break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(40));//sleepさせるとCPU使用率が下がる
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	if (state.esc()) throw normal_exit();
	return (flag_no_continue) ? main_status::title : main_status::game_preprocess;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
