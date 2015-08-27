#pragma once
#include <utility>
typedef std::pair<int, int> INT2_t;
const INT2_t operator+(const INT2_t& l, const INT2_t& r) {
	return INT2_t({ l.first + r.first, l.second + r.second });
}
const INT2_t operator-(const INT2_t& l, const INT2_t& r) {
	return INT2_t({ l.first - r.first, l.second - r.second });
}
const INT2_t operator*(const INT2_t& l, const int r) {
	return INT2_t({ l.first * r, l.second * r });
}
const INT2_t operator/(const INT2_t& l, const int r) {
	return INT2_t({ l.first / r, l.second / r });
}
const INT2_t& operator+=(INT2_t& l, const INT2_t& r) {
	l.first += r.first;
	l.second += r.second;
	return l;
}
const INT2_t& operator-=(INT2_t& l, const INT2_t& r) {
	l.first -= r.first;
	l.second -= r.second;
	return l;
}
