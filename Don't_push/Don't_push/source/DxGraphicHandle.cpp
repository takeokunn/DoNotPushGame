#include "DxGraphicHandle.h"
#include "DxLib.h"
#include "dxlibex/config/defines.h"
#undef max
#undef min
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
#include "DxHandleException.h"
#endif
#include <algorithm>

DxGHandle::DxGHandle(const char * FileName) DxHANDLE_NOEXCEPT {
	this->GrHandle = LoadGraph(FileName);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("Fail to load image.");
#endif
}

DxGHandle::DxGHandle(const std::string & FileName) DxHANDLE_NOEXCEPT : DxGHandle(FileName.c_str()){}//C++11:delegating constructor

DxGHandle::DxGHandle(int SizeX, int SizeY) DxHANDLE_NOEXCEPT {
	this->GrHandle = MakeGraph(SizeX, SizeY);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("Fail to make graphic handle.");
#endif
}

DxGHandle::DxGHandle(dxle::pointi size) DxHANDLE_NOEXCEPT {
	this->GrHandle = MakeGraph(size.x, size.y);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->GrHandle) throw DxGHandle_runtime_error("Fail to make graphic handle.");
#endif
}

DxGHandle::DxGHandle(DxGHandle_t GrHandle) DxHANDLE_NOEXCEPT {
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == GrHandle) throw DxGHandle_runtime_error("Fail to make graphic handle.");
#endif
	this->GrHandle = GrHandle;
}

int DxGHandle::DrawGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawGraph(x, y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawGraph().");
#endif
	return re;
}

