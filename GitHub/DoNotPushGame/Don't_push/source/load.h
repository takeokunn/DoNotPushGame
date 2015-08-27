#pragma once
#include "DxGraphicHandle.h"
#include <unordered_map>
#include<string>
std::unordered_map<std::string, DxGHandle> make_image_array(const std::string& path);
