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

template<typename CharType>void skip_utf8_bom(std::basic_ifstream<CharType>& fs) {
	int dst[3];
	for (auto& i : dst) i = fs.get();
	DXLE_CONSTEXPR int utf8[] = { 0xEF, 0xBB, 0xBF };
	if (!std::equal(std::begin(dst), std::end(dst), utf8)) fs.seekg(0);
}


boost::property_tree::wptree read_json(const std::string& path) {
	std::ifstream file(path);
	if (!file) throw std::runtime_error("fail to read file.");
	skip_utf8_bom(file);
	std::string buf;
	for (std::string tmp; std::getline(file, tmp);) {
		buf += tmp + "\n";
	}
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> cvt;
	std::wstringstream ss;
	ss << cvt.from_bytes(buf);
	boost::property_tree::wptree pt;
	boost::property_tree::read_json(ss, pt);
	return pt;
}
config_info::lang_table_t load_lang(const std::string& lang_json_path) {
	boost::property_tree::wptree pt = read_json(lang_json_path);
	static_assert(sizeof(wchar_t) == 2, "In function load_config, wchar_t is not UTF16.");
	//UTF-8 -> UTF16(wchar_t in Windows.)
	//boost::property_tree::read_json(lang_json_path, pt, std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>()));
	auto str_table = std_future::make_array(L"Don't Push Game", L"I did it!", L"Press X", L"Press Z", L"Press Z when it is decided");
	config_info::lang_table_t re;
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
	boost::property_tree::wptree pt = read_json(config_json_path);
	static_assert(sizeof(wchar_t) == 2, "In function load_config, wchar_t is not UTF16.");
	//UTF-8 -> UTF16(wchar_t in Windows.)
	//boost::property_tree::read_json(config_json_path, pt, std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>()));
	config_info re{};
	for (auto& p : pt) {
		if (L"current_lang" == p.first) {
			const auto lang_json_path = config_json_path.substr(0, config_json_path.find_last_of("\\/")) + "/lang/" + char_cvt::utf_16_to_shift_jis(p.second.data()) + ".json";
			re.lang_str = load_lang(lang_json_path);
		}
	}
	return re;
}
