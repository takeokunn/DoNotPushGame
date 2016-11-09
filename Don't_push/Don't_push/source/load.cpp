#include "load.h"
class make_texture2d_pair{
public:
	make_texture2d_pair(const dxle::tstring& path_) : path(path_) {}
	make_texture2d_pair(dxle::tstring&& path_) : path(path_) {}
	std::pair<dxle::tstring, dxle::texture2d> operator() (const dxle::tstring& name, const TCHAR* ext = _T("png")){
		return make_pair(name, dxle::LoadGraph(this->path + name + _T(".") + ext));
	}
private:
	dxle::tstring path;
};
img_arr_t make_image_array() {
	img_arr_t re;
	make_texture2d_pair img(_T("assets\\img\\"));
	re.insert(img(_T("bouninngennA")));
	re.insert(img(_T("bouninngennA_fall")));
	re.insert(img(_T("bouninngennB")));
	re.insert(img(_T("bouninngennB_fall")));
	re.insert(img(_T("gake")));
	re.insert(img(_T("herikoputa-")));
	re.insert(img(_T("hunn")));
	re.insert(img(_T("kunai")));
	re.insert(img(_T("kuruma")));
	re.insert(img(_T("seoinage")));
	re.insert(img(_T("tori")));
	re.insert(img(_T("Presentation1")));
	re.insert(img(_T("back_str")));
	re.insert(img(_T("game_main_gauge_bg")));
	return re;
}
class make_DxSHandle_pair {
public:
	make_DxSHandle_pair(const dxle::tstring& path_) : path(path_) {}
	make_DxSHandle_pair(dxle::tstring&& path_) : path(path_) {}
	std::pair<dxle::tstring, DxSHandle> operator() (const dxle::tstring& name, const TCHAR* ext = _T("wav")) {
		return make_pair(name, DxSHandle(this->path + name + _T(".") + ext));
	}
private:
	dxle::tstring path;
};
sound_arr_t make_sound_array() {
	sound_arr_t re;
	make_DxSHandle_pair sound(_T("assets\\music\\"));
	re.insert(sound(_T("flower garden")));
	re.insert(sound(_T("title")));
	re.insert(sound(_T("Thank_you_for_playing_en"), _T("ogg")));
	re.insert(sound(_T("Thank_you_for_playing_ja"), _T("ogg")));
	return re;
}