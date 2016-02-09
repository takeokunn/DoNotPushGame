#include "title.h"
#include "DxLib.h"
#include "define.h"
#include "Dxkeystate.h"

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4706) //warning C4706: 条件式の比較値は、代入の結果になっています。
#endif
Status title(const img_arr_t&, const sound_arr_t& sound) {
	sound.at(_T("title")).play(DxSoundMode::LOOP);//p0052r0のscope_exitがほしい
	//フォントの定義
	const int Font_title = CreateFontToHandle(nullptr, 70, 5, DX_FONTTYPE_EDGE);        //タイトルロゴ
	const int Font_1     = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Zキーを押してね」の奴
	keystate state;
	auto normal_con_f = []() -> bool { 
		return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); 
	};
	bool is_normal_state = true;
	while (state.update() && !state[KEY_INPUT_Z] && !state.esc() && (is_normal_state = normal_con_f())) {
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景
		DrawStringToHandle(100 + 5, WINDOW_HEIGHT / 3 + 5, L"D...DON'T PUSH!!", GetColor(255, 255, 255), Font_title);		//タイトル（影）
		DrawStringToHandle(100, WINDOW_HEIGHT / 3, L"D...DON'T PUSH!!", GetColor(0, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(260, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), L"- Zキーを押してね -", GetColor(0, 0, 0), Font_1); //Zキー押してね
	}
	if (!is_normal_state) throw std::runtime_error("ProcessMessage() return -1.");
	sound.at(_T("title")).stop();
	if (state.esc()) throw normal_exit();
	return Status::GAME;
	//return Status::HELICOPTER_ANIMATION;
}
#ifdef _MSC_VER
#pragma warning (pop)
#endif
