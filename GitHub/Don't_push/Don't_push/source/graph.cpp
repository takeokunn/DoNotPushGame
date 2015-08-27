#include "graph.h"
#include "DxLib.h"
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
#include <stdexcept>
class DxGHandle_runtime_error : public std::runtime_error {
public:
	explicit DxGHandle_runtime_error(const std::string& what_arg) : std::runtime_error("DxGHandle_runtime_error_runtime_error : " + what_arg) {}
	explicit DxGHandle_runtime_error(const char* what_arg) : std::runtime_error(std::string("DxGHandle_runtime_error_runtime_error : ") + what_arg) {}
};
#endif
DxGHandle::DxGHandle(const std::string & FileName) DxHANDLE_NOEXCEPT{
	this->GrHandle = LoadGraph(FileName.c_str());
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
}

DxGHandle::DxGHandle(int SizeX, int SizeY) DxHANDLE_NOEXCEPT{
	this->GrHandle = MakeGraph(SizeX, SizeY);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("‰æ‘œƒnƒ“ƒhƒ‹‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
}

DxGHandle::DxGHandle(INT2_t size) DxHANDLE_NOEXCEPT{
	this->GrHandle = MakeGraph(size.first, size.second);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("‰æ‘œƒnƒ“ƒhƒ‹‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
}

DxGHandle::DxGHandle(int GrHandle) DxHANDLE_NOEXCEPT{
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == GrHandle) throw DxGHandle_runtime_error("‰æ‘œƒnƒ“ƒhƒ‹‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	this->GrHandle = GrHandle;
}

int DxGHandle::DrawGraph(int x, int y, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawGraph(x, y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawGraph(INT2_t p, bool TransFlag) {
	const auto re = DxLib::DrawGraph(p.first, p.second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawTurnGraph(int x, int y, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawTurnGraph(x, y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawTurnGraph(INT2_t p, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawTurnGraph(p.first, p.second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawExtendGraph(int x1, int y1, int x2, int y2, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawExtendGraph(x1, y1, x2, y2, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚ÌŠg‘åk¬•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawExtendGraph(INT2_t p1, INT2_t p2, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawExtendGraph(p1.first, p1.second, p2.first, p2.second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚ÌŠg‘åk¬•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRotaGraph(x, y, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‰ñ“]•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(INT2_t p, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRotaGraph(p.first, p.second, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‰ñ“]•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, int cx, int cy, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRotaGraph2(x, y, cx, cy, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‰ñ“]•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(INT2_t p, INT2_t c, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRotaGraph2(p.first, p.second, c.first, c.second, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‰ñ“]•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, bool TransFlag, int TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‰ñ“]•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(INT2_t p, INT2_t c, std::pair<double, double> ExtRate, double Angle, bool TransFlag, int TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRotaGraph3(p.first, p.second, c.first, c.second, ExtRate.first, ExtRate.second, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‰ñ“]•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawModiGraph(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚ÌŽ©—R•ÏŒ`•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawModiGraph(std::array<INT2_t, 4> p, bool TransFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawModiGraph(p[0].first, p[0].second, p[1].first, p[1].second, p[2].first, p[2].second, p[3].first, p[3].second, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚ÌŽ©—R•ÏŒ`•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}
int DxGHandle::DrawRectGraph(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, bool TransFlag, bool TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì•”•ª•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

int DxGHandle::DrawRectGraph(INT2_t Dest, INT2_t Src, INT2_t coord, bool TransFlag, bool TurnFlag) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::DrawRectGraph(Dest.first, Dest.second, Src.first, Src.second, coord.first, coord.second, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì•”•ª•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

DxGHandle DxGHandle::DerivationGraph(int SrcX, int SrcY, int Width, int Height) DxHANDLE_NOEXCEPT{
	return DxGHandle(DxLib::DerivationGraph(SrcX, SrcY, Width, Height, this->GrHandle));
}

DxGHandle DxGHandle::DerivationGraph(INT2_t Src, INT2_t coord) DxHANDLE_NOEXCEPT{
	return DxGHandle(DxLib::DerivationGraph(Src.first, Src.second, coord.first, coord.second, this->GrHandle));
}

int DxGHandle::GetGraphSize(int * SizeXBuf, int * SizeYBuf) DxHANDLE_NOEXCEPT{
	const auto re = DxLib::GetGraphSize(this->GrHandle, SizeXBuf, SizeYBuf);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("‰æ‘œ‚Ì‘å‚«‚³‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
#endif
	return re;
}

std::pair<int, int> DxGHandle::GetGraphSize() DxHANDLE_NOEXCEPT{
	std::pair<int, int> re;
	return (0 == this->GetGraphSize(&re.first, &re.second)) ? re : std::pair<int, int>();
}