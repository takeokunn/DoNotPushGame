#include "load.h"
class make_DxGHandle_pair{
public:
	make_DxGHandle_pair(const std::string& path_) : path(path_) {}
	make_DxGHandle_pair(std::string&& path_) : path(path_) {}
	std::pair<std::string, DxGHandle> operator() (const std::string& name, const char* ext = "png"){
		return make_pair(name, DxGHandle(this->path + name + "." + ext));
	}
private:
	std::string path;
};
img_arr_t make_image_array() {
	img_arr_t re;
	make_DxGHandle_pair img("assets\\img\\");
	re.insert(img("bouninngennA"));
	re.insert(img("bouninngennA_fall"));
	re.insert(img("bouninngennB"));
	re.insert(img("bouninngennB_fall"));
	re.insert(img("gake"));
	re.insert(img("herikoputa-"));
	re.insert(img("hunn"));
	re.insert(img("kunai"));
	re.insert(img("kuruma"));
	re.insert(img("seoinage"));
	re.insert(img("tori"));
	re.insert(img("Presentation1"));
	re.insert(img("back_str"));
	re.insert(img("game_main_gauge_bg"));
	return re;
}
class make_DxSHandle_pair {
public:
	make_DxSHandle_pair(const std::string& path_) : path(path_) {}
	make_DxSHandle_pair(std::string&& path_) : path(path_) {}
	std::pair<std::string, DxSHandle> operator() (const std::string& name, const char* ext = "wav") {
		return make_pair(name, DxSHandle(this->path + name + "." + ext));
	}
private:
	std::string path;
};
sound_arr_t make_sound_array() {
	sound_arr_t re;
	make_DxSHandle_pair sound("assets\\music\\");
	re.insert(sound("flower garden"));
	re.insert(sound("title"));
	return re;
}