#pragma once
#include <utility>
typedef std::pair<int, int> INT2_t;
const INT2_t operator+(const INT2_t& l, const INT2_t& r);
const INT2_t operator-(const INT2_t& l, const INT2_t& r);
const INT2_t operator*(const INT2_t& l, const int r);
const INT2_t operator/(const INT2_t& l, const int r);
const INT2_t& operator+=(INT2_t& l, const INT2_t& r);
const INT2_t& operator-=(INT2_t& l, const INT2_t& r);
