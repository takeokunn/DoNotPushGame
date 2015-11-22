#pragma once
#if (defined(_MSC_VER) && _MSC_FULL_VER >= 180031101) ||(defined(__clang__) && __clang__ >= 3) || (defined(__GNUC__) && (__GNUC__ > 4  || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif //_MSC_VER > 1800
#define ATT_PURE NOEXCEPT//attribute [[pure]]
#ifdef DxHANDLE_WRAP_USE_EXCEPTION
#define DxHANDLE_NOEXCEPT
#else
#define DxHANDLE_NOEXCEPT NOEXCEPT
#endif //DxHANDLE_WRAP_USE_EXCEPTION
