#pragma once
#include <string>
#include <utility>
#include <array>
#include <cstdint>
#include "util_INT2_t_calc.h"
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
	explicit DxGHandle(INT2_t size) DxHANDLE_NOEXCEPT ;
	explicit DxGHandle(DxGHandle_t GrHandle) DxHANDLE_NOEXCEPT;
	DxGHandle(const DxGHandle& o) NOEXCEPT : GrHandle(o.GrHandle) {}
	explicit DxGHandle(DxGHandle&& o) NOEXCEPT : GrHandle(o.GrHandle) {}
	int DrawGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT;
	int DrawGraph(INT2_t p, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawTurnGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawTurnGraph(INT2_t p, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawExtendGraph(int x1, int y1, int x2, int y2, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawExtendGraph(INT2_t p1, INT2_t p2, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(int x, int y, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(INT2_t p, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(int x, int y, int cx, int cy, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(INT2_t p, INT2_t c, double ExtRate, double Angle, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, bool TransFlag, int TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRotaGraph(INT2_t p, INT2_t c, std::pair<double, double> ExtRate, double Angle, bool TransFlag, int TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawModiGraph(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawModiGraph(std::array<INT2_t, 4> p, bool TransFlag) const DxHANDLE_NOEXCEPT ;
	int DrawRectGraph(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	int DrawRectGraph(INT2_t Dest, INT2_t Src, INT2_t coord, bool TransFlag, bool TurnFlag = false) const DxHANDLE_NOEXCEPT ;
	DxGHandle DerivationGraph(int SrcX, int SrcY, int Width, int Height) const DxHANDLE_NOEXCEPT ;
	DxGHandle DerivationGraph(INT2_t Src, INT2_t coord) const DxHANDLE_NOEXCEPT ;
	int GetGraphSize(int *SizeXBuf, int *SizeYBuf) const DxHANDLE_NOEXCEPT ;
	INT2_t GetGraphSize() const DxHANDLE_NOEXCEPT ;
	INT2_t GetRelativeGraphCenter() const DxHANDLE_NOEXCEPT;
	int filter_mono(int16_t Cr, int16_t Cb);
	int filter_gaussian(uint16_t PixelWidth, int Param);
	int filter_down_scale(uint8_t DivNum);
	int filter_bright_clip(bright_clip_mode clipmode, uint8_t clip_pram, unsigned int fillcolor, uint8_t fillalpha);
	int filter_HSB(bool HueType, int16_t Hue, int Saturation, int16_t Bright);
	int filter_invert();
	int filter_level(uint8_t min, uint8_t max, int Gamma, uint8_t Aftermin, uint8_t Aftermax);
	int filter_two_color(uint8_t threshold, unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha);
	//int filter_two_color_algolithm_otu(unsigned int LowColor, unsigned int HighColor);
	DxGHandle_t get_raw() const NOEXCEPT { return this->GrHandle; }
private:
	DxGHandle_t GrHandle;
};
DxGHandle make_gradation_graph_handle(unsigned int base_color, bool trans_flag = false);
