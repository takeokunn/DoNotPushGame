#pragma once
#include <string>
#include <utility>
#include <array>
#ifndef DISABLE_DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_WRAP_USE_EXCEPTION//throwする
#endif
#include "util_noexcept.h"

typedef std::pair<int, int> INT2_t;
class DxGHandle
{
public:
	typedef int DxGHandle_t;
	DxGHandle() NOEXCEPT : GrHandle(-1) {}
	DxGHandle(const std::string& FileName) DxHANDLE_NOEXCEPT;
	DxGHandle(int SizeX, int SizeY) DxHANDLE_NOEXCEPT ;
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
	DxGHandle_t get_raw() const NOEXCEPT { return this->GrHandle; }
private:
	DxGHandle_t GrHandle;
};
