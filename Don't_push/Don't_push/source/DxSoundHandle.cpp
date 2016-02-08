#include "DxSoundHandle.h"
#include "DxLib.h"
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
#include "DxHandleException.h"
#endif
DxSHandle::DxSHandle(const std::string & FileName) DxHANDLE_NOEXCEPT {
	this->SHandle = LoadSoundMem(FileName.c_str());
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == this->SHandle) {
		const auto ext = FileName.substr(FileName.find_first_of('.'), ((FileName.back() == '\\') ? FileName.length() - 2 : std::string::npos));
		if ("mid" == ext || "MID" == ext) throw DxSHandle_runtime_error(".midi is not supported. Use PlaySound() instead.");
		throw DxSHandle_runtime_error("Fail to load sound.");
	}
#endif
}

DxSHandle::DxSHandle(const char * FileName) : DxSHandle(std::string(FileName)) DxHANDLE_NOEXCEPT {}

DxSHandle::DxSHandle(DxSHandle_t SHandle) DxHANDLE_NOEXCEPT {
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == SHandle) throw DxGHandle_runtime_error("Fail to make sound handle.");
#endif
	this->SHandle = SHandle;
}

int DxSHandle::play(DxSoundMode PlayType, bool TopPositionFlag) const DxHANDLE_NOEXCEPT {
	const auto re = PlaySoundMem(this->SHandle, static_cast<int>(PlayType), TopPositionFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail PlaySoundMem().");
#endif
	return re;
}

int DxSHandle::play(DxSoundMode PlayType, uint8_t Volume, bool TopPositionFlag) const DxHANDLE_NOEXCEPT {
	this->ChangeNextPlayVolume(Volume);
	return this->play(PlayType, TopPositionFlag);
}

int DxSHandle::play(DxSoundMode PlayType, uint8_t Volume, int16_t Pan, bool TopPositionFlag) const DxHANDLE_NOEXCEPT {
	this->ChangeNextPlayPan(Pan);
	return this->play(PlayType, Volume, TopPositionFlag);
}

int DxSHandle::ChangeVolume(uint8_t Volume) const DxHANDLE_NOEXCEPT {
	const auto re = ChangeVolumeSoundMem(Volume, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail ChangeVolumeSoundMem().");
#endif
	return re;
}

int DxSHandle::ChangePan(int16_t Pan) const DxHANDLE_NOEXCEPT {
	const auto re = ChangePanSoundMem(Pan, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail ChangePan().");
#endif
	return 0;
}

int DxSHandle::ChangeNextPlayVolume(uint8_t Volume) const DxHANDLE_NOEXCEPT {
	const auto re = ChangeNextPlayVolumeSoundMem(Volume, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail ChangeNextPlayVolume().");
#endif
	return re;
}

int DxSHandle::ChangeNextPlayPan(int16_t Pan) const DxHANDLE_NOEXCEPT {
	const auto re = ChangeNextPlayPanSoundMem(Pan, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail ChangeNextPlayPan().");
#endif
	return re;
}

int DxSHandle::stop() const DxHANDLE_NOEXCEPT {
	const auto re = StopSoundMem(this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("Fail StopSoundMem().");
#endif
	return re;
}

int DxSHandle::is_during_playback() const NOEXCEPT {
	return CheckSoundMem(this->SHandle);
}
