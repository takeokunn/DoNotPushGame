#pragma once
#include "dxlibex/config/defines.h"
#define NOEXCEPT DXLE_NOEXCEPT_OR_NOTHROW
#define ATT_PURE NOEXCEPT//attribute [[pure]]
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_NOEXCEPT
#else
#define DxHANDLE_NOEXCEPT NOEXCEPT
#endif //DxHANDLE_WRAP_USE_EXCEPTION
