#pragma once
#include <array>
#ifndef DISABLE_DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_WRAP_USE_EXCEPTION//throwする
#endif
#include "util_noexcept.h"
#include "util_constexpr.h"

class keystate
{
public:
	void update() NOEXCEPT;
	int operator[](size_t n) const NOEXCEPT;
	int at(size_t n) const NOEXCEPT;
	bool shift() const NOEXCEPT;
	bool lshift() const NOEXCEPT;
	bool rshift() const NOEXCEPT;
	bool ctrl() const NOEXCEPT;
	bool lctrl() const NOEXCEPT;
	bool rctrl() const NOEXCEPT;
	bool esc() const NOEXCEPT;
	bool right() const NOEXCEPT;
	bool up() const NOEXCEPT;
	bool left() const NOEXCEPT;
	bool down() const NOEXCEPT;
	bool enter() const NOEXCEPT;
	bool space() const NOEXCEPT;
	static CONSTEXPR_OR_CONST size_t keybufsize = 256;
private:
	std::array<int, keybufsize> keystatebuf = {};
};
bool operator!=(const keystate& l, size_t r);
inline bool operator!=(size_t l, const keystate& r) {
	return r != l;
}
inline bool operator==(const keystate& l, size_t r) {
	return !(l != r);
}
inline bool operator==(size_t l, const keystate& r) {
	return !(l != r);
}