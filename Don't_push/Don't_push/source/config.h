#pragma once
#include <unordered_map>
#include <string>
struct config_info {
	config_info() = default;
	config_info(const config_info&) = default;
	config_info(config_info&& o) : lang_str(o.lang_str) {}
	config_info& operator=(const config_info&) = default;
	config_info& operator=(config_info&& o) {
		this->lang_str = std::move(o.lang_str);
		return *this;
	}
	std::unordered_map<std::wstring, std::wstring> lang_str;
};

config_info load_config(const std::string& config_json_path);
