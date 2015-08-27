#pragma once
#include "DxGraphicHandle.h"
#include "DxSoundHandle.h"
#include "define.h"
#include <unordered_map>
#include <string>
img_arr_t make_image_array(const std::string& path);
sound_arr_t make_sound_array(const std::string& path);