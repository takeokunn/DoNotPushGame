#pragma once
#if (defined(_MSC_VER) && _MSC_FULL_VER >= 180031101) ||(defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))) || (defined(__GNUC__) && (__GNUC__ > 4  || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#define SUPPORT_CONSTEXPR 1
#define CONSTEXPR constexpr
#define CONSTEXPR_OR_CONST constexpr
#define CONSTEXPR_OR_STATICCONST constexpr
#else
#define CONSTEXPR
#define CONSTEXPR_OR_CONST const
#define CONSTEXPR_OR_STATICCONST static const
#endif
