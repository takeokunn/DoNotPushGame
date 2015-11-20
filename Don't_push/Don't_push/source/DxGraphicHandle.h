#pragma once
#include <string>
#include <utility>
#include <array>
#include <cstdint>
#include <dxlibex/basic_types.hpp>
#include "config.h"
#include "util_noexcept.h"
enum class bright_clip_mode : int {
	LESS,
	GREATER
};
class DxGHandle
{
public:
	typedef int DxGHandle_t;
	DxGHandle() NOEXCEPT : GrHandle(-1) {}
	DxGHandle(int SizeX, int SizeY) DxHANDLE_NOEXCEPT ;
	explicit DxGHandle(const char* FileName) DxHANDLE_NOEXCEPT;
	explicit DxGHandle(const std::string& FileName) DxHANDLE_NOEXCEPT;
	explicit DxGHandle(dxle::pointi size) DxHANDLE_NOEXCEPT ;
	explicit DxGHandle(DxGHandle_t GrHandle) DxHANDLE_NOEXCEPT;
	DxGHandle(const DxGHandle& o) NOEXCEPT : GrHandle(o.GrHandle) {}
	explicit DxGHandle(DxGHandle&& o) NOEXCEPT : GrHandle(o.GrHandle) {}
	int DrawGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT;
	int DrawGraph(dxle::pointi p, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawTurnGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawTurnGraph(dxle::pointi p, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawExtendGraph(int x1, int y1, int x2, int y2, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawExtendGraph(dxle::pointi p1, dxle::pointi p2, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(int x, int y, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(dxle::pointi p, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(int x, int y, int cx, int cy, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(dxle::pointi p, dxle::pointi c, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, bool TransFlag, int TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(dxle::pointi p, dxle::pointi c, std::pair<double, double> ExtRate, double Angle, bool TransFlag, int TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawModiGraph(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawModiGraph(std::array<dxle::pointi, 4> p, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawRectGraph(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRectGraph(dxle::pointi Dest, dxle::pointi Src, dxle::pointi coord, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	DxGHandle DerivationGraph(int SrcX, int SrcY, int Width, int Height) const DxHANDLE_NOEXCEPT ;
	DxGHandle DerivationGraph(dxle::pointi Src, dxle::pointi coord) const DxHANDLE_NOEXCEPT ;
	int GetGraphSize(int *SizeXBuf, int *SizeYBuf) const DxHANDLE_NOEXCEPT ;
	dxle::pointi GetGraphSize() const DxHANDLE_NOEXCEPT ;
	dxle::pointi GetRelativeGraphCenter() const DxHANDLE_NOEXCEPT;
	int filter_mono(int16_t Cb, int16_t Cr)DxHANDLE_NOEXCEPT;
	int filter_gaussian(uint16_t PixelWidth, int Param)DxHANDLE_NOEXCEPT;
	int filter_down_scale(uint8_t DivNum)DxHANDLE_NOEXCEPT;
	int filter_bright_clip(bright_clip_mode clipmode, uint8_t clip_pram, unsigned int fillcolor, uint8_t fillalpha)DxHANDLE_NOEXCEPT;
	int filter_HSB(bool HueType, int16_t Hue, int Saturation, int16_t Bright)DxHANDLE_NOEXCEPT;
	int filter_invert()DxHANDLE_NOEXCEPT;
	int filter_level(uint8_t min, uint8_t max, int Gamma, uint8_t Aftermin, uint8_t Aftermax)DxHANDLE_NOEXCEPT;
	int filter_two_color(uint8_t threshold, unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha)DxHANDLE_NOEXCEPT;
	int filter_two_color(uint8_t threshold, unsigned int LowColor, unsigned int HighColor) DxHANDLE_NOEXCEPT;
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	int filter_two_color_algolithm_otu(unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha) DxHANDLE_NOEXCEPT;
	int filter_two_color_algolithm_otu(unsigned int LowColor, unsigned int HighColor) DxHANDLE_NOEXCEPT;
#endif
	int filter_gradient_map(const DxGHandle& MapGrHandle, bool Reverse_flag = false)DxHANDLE_NOEXCEPT;
	int filter_gradient_map(unsigned int base_color, bool Reverse_flag = false)DxHANDLE_NOEXCEPT;
	DxGHandle_t get_raw() const NOEXCEPT { return this->GrHandle; }
private:
	DxGHandle_t GrHandle;
};
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
uint8_t calc_threshold_algolithm_otu(const DxGHandle& handle);
#endif
DxGHandle make_gradation_graph_handle(unsigned int base_color, bool trans_flag = false) NOEXCEPT;

enum class filter_type {
	mono,
	gaussian,
	down_scale,
	bright_clip,
	HSB,
	invert,
	level,
	gradient_map,
	two_color,
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	two_color_algolithm_otu,
#endif
};

template<filter_type f_type> class filter {
};
template<> class filter<filter_type::mono> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(int16_t Cb, int16_t Cr) {
		return this->handle_.filter_mono(Cb, Cr);
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::gaussian> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(uint16_t PixelWidth, int Param) {
		return this->handle_.filter_gaussian(PixelWidth, Param);
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::down_scale> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(uint8_t DivNum) {
		return this->handle_.filter_down_scale(DivNum);
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::bright_clip> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(bright_clip_mode clipmode, uint8_t clip_pram, unsigned int fillcolor, uint8_t fillalpha) {
		return this->handle_.filter_bright_clip(clipmode, clip_pram, fillcolor, fillalpha);
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::HSB> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(bool HueType, int16_t Hue, int Saturation, int16_t Bright) {
		return this->handle_.filter_HSB(HueType, Hue, Saturation, Bright);
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::invert> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()() {
		return this->handle_.filter_invert();
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::level> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(uint8_t min, uint8_t max, int Gamma, uint8_t Aftermin, uint8_t Aftermax) {
		return this->handle_.filter_level(min, max, Gamma, Aftermin, Aftermax);
	}
private:
	DxGHandle& handle_;
};
template<> class filter<filter_type::two_color> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(uint8_t threshold, unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha) {
		return this->handle_.filter_two_color(threshold, LowColor, LowAlpha, HighColor, HighAlpha);
	}
	int operator()(uint8_t threshold, unsigned int LowColor, unsigned int HighColor) {
		return this->handle_.filter_two_color(threshold, LowColor, HighColor);
	}
private:
	DxGHandle& handle_;
};

template<> class filter<filter_type::gradient_map> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(const DxGHandle& MapGrHandle, bool Reverse_flag = false) {
		return this->handle_.filter_gradient_map(MapGrHandle, Reverse_flag);
	}
	int operator()(unsigned int base_color, bool Reverse_flag = false) {
		return this->handle_.filter_gradient_map(base_color, Reverse_flag);
	}
private:
	DxGHandle& handle_;
};

#ifdef DxHANDLE_WRAP_USE_EXCEPTION
template<> class filter<filter_type::two_color_algolithm_otu> {
public:
	explicit filter(DxGHandle& handle) : handle_(handle) {}
	int operator()(unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha) {
		return this->handle_.filter_two_color_algolithm_otu(LowColor, LowAlpha, HighColor, HighAlpha);
	}
	int operator()(unsigned int LowColor, unsigned int HighColor) {
		return this->handle_.filter_two_color_algolithm_otu(LowColor, HighColor);
	}
private:
	DxGHandle& handle_;
};
#endif
