#	if !defined(CINTERFACE) && defined(__c2__) &&  __clang_major__ == 3 && __clang_minor__ == 8
//To avoid compile error
//C:\Program Files (x86)\Windows Kits\8.1\Include\um\combaseapi.h(229,21): error : unknown type name 'IUnknown'
//          static_cast<IUnknown*>(*pp);    // make sure everyone derives from IUnknown
#		define CINTERFACE
#	endif
#include "DxLib.h"
#include "define.h"
#include "load.h"
#include "Dxkeystate.h"
#include "game_preprocess.h"
#include "game.h"
#include "title.h"
#include "continue.h"
#include "end.h"
#include "config.h"
#include "ending_animation.h"
#include <exception>
//初期化関数
int init(const config_info::lang_table_t& lang_table){
	SetMainWindowText(lang_table.at(L"Don't Push Game").c_str());
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WINDOW.width, WINDOW.height, 16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(255, 255, 255);
	if (DxLib_Init() == -1)return -1;// エラーが起きたら直ちに終了
	//SetTransColor(0, 0, 254);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	return 0;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//変数定義------------------------------------------------------

	main_status status_ = main_status::title;

	//処理-----------------------------------------------------------

	try{
		auto config = load_config("assets/config.json");
		init(config.lang_str);
		game_c game({ WINDOW.width * 57 / 256 , WINDOW.height * 2 / 7 }, { WINDOW.width * 71 / 128 , WINDOW.height * 2 / 7 }, config.lang_str);//棒人形A, 棒人形B
		try {
			while (main_status::exit != status_ && -1 != ProcessMessage()) {
				switch (status_)
				{
				case main_status::title:
					status_ = title(game.get_img(), game.get_sound(), config.lang_str);//title BGM流す。この中でBGM止める
					break;
				case main_status::game_preprocess:
					status_ = game_preprocess();
					break;
				case main_status::game_main:
					status_ = game.game_main();//BGM流し始め
					break;
				case main_status::end:
					status_ = end(game.get_img(), game.get_sound(), config.lang_str);//ここでGAMEで流れだした音楽を止める
					break;
				case main_status::flying_mare_animation:
					break;
				case main_status::car_animation:
					break;
				case main_status::helicopter_animation:
					status_ = game.helicopter_event();
					break;
				case main_status::result_echo:
					status_ = game.echo_score();
					break;
				case main_status::gameover:
					status_ = game.echo_game_over();
					break;
				case main_status::game_continue:
					status_ = continu(game.get_img(), game.get_sound(), config.lang_str);//ここでGAMEで流れだした音楽を止める
					break;
				case main_status::exit:
					break;
				default:
					DxLib_End();
					return -1;
					break;
				}
				ScreenFlip();//裏画面表示
			}
		}
		catch (const normal_exit&) {
		}
		for (auto& s : game.get_sound()) s.second.stop();//BGM全部停止
		ending(game.get_sound());
	}
	catch (const std::exception&){
		DxLib_End();
		return -1;
	}
	DxLib_End();
	return 0;   
}
