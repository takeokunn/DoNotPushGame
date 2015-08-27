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
std::unordered_map<std::string, DxGHandle> make_image_array(const std::string& path){

	std::unordered_map<std::string, DxGHandle> rtn;
	make_DxGHandle_pair img((path.back() == '\\') ? path : path + '\\');
	rtn.insert(img("title"));
	rtn.insert(img("game"));
	rtn.insert(img("end"));
	return rtn;
}
