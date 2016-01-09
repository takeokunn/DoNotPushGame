#pragma once
#include "define.h"
#include <dxlibex/basic_types.hpp>
#ifndef DISABLE_DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_WRAP_USE_EXCEPTION//throwする
#endif
#include "util_noexcept.h"

///<summary>体力ゲージの表示用クラスです</summary>
class power_bar_c
{
public:
	///<summary><c>power_bar_c</c>のインスタンスを初期化します</summary>
	///<param name="base_point">バーの左上の座標</param>
	///<param name="whole_bar_size_">バーの大きさ(最大)</param>
	///<param name="frame_num_to_fill">バーの長さが最大になるまでに必要なframe数</param>
	///<param name="color">バーの色</param>
	power_bar_c(const dxle::pointi& base_point, const dxle::pointi& whole_bar_size, size_t frame_num_to_fill, unsigned int color) NOEXCEPT;
	explicit power_bar_c(const power_bar_c& o) NOEXCEPT;
	///<summary>状態を更新します。描画ループで毎回呼び出してください</summary>
	void update() NOEXCEPT;
	///<summary>描画します</summary>
	///<exception　cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int draw() const DxHANDLE_NOEXCEPT;
	///<summary>描画が全体の何%かを調べます</summary>
	double get_percent() const NOEXCEPT;
private:
	///<summary>バーの左上の座標</summary>
	dxle::pointi base_point_;
	///<summary>バーの大きさ(最大)</summary>
	const dxle::pointi whole_bar_size_;
	///<summary>バーの長さ</summary>
	int draw_pixcel_num_;
	///<summary>バーの色</summary>
	const unsigned int color_;
	///<summary>バーの長さが0の時からのframe数</summary>
	size_t spent_frame_;
	///<summary>バーの長さが最大になるまでに必要なframe数</summary>
	const size_t frame_num_to_fill_;
};
