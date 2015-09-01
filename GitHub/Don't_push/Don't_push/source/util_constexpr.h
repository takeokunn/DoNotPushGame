#pragma once
#if (defined(_MSC_VER) && _MSC_FULL_VER >= 180031101) ||(defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 1))) || (defined(__GNUC__) && (__GNUC__ > 4  || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#define SUPPORT_CONSTEXPR 1
#define CONSTEXPR constexpr
#define CONSTEXPR_OR_CONST constexpr
#define CONSTEXPR_OR_STATICCONST constexpr
#if (defined(_MSC_VER) && _MSC_VER < 1900)
#define CONSTEXPR_FUNCTION
#else
#define SUPPORT_CONSTEXPR_FUNCTION 1
#define CONSTEXPR_FUNCTION constexpr
#endif
#else
#define CONSTEXPR
#define CONSTEXPR_OR_CONST const
#define CONSTEXPR_OR_STATICCONST static const
#endif
#if ((defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))) || (defined(__GNUC__) && (__GNUC__ > 5)))
#define SUPPORT_CXX14_CONSTEXPR 1
#define CXX14_CONSTEXPR constexpr
#else
#define CXX14_CONSTEXPR
#endif
