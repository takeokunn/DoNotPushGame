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
		if ("mid" == ext || "MID" == ext) throw DxSHandle_runtime_error("midiファイルは利用できません。PlaySound関数を利用してください");
		throw DxSHandle_runtime_error("音声の読み込みに失敗しました");
	}
#endif
}

DxSHandle::DxSHandle(DxSHandle_t SHandle) DxHANDLE_NOEXCEPT {
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == SHandle) throw DxGHandle_runtime_error("音声ハンドルの作成に失敗しました");
#endif
	this->SHandle = SHandle;
}

int DxSHandle::play(DxSoundMode PlayType, bool TopPositionFlag) DxHANDLE_NOEXCEPT {
	const auto re = PlaySoundMem(this->SHandle, static_cast<int>(PlayType), TopPositionFlag);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("音声の再生に失敗しました");
#endif
	return re;
}

int DxSHandle::play(DxSoundMode PlayType, uint8_t Volume, bool TopPositionFlag) DxHANDLE_NOEXCEPT {
	this->ChangeNextPlayVolume(Volume);
	return this->play(PlayType, TopPositionFlag);
}

int DxSHandle::play(DxSoundMode PlayType, uint8_t Volume, int16_t Pan, bool TopPositionFlag) DxHANDLE_NOEXCEPT {
	this->ChangeNextPlayPan(Pan);
	return this->play(PlayType, Volume, TopPositionFlag);
}

int DxSHandle::ChangeVolume(uint8_t Volume) DxHANDLE_NOEXCEPT {
	const auto re = ChangeVolumeSoundMem(Volume, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("音量を変更できませんでした");
#endif
	return re;
}

int DxSHandle::ChangePan(int16_t Pan) DxHANDLE_NOEXCEPT {
	const auto re = ChangePanSoundMem(Pan, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("パンを変更できませんでした");
#endif
	return 0;
}

int DxSHandle::ChangeNextPlayVolume(uint8_t Volume) DxHANDLE_NOEXCEPT {
	const auto re = ChangeNextPlayVolumeSoundMem(Volume, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("音量を変更できませんでした");
#endif
	return re;
}

int DxSHandle::ChangeNextPlayPan(int16_t Pan) DxHANDLE_NOEXCEPT {
	const auto re = ChangeNextPlayPanSoundMem(Pan, this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("パンを変更できませんでした");
#endif
	return re;
}

int DxSHandle::stop() DxHANDLE_NOEXCEPT {
	const auto re = StopSoundMem(this->SHandle);
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
	if (-1 == re) throw DxGHandle_runtime_error("StopSoundMem関数で失敗しました");
#endif
	return re;
}

int DxSHandle::is_during_playback() NOEXCEPT {
	return CheckSoundMem(this->SHandle);
}
