#include "config.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <codecvt>
#include <stdexcept>
#include <type_traits>
#include <fstream>
#include "make_array.hpp"
#include "char_convert.hpp"

std::unordered_map<std::wstring, std::wstring> load_lang(const std::string& lang_json_path) {
	boost::property_tree::wptree pt;
	static_assert(sizeof(wchar_t) == 2, "In function load_config, wchar_t is not UTF16.");
	//UTF-8 -> UTF16(wchar_t in Windows.)
	boost::property_tree::read_json(lang_json_path, pt, std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>()));
	auto str_table = std_future::make_array(L"Don't Push Game", L"I did it!", L"Press X", L"Press Z", L"Press Z when it is decided");
	std::unordered_map<std::wstring, std::wstring> re;
	re.reserve(str_table.size());
	for (auto& p : pt) {
		for (auto s : str_table) {
			if (s == p.first) {
				re[s] = p.second.data();
			}
		}
	}
	return re;
}

config_info load_config(const std::string & config_json_path)
{
	boost::property_tree::wptree pt;
	static_assert(sizeof(wchar_t) == 2, "In function load_config, wchar_t is not UTF16.");
	//UTF-8 -> UTF16(wchar_t in Windows.)
	boost::property_tree::read_json(config_json_path, pt, std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>()));
	config_info re{};
	for (auto& p : pt) {
		if (L"current_lang" == p.first) {
			const auto lang_json_path = config_json_path.substr(0, config_json_path.find_last_of("\\/")) + char_cvt::utf_16_to_shift_jis(p.second.data());
			re.lang_str = load_lang(lang_json_path);
		}
	}
	return re;
}
