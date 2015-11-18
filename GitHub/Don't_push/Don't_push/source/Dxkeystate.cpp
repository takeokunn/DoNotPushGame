#include "Dxkeystate.h"
#include "DxLib.h"
#include <limits>
#ifdef max
#undef max
#endif
keystate::keystate() NOEXCEPT : keystatebuf() {
	this->fllush_stream();
}

bool keystate::update() NOEXCEPT {
	char buf[keybufsize];
	auto re = GetHitKeyStateAll(buf);
	if (0 != re) return false;
	for (size_t i = 0; i < keybufsize; ++i) {
		if (buf[i] && std::numeric_limits<int>::max() != this->keystatebuf[i]) ++this->keystatebuf[i];
		else this->keystatebuf[i] = 0;
	}
	return true;
}

bool keystate::fllush() {
	this->fllush_stream();
	this->keystatebuf.fill(0);
	return true;
}
bool keystate::fllush_stream() {
	char buf[2][keybufsize] = {};
	for (size_t i = 0; i < this->keystatebuf.size(); ++i) buf[0][i] = 0 != this->keystatebuf[i];
	char* first_p;
	char* last_p;
	size_t i;
	for (first_p = buf[0], last_p = buf[1]; 0 == DxLib::GetHitKeyStateAll(last_p); std::swap(first_p, last_p)) {
		for (i = 0; i < keybufsize && !first_p[i] && !last_p[i]; ++i);
		if (i == keybufsize) break;
	}
	return (i == keybufsize);
}

int keystate::operator[](size_t n) const NOEXCEPT {
	return this->keystatebuf[n];
}

int keystate::at(size_t n) const {
	return this->keystatebuf.at(n);
}
bool keystate::shift() const NOEXCEPT {
	return this->lshift() || this->rshift();
}
bool keystate::lshift() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_LSHIFT];
}
bool keystate::rshift() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_RSHIFT];
}
bool keystate::ctrl() const NOEXCEPT {
	return this->lctrl() || this->rctrl();
}
bool keystate::lctrl() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_LCONTROL];
}
bool keystate::rctrl() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_RCONTROL];
}
bool keystate::esc() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_ESCAPE];
}
bool keystate::right() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_RIGHT];
}
bool keystate::up() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_UP];
}
bool keystate::left() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_LEFT];
}
bool keystate::down() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_DOWN];
}
bool keystate::enter() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_RETURN];
}
bool keystate::space() const NOEXCEPT {
	return 0 != this->keystatebuf[KEY_INPUT_SPACE];
}
bool operator!=(const keystate& l, size_t r) {
	return 0 == l[r];
}
