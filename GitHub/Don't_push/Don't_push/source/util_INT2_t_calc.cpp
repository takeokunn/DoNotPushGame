#include "util_INT2_t_calc.h"
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