int DxGHandle::DrawGraph(dxle::pointi p, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawGraph(p.x, p.y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawGraph().");
#endif
	return re;
}

int DxGHandle::DrawTurnGraph(int x, int y, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawTurnGraph(x, y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawGraph().");
#endif
	return re;
}

int DxGHandle::DrawTurnGraph(dxle::pointi p, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawTurnGraph(p.x, p.y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawTurnGraph().");
#endif
	return re;
}

int DxGHandle::DrawExtendGraph(int x1, int y1, int x2, int y2, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawExtendGraph(x1, y1, x2, y2, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawExtendGraph().");
#endif
	return re;
}

int DxGHandle::DrawExtendGraph(dxle::pointi p1, dxle::pointi p2, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawExtendGraph(p1.x, p1.y, p2.x, p2.y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawExtendGraph().");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph(x, y, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRotaGraph().");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(dxle::pointi p, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph(p.x, p.y, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRotaGraph().");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, int cx, int cy, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph2(x, y, cx, cy, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRotaGraph().");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(dxle::pointi p, dxle::pointi c, double ExtRate, double Angle, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph2(p.x, p.y, c.x, c.y, ExtRate, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRotaGraph().");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, bool TransFlag, int TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRotaGraph().");
#endif
	return re;
}

int DxGHandle::DrawRotaGraph(dxle::pointi p, dxle::pointi c, std::pair<double, double> ExtRate, double Angle, bool TransFlag, int TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRotaGraph3(p.x, p.y, c.x, c.y, ExtRate.first, ExtRate.second, Angle, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRotaGraph().");
#endif
	return re;
}

int DxGHandle::DrawModiGraph(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawModiGraph().");
#endif
	return re;
}

int DxGHandle::DrawModiGraph(std::array<dxle::pointi, 4> p, bool TransFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawModiGraph(p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y, p[3].x, p[3].y, this->GrHandle, TransFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawModiGraph().");
#endif
	return re;
}
int DxGHandle::DrawRectGraph(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRectGraph(DestX, DestY, SrcX, SrcY, Width, Height, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRectGraph().");
#endif
	return re;
}

int DxGHandle::DrawRectGraph(dxle::pointi Dest, dxle::pointi Src, dxle::pointi coord, bool TransFlag, bool TurnFlag) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::DrawRectGraph(Dest.x, Dest.y, Src.x, Src.y, coord.x, coord.y, this->GrHandle, TransFlag, TurnFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail DrawRectGraph().");
#endif
	return re;
}

DxGHandle DxGHandle::DerivationGraph(int SrcX, int SrcY, int Width, int Height) const DxHANDLE_NOEXCEPT {
	return DxGHandle(DxLib::DerivationGraph(SrcX, SrcY, Width, Height, this->GrHandle));
}

DxGHandle DxGHandle::DerivationGraph(dxle::pointi Src, dxle::pointi coord) const DxHANDLE_NOEXCEPT {
	return DxGHandle(DxLib::DerivationGraph(Src.x, Src.y, coord.x, coord.y, this->GrHandle));
}

int DxGHandle::GetGraphSize(int * SizeXBuf, int * SizeYBuf) const DxHANDLE_NOEXCEPT {
	const auto re = DxLib::GetGraphSize(this->GrHandle, SizeXBuf, SizeYBuf);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail GetGraphSize().");
#endif
	return re;
}

dxle::pointi DxGHandle::GetGraphSize() const DxHANDLE_NOEXCEPT {
	dxle::pointi re;
	return (0 == this->GetGraphSize(&re.x, &re.y)) ? re : dxle::pointi();
}

dxle::pointi DxGHandle::GetRelativeGraphCenter() const DxHANDLE_NOEXCEPT{
	return this->GetGraphSize() / 2;
}
namespace detail {
	DXLE_CONSTEXPR uint8_t DxGetRValue(unsigned int X8R8G8B8) { return static_cast<uint8_t>((0x00FF0000 & X8R8G8B8) >> 16); }
	DXLE_CONSTEXPR uint8_t DxGetGValue(unsigned int X8R8G8B8) { return static_cast<uint8_t>((0x0000FF00 & X8R8G8B8) >> 8); }
	DXLE_CONSTEXPR uint8_t DxGetBValue(unsigned int X8R8G8B8) { return static_cast<uint8_t>(0x000000FF & X8R8G8B8); }
	struct RGB_t {
		DXLE_CONSTEXPR RGB_t() : r(), g(), b() {}
		DXLE_CONSTEXPR RGB_t(uint8_t i_r, uint8_t i_g, uint8_t i_b) : r(i_r), g(i_g), b(i_b){}
		explicit DXLE_CONSTEXPR RGB_t(unsigned int X8R8G8B8) : r(DxGetRValue(X8R8G8B8)), g(DxGetGValue(X8R8G8B8)), b(DxGetBValue(X8R8G8B8)) {}
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
	RGB_t& operator+=(RGB_t& l, const RGB_t& r) {
		l.r += r.r;
		l.g += r.g;
		l.b += r.b;
		return l;
	}
	struct YPbPr {//ITU-R BT.709 cf.)http://koujinz.cocolog-nifty.com/blog/2009/03/rgbycbcr-a4a5.html
		YPbPr() = default;
		DXLE_CONSTEXPR YPbPr(uint8_t i_y, uint8_t i_pb, uint8_t i_pr) : y(i_y), pb(i_pb), pr(i_pr) {}
		explicit DXLE_CONSTEXPR YPbPr(uint8_t i_y) : y(i_y), pb(0), pr(0) {}
		uint8_t y, pb, pr;
	};
	DXLE_CONSTEXPR YPbPr to_YPbPr(RGB_t in) NOEXCEPT{
		return YPbPr(static_cast<uint8_t>(0.2126 * in.r + 0.7152 * in.g + 0.0722 * in.b), static_cast<uint8_t>(-0.1146 * in.r - 0.3854 * in.g + 0.5 * in.b), static_cast<uint8_t>(0.5 * in.r - 0.4542 * in.g - 0.0458 * in.b));
	}
	DXLE_CONSTEXPR RGB_t to_RGB_t(YPbPr in) NOEXCEPT{
		return RGB_t(static_cast<uint8_t>(in.y + 1.5748 * in.pr), static_cast<uint8_t>(in.y - 0.1873 * in.pb - 0.4681 * in.pr), static_cast<uint8_t>(in.y + 1.8556 * in.pb));
	}
	double num_distance(double a, double b) {
		const auto tmp = std::minmax(a, b);
		return tmp.second - tmp.first;
	}
}
DXLE_CXX14_CONSTEXPR std::array<detail::RGB_t, 256> make_y_gradation_rgb_arr_helper() NOEXCEPT{
	std::array<detail::RGB_t, 256> data_arr;
	static_assert(sizeof(detail::RGB_t) == 3, "sizeof struct 'detail::COLORTYPE' is not equal with 3.");
	for (std::size_t i = 0; i < data_arr.size(); ++i) data_arr[i] = detail::to_RGB_t(detail::YPbPr(static_cast<uint8_t>(i)));
	return data_arr;
}
std::array<detail::RGB_t, 256> make_y_gradation_rgb_arr(unsigned int base_color, bool trans_flag) NOEXCEPT {
	auto base_ypbpr = detail::to_YPbPr(detail::RGB_t(base_color));
	base_ypbpr.y = 0;
	const auto base_rbg = detail::to_RGB_t(base_ypbpr);
	auto re = make_y_gradation_rgb_arr_helper();
	if (trans_flag) std::reverse(re.begin(), re.end());
	for (auto& i : re) i += base_rbg;
	return re;
}

DxGHandle make_gradation_graph_handle(unsigned int base_color, bool trans_flag) NOEXCEPT {
	//http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=1837
	//http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=3365
	//http://eternalwindows.jp/graphics/bitmap/bitmap10.html
	//http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=1974
	auto y_gradation_rgb_arr = make_y_gradation_rgb_arr(base_color, trans_flag);
	BASEIMAGE tmp;
	CreateFullColorData(&tmp.ColorData);
	tmp.MipMapCount = 0;
	tmp.Height = 1;
	tmp.Width = static_cast<int>(y_gradation_rgb_arr.size());
	tmp.Pitch = tmp.Width * tmp.ColorData.PixelByte;
	tmp.GraphData = y_gradation_rgb_arr.data();
	return DxGHandle(CreateGraphFromBaseImage(&tmp));
}

int DxGHandle::filter_mono(int16_t Cb, int16_t Cr) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_MONO, Cb, Cr);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_mono().");
#endif
	return re;
}

int DxGHandle::filter_gaussian(uint16_t PixelWidth, int Param) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_GAUSS, PixelWidth, Param);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_gaussian().");
#endif
	return re;
}

int DxGHandle::filter_down_scale(uint8_t DivNum) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_DOWN_SCALE, DivNum);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_down_scale().");
#endif
	return re;
}

int DxGHandle::filter_bright_clip(bright_clip_mode clipmode, uint8_t clip_pram, unsigned int fillcolor, uint8_t fillalpha) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_BRIGHT_CLIP, clipmode, clip_pram, fillcolor, fillalpha);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_bright_clip().");
#endif
	return re;
}

int DxGHandle::filter_HSB(bool HueType, int16_t Hue, int Saturation, int16_t Bright) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_HSB, HueType, Hue, Saturation, Bright);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_HSB().");
#endif
	return re;
}

