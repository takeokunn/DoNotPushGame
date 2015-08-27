#include "Dxkeystate.h"
#include "DxLib.h"
#include <limits>
#ifdef max
#undef max
#endif
void keystate::update() NOEXCEPT {
	char buf[keybufsize];
	GetHitKeyStateAll(buf);
	for (size_t i = 0; i < keybufsize; ++i) {
		if (buf[i] && std::numeric_limits<int>::max() != this->keystatebuf[i]) ++this->keystatebuf[i];
		else this->keystatebuf[i] = 0;
	}
}

int keystate::operator[](size_t n) const NOEXCEPT {
	return this->keystatebuf[n];
}

int keystate::at(size_t n) const NOEXCEPT {
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
