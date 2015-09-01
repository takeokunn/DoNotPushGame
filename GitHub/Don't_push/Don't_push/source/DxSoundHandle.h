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

class DxSHandle {
public:
	typedef int DxSHandle_t;
	DxSHandle() NOEXCEPT : SHandle(-1) {}
	explicit DxSHandle(const std::string& FileName) DxHANDLE_NOEXCEPT;
	explicit DxSHandle(const char* FileName) DxHANDLE_NOEXCEPT;
	explicit DxSHandle(DxSHandle_t SHandle) DxHANDLE_NOEXCEPT;
	DxSHandle(const DxSHandle& o) NOEXCEPT : SHandle(o.SHandle) {}
	explicit DxSHandle(DxSHandle&& o) NOEXCEPT : SHandle(o.SHandle) {}
	int play(DxSoundMode PlayType, bool TopPositionFlag = true) DxHANDLE_NOEXCEPT;
	int play(DxSoundMode PlayType, uint8_t Volume, bool TopPositionFlag = true) DxHANDLE_NOEXCEPT;
	int play(DxSoundMode PlayType, uint8_t Volume, int16_t Pan, bool TopPositionFlag = true) DxHANDLE_NOEXCEPT;
	int ChangeVolume(uint8_t Volume) DxHANDLE_NOEXCEPT;
	int ChangePan(int16_t Pan) DxHANDLE_NOEXCEPT;
	int ChangeNextPlayVolume(uint8_t Volume) DxHANDLE_NOEXCEPT;
	int ChangeNextPlayPan(int16_t Pan) DxHANDLE_NOEXCEPT;
	int stop() DxHANDLE_NOEXCEPT;
	int is_during_playback() NOEXCEPT;
	DxSHandle_t get_raw() NOEXCEPT { return this->SHandle; }
private:
	DxSHandle_t SHandle;
};
