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
img_arr_t make_image_array(){
	img_arr_t rtn;
	make_DxGHandle_pair img("assets\\status_img\\");
	rtn.insert(img("title"));
	rtn.insert(img("game"));
	rtn.insert(img("end"));
	return rtn;
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