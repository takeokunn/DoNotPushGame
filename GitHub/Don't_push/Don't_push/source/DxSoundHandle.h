#pragma once
#include <string>
#include <cstdint>
#ifndef DISABLE_DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_WRAP_USE_EXCEPTION//throwする
#endif
#include "util_noexcept.h"

enum class DxSoundMode : int
{
	NORMAL = 0,
	BACK = 1,
	LOOP = 3
};
///<summary>音楽再生に関する関数のラップクラスです</summary>
class DxSHandle {
public:
	typedef int DxSHandle_t;
	DxSHandle() NOEXCEPT : SHandle(-1) {}
	explicit DxSHandle(const std::string& FileName) DxHANDLE_NOEXCEPT;
	explicit DxSHandle(const char* FileName) DxHANDLE_NOEXCEPT;
	explicit DxSHandle(DxSHandle_t SHandle) DxHANDLE_NOEXCEPT;
	DxSHandle(const DxSHandle& o) NOEXCEPT : SHandle(o.SHandle) {}
	explicit DxSHandle(DxSHandle&& o) NOEXCEPT : SHandle(o.SHandle) {}
	///<summary>音楽を再生します</summary>
	///<param name="PlayType">再生モード</param>
	///<param name="TopPositionFlag">音データを再生する前に再生開始位置を先頭に戻すかどうか</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int play(DxSoundMode PlayType, bool TopPositionFlag = true) DxHANDLE_NOEXCEPT;
	///<summary>音楽を再生します</summary>
	///<param name="PlayType">再生モード</param>
	///<param name="Volume">音量(0-255)</param>
	///<param name="TopPositionFlag">音データを再生する前に再生開始位置を先頭に戻すかどうか</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int play(DxSoundMode PlayType, uint8_t Volume, bool TopPositionFlag = true) DxHANDLE_NOEXCEPT;
	///<summary>音楽を再生します</summary>
	///<param name="PlayType">再生モード</param>
	///<param name="Volume">音量(0-255)</param>
	///<param name="Volume">左右の音量の比率(-255 ～ 255 ＋は左の音量を下げ、－は右の音量を下げる)(0-255)</param>
	///<param name="TopPositionFlag">音データを再生する前に再生開始位置を先頭に戻すかどうか</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int play(DxSoundMode PlayType, uint8_t Volume, int16_t Pan, bool TopPositionFlag = true) DxHANDLE_NOEXCEPT;
	///<summary>再生中の音楽の音量を変更します</summary>
	///<param name="Volume">音量(0-255)</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int ChangeVolume(uint8_t Volume) DxHANDLE_NOEXCEPT;
	///<summary>再生中の音楽の左右の音量の比率を変更します</summary>
	///<param name="Volume">左右の音量の比率(-255 ～ 255 ＋は左の音量を下げ、－は右の音量を下げる)(0-255)</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int ChangePan(int16_t Pan) DxHANDLE_NOEXCEPT;
	///<summary>次に再生する音楽の音量を変更します</summary>
	///<param name="Volume">音量(0-255)</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int ChangeNextPlayVolume(uint8_t Volume) DxHANDLE_NOEXCEPT;
	///<summary>次に再生する音楽の左右の音量の比率を変更します</summary>
	///<param name="Volume">左右の音量の比率(-255 ～ 255 ＋は左の音量を下げ、－は右の音量を下げる)(0-255)</param>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int ChangeNextPlayPan(int16_t Pan) DxHANDLE_NOEXCEPT;
	///<summary>音楽の再生を終了します</summary>
	///<exception cref="DxSHandle_runtime_error">DxSHandle_runtime_error</exception>
	int stop() DxHANDLE_NOEXCEPT;
	///<summary>音楽が再生中か調べます</summary>
	///<returns>1：再生中, 0：再生されていない, -1：エラー発生</returns>
	int is_during_playback() NOEXCEPT;
	///<summary>生のサウンドハンドルを返します</summary>
	///<returns>DxLibの関数に指定できるサウンドハンドル(int型)</returns>
	DxSHandle_t get_raw() NOEXCEPT { return this->SHandle; }
private:
	///<summary>サウンドハンドル</summary>
	DxSHandle_t SHandle;
};
