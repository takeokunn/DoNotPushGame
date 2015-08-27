#pragma once
#include "DxGraphicHandle.h"
#include "DxSoundHandle.h"
#include <unordered_map>
#include <string>
std::unordered_map<std::string, DxGHandle> make_image_array(const std::string& path);
std::unordered_map<std::string, DxSHandle> make_sound_array(const std::string& path);