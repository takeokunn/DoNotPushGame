#include "load.h"
constexpr size_t WINDOW_WIDTH = 640;
constexpr size_t WINDOW_HEIGHT = 480;
//状態管理
enum class Status{
	TITLE,
	GAME,
	END,
	EXIT
};
using img_arr_t = std::unordered_map < std::string, DxGHandle >;