int DxGHandle::filter_invert() DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_INVERT);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_invert().");
#endif
	return re;
}

int DxGHandle::filter_level(uint8_t min, uint8_t max, int Gamma, uint8_t Aftermin, uint8_t Aftermax) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_LEVEL, min, max, Gamma, Aftermin, Aftermax);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_level().");
#endif
	return re;
}

int DxGHandle::filter_two_color(uint8_t threshold, unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_LEVEL, threshold, LowColor, LowAlpha, HighColor, HighAlpha);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_two_color().");
#endif
	return re;
}

int DxGHandle::filter_two_color(uint8_t threshold, unsigned int LowColor, unsigned int HighColor) DxHANDLE_NOEXCEPT {
	return this->filter_two_color(threshold, LowColor, 255, HighColor, 255);
}

int DxGHandle::filter_gradient_map(const DxGHandle & MapGrHandle, bool Reverse_flag) DxHANDLE_NOEXCEPT {
	const auto re = GraphFilter(this->GrHandle, DX_GRAPH_FILTER_LEVEL, MapGrHandle.GrHandle, Reverse_flag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail filter_gradient_map().");
#endif
	return re;
}

int DxGHandle::filter_gradient_map(unsigned int base_color, bool Reverse_flag) DxHANDLE_NOEXCEPT {
	return this->filter_gradient_map(make_gradation_graph_handle(base_color), Reverse_flag);
}
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
BASEIMAGE to_BASEIMAGE(const DxGHandle & handle) {//YOU MUST CALL ReleaseBaseImage to free memory.
	const auto size = handle.GetGraphSize();
	const auto tmp_screen = DxLib::MakeScreen(size.x, size.y, TRUE);
	auto err = DxLib::SetDrawScreen(tmp_screen);
	if (-1 == err) std::runtime_error("Fail DxLib::SetDrawScreen().");
	err = DxLib::SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR, 255);// 透明部分もそのまま描画先に描き込むブレンドモードにセット
	if (-1 == err) std::runtime_error("Fail DxLib::SetDrawBlendMode().");
	handle.DrawGraph(0, 0, true);//透明度を有効に
	BASEIMAGE BaseImage;
	err = DxLib::CreateARGB8ColorBaseImage(size.x, size.y, &BaseImage);//画像サイズと同じサイズの BASEIMAGE を作成
	if (-1 == err) std::runtime_error("Fail DxLib::CreateARGB8ColorBaseImage().");
	err = DxLib::GetDrawScreenBaseImage(0, 0, size.x, size.y, &BaseImage);//描画先から画像を取り込む
	if (-1 == err) std::runtime_error("Fail DxLib::GetDrawScreenBaseImage().");
	err = DxLib::DeleteGraph(tmp_screen);
	if (-1 == err) std::runtime_error("Fail DxLib::DeleteGraph().");
	return BaseImage;
}
using hist_arr_t = std::array<uint32_t, 256>;
uint8_t calc_threshold_algolithm_otu(const DxGHandle & handle) {
	//http://web.archive.org/web/20120625061358/http://cct2.toba-cmt.ac.jp/~5509/report/ps-1/otsu_bin.html
	//http://aquioux.net/blog/coding/as/automatic-calculation-of-threshold-by-discriminant-analysis-method-again-2/
	using namespace detail;
	BASEIMAGE baseimage = to_BASEIMAGE(handle);
	if (baseimage.ColorData.PixelByte != 4) throw std::runtime_error("to_BASEIMAGE() make irregal BASEIMAGE struct.");

	hist_arr_t histgram = {};//初期化
	for (int i = 0; i < baseimage.Height * baseimage.Width; ++i)
		++histgram[to_YPbPr(RGB_t(static_cast<uint32_t*>(baseimage.GraphData)[i])).y];//投票
	ReleaseBaseImage(&baseimage);

	hist_arr_t sumN, sumM;
	for (uint32_t i = 0; i < histgram.size(); ++i) {
		sumN[i] = sumN[i ? i - 1 : 0] + histgram[i];
		sumM[i] = sumM[i ? i - 1 : 0] + histgram[i] * i;
	}
	const auto n0 = sumN.back();// 画素数
	const auto m0 = sumM.back();// 濃度
	double max_dispersion = 0.0;// 最大分散
	uint8_t threshold = 0;//   求める閾値
	for (size_t i = 0; i < histgram.size(); ++i) {
		const auto   n1 = sumN[i];// 画素数
		const double m1 = sumM[i];// 濃度
		const auto   n2 = n0 - n1;// 画素数
		const double m2 = m0 - m1;// 濃度

		const double val1 = ((n1) ? m1 / n1 : 0) - m0;
		const double val2 = ((n2) ? m2 / n2 : 0) - m0;
		const double dispersion = (n1 * val1 * val1 + n2 * val2 * val2) / n0;
		if (max_dispersion < dispersion) {
			max_dispersion = dispersion;
			threshold = static_cast<uint8_t>(i);
		}
	}
	return threshold;
}
int DxGHandle::filter_two_color_algolithm_otu(unsigned int LowColor, uint8_t LowAlpha, unsigned int HighColor, uint8_t HighAlpha) DxHANDLE_NOEXCEPT{
	return this->filter_two_color(calc_threshold_algolithm_otu(*this), LowColor, LowAlpha, HighColor, HighAlpha);
}
int DxGHandle::filter_two_color_algolithm_otu(unsigned int LowColor, unsigned int HighColor) DxHANDLE_NOEXCEPT {
	return this->filter_two_color_algolithm_otu(LowColor, 255, HighColor, 255);
}
#endif

