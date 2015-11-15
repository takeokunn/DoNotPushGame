﻿#include "DxLib.h"
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
	SetMainWindowText("アプリケーション");
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
		auto img_arr = make_image_array();
		auto status_img = make_status_image_array();
		auto sound_arr = make_sound_array();
		while (Status::EXIT != status_ && -1 != ProcessMessage()){
			switch (status_)
			{
			case Status::TITLE:
				status_ = title(img_arr, sound_arr);//title BGM流す。この中でBGM止める
				break;
			case Status::GAME:
				status_ = game(img_arr, sound_arr);//BGM流し始め
				break;
			case Status::END:
				status_ = end(img_arr, sound_arr);//ここでGAMEで流れだした音楽を止める
				break;
			case Status::FLYING_MARE_ANIMATION:
				break;
			case Status::CAR_ANIMATION:
				break;
			case Status::HELICOPTER_ANIMATION:
				break;
			case Status::CONTINUE:
				status_ = continu(img_arr, sound_arr);//ここでGAMEで流れだした音楽を止める
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
	catch (std::exception&){
		DxLib_End();
		return -1;
	}

	//終了処理--------------------------------------------------------------

	DxLib_End();

	return 0;   
}
