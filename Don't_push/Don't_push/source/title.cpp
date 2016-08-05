#include "title.h"
#include "DxLib.h"
#include "define.h"
#include "Dxkeystate.h"
#include <chrono>
#include <thread>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
main_status title(const img_arr_t&, const sound_arr_t& sound, const config_info::lang_table_t& lang_table) {
	sound.at(_T("title")).play(DxSoundMode::LOOP);//p0052r0のscope_exitがほしい
	//フォントの定義
	static const int font_title = CreateFontToHandle(nullptr, 70, 5, DX_FONTTYPE_EDGE);        //タイトルロゴ
	static const int font_1     = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Zキーを押してね」の奴
	keystate state;
	auto normal_con_f = []() -> bool { 
		bool re = -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen();
		if(!re) throw std::runtime_error("ProcessMessage() return -1.");
		return re;
	};
	bool is_normal_state = normal_con_f();
	DrawBox(0, 0, WINDOW.width, WINDOW.height, GetColor(100, 180, 250), true);	//背景
	DrawStringToHandle(100 + 5, WINDOW.height / 3 + 5, L"D...DON'T PUSH!!", GetColor(255, 255, 255), font_title);		//タイトル（影）
	DrawStringToHandle(100, WINDOW.height / 3, L"D...DON'T PUSH!!", GetColor(0, 0, 0), font_title);					//タイトル
	DrawStringToHandle(260, WINDOW.height - (WINDOW.height / 3), (L"- " + lang_table.at(L"Press Z") + L" -").c_str(), GetColor(0, 0, 0), font_1); //Zキー押してね
	is_normal_state = normal_con_f();
	while (state.update() && !state[KEY_INPUT_Z] && !state.esc() && (is_normal_state = -1 != ProcessMessage())) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	sound.at(_T("title")).stop();
	if (state.esc()) throw normal_exit();
	return main_status::game_preprocess;
	//return main_status::HELICOPTER_ANIMATION;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
