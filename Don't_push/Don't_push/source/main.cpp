#include "DxLib.h"
#include "DxGraphicHandle.h"
#include "define.h"
#include "load.h"
#include "Dxkeystate.h"
#include "game.h"
#include "title.h"
#include "continue.h"
#include "end.h"
#include <exception>
//初期化関数
int init(){
	SetMainWindowText(L"Don't Push Game.");
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);
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
	init();

	//変数定義------------------------------------------------------

	Status status_ = Status::TITLE;


	//処理-----------------------------------------------------------

	try{
		game_c game({ WINDOW_WIDTH * 57 / 256 , WINDOW_HEIGHT * 2 / 7 }, { WINDOW_WIDTH * 71 / 128 , WINDOW_HEIGHT * 2 / 7 });//棒人形A, 棒人形B
		while (Status::EXIT != status_ && -1 != ProcessMessage()){
			switch (status_)
			{
			case Status::TITLE:
				status_ = title(game.get_img(), game.get_sound());//title BGM流す。この中でBGM止める
				break;
			case Status::GAME:
				status_ = game.game_main();//BGM流し始め
				break;
			case Status::END:
				status_ = end(game.get_img(), game.get_sound());//ここでGAMEで流れだした音楽を止める
				break;
			case Status::FLYING_MARE_ANIMATION:
				break;
			case Status::CAR_ANIMATION:
				break;
			case Status::HELICOPTER_ANIMATION:
				status_ = game.helicopter_event();
				break;
			case Status::RESULT_ECHO:
				status_ = game.echo_score();
				break;
			case Status::GAME_OVER:
				status_ = game.echo_game_over();
				break;
			case Status::CONTINUE:
				status_ = continu(game.get_img(), game.get_sound());//ここでGAMEで流れだした音楽を止める
				break;
			case Status::EXIT:
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
	catch (const std::exception&){
		DxLib_End();
		return -1;
	}
	DxLib_End();
	return 0;   
}
