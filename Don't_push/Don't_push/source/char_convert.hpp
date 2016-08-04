#ifndef CHAR_CONVERT_INC_ARITHMETIC_CHAR_CONVERT_HPP_
#define CHAR_CONVERT_INC_ARITHMETIC_CHAR_CONVERT_HPP_
#include <codecvt>
#include <string>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif //NOMINMAX
#	if !defined(CINTERFACE) && defined(__c2__) &&  __clang_major__ == 3 && __clang_minor__ == 8
//To avoid compile error
//C:\Program Files (x86)\Windows Kits\8.1\Include\um\combaseapi.h(229,21): error : unknown type name 'IUnknown'
//          static_cast<IUnknown*>(*pp);    // make sure everyone derives from IUnknown
#		define CINTERFACE
#	endif
#include <windows.h>
#include <cstring>
namespace char_cvt {
	inline std::wstring shift_jis_to_utf_16(const std::string& str)
	{
		static_assert(sizeof(wchar_t) == 2, "this functon is windows only");
		const int len = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
		std::wstring re(len * 2 + 2, L'\0');
		if (!::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &re[0], len)) {
			const auto ec = ::GetLastError();
			switch (ec)
			{
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			case ERROR_NO_UNICODE_TRANSLATION:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_NO_UNICODE_TRANSLATION"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
			}
		}
		const std::size_t real_len = std::wcslen(re.c_str());
		re.resize(real_len);
		re.shrink_to_fit();
		return re;
	}
	inline std::string utf_16_to_shift_jis(const std::wstring& str) {
		static_assert(sizeof(wchar_t) == 2, "this functon is windows only");
		const int len = ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string re(len * 2, '\0');
		if (!::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, &re[0], len, nullptr, nullptr)) {
			const auto ec = ::GetLastError();
			switch (ec)
			{
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
			}
		}
		const std::size_t real_len = std::strlen(re.c_str());
		re.resize(real_len);
		re.shrink_to_fit();
		return re;
	}
}
#endif
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER <= 190023506
#include <algorithm>
namespace char_cvt {
	namespace detail {
		inline std::basic_string<__int32> u32_to_int32_string(const std::u32string& s) {
			std::basic_string<__int32> re;
			re.resize(s.size());
			std::copy(s.begin(), s.end(), re.begin());
			return re;
		}
		inline std::u32string int32_to_u32_string(const std::basic_string<__int32>& s) {
			std::u32string re;
			re.resize(s.size());
			std::copy(s.begin(), s.end(), re.begin());
			return re;
		}
		inline std::basic_string<__int16> u16_to_int16_string(const std::u16string& s) {
			std::basic_string<__int16> re;
			re.resize(s.size());
			std::copy(s.begin(), s.end(), re.begin());
			return re;
		}
		inline std::u16string int16_to_u16_string(const std::basic_string<__int16>& s) {
			std::u16string re;
			re.resize(s.size());
			std::copy(s.begin(), s.end(), re.begin());
			return re;
		}
	}
}
#endif

namespace char_cvt {
	inline std::string u32tou8(const std::u32string& s) {
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER <= 190023506
		std::wstring_convert<std::codecvt_utf8<__int32>, __int32> u8u32cvt;
		return u8u32cvt.to_bytes(detail::u32_to_int32_string(s));
#else
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u8u32cvt;
		return u8u32cvt.to_bytes(s);
#endif
	}
	inline std::u32string u8tou32(const std::string& s) {
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER <= 190023506
		std::wstring_convert<std::codecvt_utf8<__int32>, __int32> u8u32cvt;
		return detail::int32_to_u32_string(u8u32cvt.from_bytes(s));
#else
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u8u32cvt;
		return u8u32cvt.from_bytes(s);
#endif
	}
	inline std::string u16tou8(const std::u16string& s) {
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER <= 190023506
		std::wstring_convert<std::codecvt_utf8_utf16<__int16>, __int16> u8u16cvt;
		return u8u16cvt.to_bytes(detail::u16_to_int16_string(s));
#else
		std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> u8u16cvt;
		return u8u16cvt.to_bytes(s);
#endif
	}
	inline std::u16string u8tou16(const std::string& s) {
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER <= 190023506
		std::wstring_convert<std::codecvt_utf8_utf16<__int16>, __int16> u8u16cvt;
		return detail::int16_to_u16_string(u8u16cvt.from_bytes(s));
#else
		std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> u8u16cvt;
		return u8u16cvt.from_bytes(s);
#endif
	}
}
#endif //CHAR_CONVERT_INC_ARITHMETIC_CHAR_CONVERT_HPP_