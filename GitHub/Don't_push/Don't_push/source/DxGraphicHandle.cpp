#include "DxGraphicHandle.h"
#include "DxLib.h"
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
#include "DxHandleException.h"
#endif
DxGHandle::DxGHandle(const std::string & FileName) DxHANDLE_NOEXCEPT {
	this->GrHandle = LoadGraph(FileName.c_str());
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("画像の読み込みに失敗しました");
#endif
}

DxGHandle::DxGHandle(int SizeX, int SizeY) DxHANDLE_NOEXCEPT {
	this->GrHandle = MakeGraph(SizeX, SizeY);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("画像ハンドルの作成に失敗しました");
#endif
}

DxGHandle::DxGHandle(INT2_t size) DxHANDLE_NOEXCEPT {
	this->GrHandle = MakeGraph(size.first, size.second);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("画像ハンドルの作成に失敗しました");
#endif
}

DxGHandle::DxGHandle(DxGHandle_t GrHandle) DxHANDLE_NOEXCEPT {
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == GrHandle) throw DxGHandle_runtime_error("画像ハンドルの作成に失敗しました");
#endif
	this->GrHandle = GrHandle;
}

int DxGHandle::DrawGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawGraph(x, y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawGraph(INT2_t p, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawGraph(p.first, p.second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawTurnGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawTurnGraph(x, y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawTurnGraph(INT2_t p, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawTurnGraph(p.first, p.second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawExtendGraph(int x1, int y1, int x2, int y2, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawExtendGraph(x1, y1, x2, y2, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の拡大縮小描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawExtendGraph(INT2_t p1, INT2_t p2, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawExtendGraph(p1.first, p1.second, p2.first, p2.second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の拡大縮小描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph(x, y, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の回転描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(INT2_t p, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph(p.first, p.second, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の回転描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, int cx, int cy, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph2(x, y, cx, cy, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の回転描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(INT2_t p, INT2_t c, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph2(p.first, p.second, c.first, c.second, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の回転描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, bool TransFlag, int TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の回転描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(INT2_t p, INT2_t c, std::pair<double, double> ExtRate, double Angle, bool TransFlag, int TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph3(p.first, p.second, c.first, c.second, ExtRate.first, ExtRate.second, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の回転描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawModiGraph(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の自由変形描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawModiGraph(std::array<INT2_t, 4> p, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawModiGraph(p[0].first, p[0].second, p[1].first, p[1].second, p[2].first, p[2].second, p[3].first, p[3].second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の自由変形描画に失敗しました");
#endif
	return re;
}
int DxGHandle::DrawRectGraph(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の部分描画に失敗しました");
#endif
	return re;
}

int DxGHandle::DrawRectGraph(INT2_t Dest, INT2_t Src, INT2_t coord, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRectGraph(Dest.first, Dest.second, Src.first, Src.second, coord.first, coord.second, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の部分描画に失敗しました");
#endif
	return re;
}

DxGHandle DxGHandle::DerivationGraph(int SrcX, int SrcY, int Width, int Height) const DxHANDLE_NOEXCEPT {
	return DxGHandle(DxLib::DerivationGraph(SrcX, SrcY, Width, Height, this->GrHandle));
}

DxGHandle DxGHandle::DerivationGraph(INT2_t Src, INT2_t coord) const DxHANDLE_NOEXCEPT {
	return DxGHandle(DxLib::DerivationGraph(Src.first, Src.second, coord.first, coord.second, this->GrHandle));
}

int DxGHandle::GetGraphSize(int * SizeXBuf, int * SizeYBuf) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::GetGraphSize(this->GrHandle, SizeXBuf, SizeYBuf);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("画像の大きさの取得に失敗しました");
#endif
	return re;
}

INT2_t DxGHandle::GetGraphSize() const DxHANDLE_NOEXCEPT {
	INT2_t re;
	return (0 == this->GetGraphSize(&re.first, &re.second)) ? re : INT2_t();
}

INT2_t DxGHandle::GetRelativeGraphCenter() const DxHANDLE_NOEXCEPT{
	return this->GetGraphSize() / 2;
}
