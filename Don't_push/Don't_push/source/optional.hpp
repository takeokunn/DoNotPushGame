// Copyright (C) 2011 - 2012 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// The idea and interface is based on Boost.Optional library
// authored by Fernando Luis Cacciola Carballal

# ifndef ___OPTIONAL_HPP___
# define ___OPTIONAL_HPP___

# include <utility>
# include <type_traits>
# include <initializer_list>
# include <cassert>
# include <functional>
# include <string>
# include <stdexcept>
#include "dxlibex/config/defines.h"
# define TR2_OPTIONAL_REQUIRES(...) typename enable_if<__VA_ARGS__::value, bool>::type = false

# if defined __GNUC__ // NOTE: GNUC is also defined for Clang
#   if (__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)
#     define TR2_OPTIONAL_GCC_4_8_AND_HIGHER___
#   elif (__GNUC__ > 4)
#     define TR2_OPTIONAL_GCC_4_8_AND_HIGHER___
#   endif
#
#   if (__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)
#     define TR2_OPTIONAL_GCC_4_7_AND_HIGHER___
#   elif (__GNUC__ > 4)
#     define TR2_OPTIONAL_GCC_4_7_AND_HIGHER___
#   endif
#
#   if (__GNUC__ == 4) && (__GNUC_MINOR__ == 8) && (__GNUC_PATCHLEVEL__ >= 1)
#     define TR2_OPTIONAL_GCC_4_8_1_AND_HIGHER___
#   elif (__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)
#     define TR2_OPTIONAL_GCC_4_8_1_AND_HIGHER___
#   elif (__GNUC__ > 4)
#     define TR2_OPTIONAL_GCC_4_8_1_AND_HIGHER___
#   endif
# endif
#
# if defined __clang_major__
#   if (__clang_major__ == 3 && __clang_minor__ >= 5)
#     define TR2_OPTIONAL_CLANG_3_5_AND_HIGHTER_
#   elif (__clang_major__ > 3)
#     define TR2_OPTIONAL_CLANG_3_5_AND_HIGHTER_
#   endif
#   if defined TR2_OPTIONAL_CLANG_3_5_AND_HIGHTER_
#     define TR2_OPTIONAL_CLANG_3_4_2_AND_HIGHER_
#   elif (__clang_major__ == 3 && __clang_minor__ == 4 && __clang_patchlevel__ >= 2)
#     define TR2_OPTIONAL_CLANG_3_4_2_AND_HIGHER_
#   endif
# endif
#
# if defined _MSC_VER
#   if (_MSC_VER >= 1900)
#     define TR2_OPTIONAL_MSVC_2015_AND_HIGHER___
#   endif
# endif

# if defined __clang__
#   if (__clang_major__ > 2) || (__clang_major__ == 2) && (__clang_minor__ >= 9)
#     define OPTIONAL_HAS_THIS_RVALUE_REFS 1
#   else
#     define OPTIONAL_HAS_THIS_RVALUE_REFS 0
#   endif
# elif defined TR2_OPTIONAL_GCC_4_8_1_AND_HIGHER___
#   define OPTIONAL_HAS_THIS_RVALUE_REFS 1
# elif defined TR2_OPTIONAL_MSVC_2015_AND_HIGHER___
#   define OPTIONAL_HAS_THIS_RVALUE_REFS 1
# else
#   define OPTIONAL_HAS_THIS_RVALUE_REFS 0
# endif


# if defined TR2_OPTIONAL_GCC_4_8_1_AND_HIGHER___
#   define OPTIONAL_HAS_CONSTEXPR_INIT_LIST 1
#   define OPTIONAL_CONSTEXPR_INIT_LIST constexpr
# else
#   define OPTIONAL_HAS_CONSTEXPR_INIT_LIST 0
#   define OPTIONAL_CONSTEXPR_INIT_LIST
# endif

# if defined TR2_OPTIONAL_CLANG_3_5_AND_HIGHTER_ && (defined __cplusplus) && (__cplusplus != 201103L)
#   define OPTIONAL_HAS_MOVE_ACCESSORS 1
# else
#   define OPTIONAL_HAS_MOVE_ACCESSORS 0
# endif

# // In C++11 constexpr implies const, so we need to make non-const members also non-constexpr
# if (defined __cplusplus) && (__cplusplus == 201103L)
#   define OPTIONAL_MUTABLE_CONSTEXPR
# else
#   define OPTIONAL_MUTABLE_CONSTEXPR DXLE_CONSTEXPR
# endif

namespace std{

namespace experimental{

// BEGIN workaround for missing is_trivially_destructible
# if defined TR2_OPTIONAL_GCC_4_8_AND_HIGHER___
    // leave it: it is already there
# elif defined TR2_OPTIONAL_CLANG_3_4_2_AND_HIGHER_
    // leave it: it is already there
# elif defined TR2_OPTIONAL_MSVC_2015_AND_HIGHER___
    // leave it: it is already there
# elif defined TR2_OPTIONAL_DISABLE_EMULATION_OF_TYPE_TRAITS
    // leave it: the user doesn't want it
# else
	template <typename T>
	using is_trivially_destructible = std::has_trivial_destructor<T>;
# endif
// END workaround for missing is_trivially_destructible

# if (defined TR2_OPTIONAL_GCC_4_7_AND_HIGHER___)
    // leave it; our metafunctions are already defined.
# elif defined TR2_OPTIONAL_CLANG_3_4_2_AND_HIGHER_
    // leave it; our metafunctions are already defined.
# elif defined TR2_OPTIONAL_MSVC_2015_AND_HIGHER___
    // leave it: it is already there
# elif defined TR2_OPTIONAL_DISABLE_EMULATION_OF_TYPE_TRAITS
    // leave it: the user doesn't want it
# else


// workaround for missing traits in GCC and CLANG
template <class T>
struct is_nothrow_move_constructible
{
  DXLE_STATIC_CONSTEXPR bool value = std::is_nothrow_constructible<T, T&&>::value;
};


template <class T, class U>
struct is_assignable
{
  template <class X, class Y>
  DXLE_CONSTEXPR static bool has_assign(...) { return false; }

  template <class X, class Y, size_t S = sizeof((std::declval<X>() = std::declval<Y>(), true)) >
  // the comma operator is necessary for the cases where operator= returns void
  DXLE_CONSTEXPR static bool has_assign(bool) { return true; }

  DXLE_STATIC_CONSTEXPR bool value = std::is_assignable<T, U>::value;
};


template <class T>
struct is_nothrow_move_assignable
{
  template <class X, bool has_any_move_assign>
  struct has_nothrow_move_assign {
	  DXLE_STATIC_CONSTEXPR bool value = false;
  };

  template <class X>
  struct has_nothrow_move_assign<X, true> {
	  DXLE_STATIC_CONSTEXPR bool value = DXLE_NOEXCEPT_EXPR(std::declval<X&>() = std::declval<X&&>());
  };

  DXLE_STATIC_CONSTEXPR bool value = has_nothrow_move_assign<T, is_assignable<T&, T&&>::value>::value;
};
// end workaround


# endif



// 20.5.4, optional for object types
template <class T> class optional;

// 20.5.5, optional for lvalue reference types
template <class T> class optional<T&>;


// workaround: std utility functions aren't constexpr yet
template <class T> inline DXLE_CONSTEXPR T&& constexpr_forward(typename std::remove_reference<T>::type& t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return static_cast<T&&>(t);
}

template <class T> inline DXLE_CONSTEXPR T&& constexpr_forward(typename std::remove_reference<T>::type&& t) DXLE_NOEXCEPT_OR_NOTHROW
{
    static_assert(!std::is_lvalue_reference<T>::value, "!!");
    return static_cast<T&&>(t);
}

template <class T> inline DXLE_CONSTEXPR typename std::remove_reference<T>::type&& constexpr_move(T&& t) DXLE_NOEXCEPT_OR_NOTHROW
{
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}


#if defined NDEBUG
# define TR2_OPTIONAL_ASSERTED_EXPRESSION(CHECK, EXPR) (EXPR)
#else
# define TR2_OPTIONAL_ASSERTED_EXPRESSION(CHECK, EXPR) ((CHECK) ? (EXPR) : ([]{assert(!#CHECK);}(), (EXPR)))
#endif


namespace detail_
{

// static_addressof: a constexpr version of addressof
template <typename T>
struct has_overloaded_addressof
{
  template <class X>
  DXLE_CONSTEXPR static bool has_overload(...) { return false; }
  
  template <class X, size_t S = sizeof(std::declval<X&>().operator&()) >
  DXLE_CONSTEXPR static bool has_overload(bool) { return true; }

  DXLE_STATIC_CONSTEXPR bool value = has_overload<T>(true);
};

template <typename T, TR2_OPTIONAL_REQUIRES(!has_overloaded_addressof<T>)>
DXLE_CONSTEXPR T* static_addressof(T& ref)
{
  return &ref;
}

template <typename T, TR2_OPTIONAL_REQUIRES(has_overloaded_addressof<T>)>
T* static_addressof(T& ref)
{
  return std::addressof(ref);
}


// the call to convert<A>(b) has return type A and converts b to type A iff b decltype(b) is implicitly convertible to A  
template <class U>
U convert(U v) { return v; }
  
} // namespace detail


DXLE_CONSTEXPR_CLASS struct trivial_init_t{} trivial_init{};


// 20.5.6, In-place construction
DXLE_CONSTEXPR_CLASS struct in_place_t{} in_place{};


// 20.5.7, Disengaged state indicator
struct nullopt_t
{
  struct init{};
  DXLE_CONSTEXPR_CLASS explicit nullopt_t(init){}
};
DXLE_CONSTEXPR_CLASS nullopt_t nullopt{ nullopt_t::init() };


// 20.5.8, class bad_optional_access
class bad_optional_access : public logic_error {
public:
  explicit bad_optional_access(const string& what_arg) : logic_error{what_arg} {}
  explicit bad_optional_access(const char* what_arg) : logic_error{what_arg} {}
};


template <class T>
union storage_t
{
  unsigned char dummy_;
  T value_;

  DXLE_CONSTEXPR_CLASS storage_t(trivial_init_t) DXLE_NOEXCEPT_OR_NOTHROW : dummy_() {};

  template <class... Args>
  DXLE_CONSTEXPR_CLASS storage_t(Args&&... args) : value_(constexpr_forward<Args>(args)...) {}

  ~storage_t(){}
};


template <class T>
union constexpr_storage_t
{
    unsigned char dummy_;
    T value_;

	DXLE_CONSTEXPR_CLASS constexpr_storage_t(trivial_init_t) DXLE_NOEXCEPT_OR_NOTHROW : dummy_() {};

    template <class... Args>
	DXLE_CONSTEXPR_CLASS constexpr_storage_t(Args&&... args) : value_(constexpr_forward<Args>(args)...) {}

    ~constexpr_storage_t() = default;
};


template <class T>
struct optional_base
{
    bool init_;
    storage_t<T> storage_;

	DXLE_CONSTEXPR_CLASS optional_base() DXLE_NOEXCEPT_OR_NOTHROW : init_(false), storage_(trivial_init) {};

	explicit DXLE_CONSTEXPR_CLASS optional_base(const T& v) : init_(true), storage_(v) {}

	explicit DXLE_CONSTEXPR_CLASS optional_base(T&& v) : init_(true), storage_(constexpr_move(v)) {}

    template <class... Args> explicit optional_base(in_place_t, Args&&... args)
        : init_(true), storage_(constexpr_forward<Args>(args)...) {}

    template <class U, class... Args, TR2_OPTIONAL_REQUIRES(is_constructible<T, std::initializer_list<U>>)>
    explicit optional_base(in_place_t, std::initializer_list<U> il, Args&&... args)
        : init_(true), storage_(il, std::forward<Args>(args)...) {}

    ~optional_base() { if (init_) storage_.value_.T::~T(); }
};


template <class T>
struct constexpr_optional_base
{
    bool init_;
    constexpr_storage_t<T> storage_;

	DXLE_CONSTEXPR_CLASS constexpr_optional_base() DXLE_NOEXCEPT_OR_NOTHROW : init_(false), storage_(trivial_init) {};

	explicit DXLE_CONSTEXPR_CLASS constexpr_optional_base(const T& v) : init_(true), storage_(v) {}

	explicit DXLE_CONSTEXPR_CLASS constexpr_optional_base(T&& v) : init_(true), storage_(constexpr_move(v)) {}

	template <class... Args> explicit DXLE_CONSTEXPR_CLASS constexpr_optional_base(in_place_t, Args&&... args)
      : init_(true), storage_(constexpr_forward<Args>(args)...) {}

    template <class U, class... Args, TR2_OPTIONAL_REQUIRES(is_constructible<T, std::initializer_list<U>>)>
    OPTIONAL_CONSTEXPR_INIT_LIST explicit constexpr_optional_base(in_place_t, std::initializer_list<U> il, Args&&... args)
      : init_(true), storage_(il, std::forward<Args>(args)...) {}

    ~constexpr_optional_base() = default;
};

template <class T>
using OptionalBase = typename std::conditional<
    is_trivially_destructible<T>::value,
    constexpr_optional_base<T>,
    optional_base<T>
>::type;



template <class T>
class optional : private OptionalBase<T>
{
  static_assert( !std::is_same<typename std::decay<T>::type, nullopt_t>::value, "bad T" );
  static_assert( !std::is_same<typename std::decay<T>::type, in_place_t>::value, "bad T" );
  

  DXLE_CONSTEXPR bool initialized() const DXLE_NOEXCEPT_OR_NOTHROW{ return OptionalBase<T>::init_; }
  T* dataptr() {  return std::addressof(OptionalBase<T>::storage_.value_); }
  DXLE_CONSTEXPR const T* dataptr() const { return detail_::static_addressof(OptionalBase<T>::storage_.value_); }
  
# if OPTIONAL_HAS_THIS_RVALUE_REFS == 1
  constexpr const T& contained_val() const& { return OptionalBase<T>::storage_.value_; }
#   if OPTIONAL_HAS_MOVE_ACCESSORS == 1
  OPTIONAL_MUTABLE_CONSTEXPR T&& contained_val() && { return std::move(OptionalBase<T>::storage_.value_); }
  OPTIONAL_MUTABLE_CONSTEXPR T& contained_val() & { return OptionalBase<T>::storage_.value_; }
#   else
  T& contained_val() & { return OptionalBase<T>::storage_.value_; }
  T&& contained_val() && { return std::move(OptionalBase<T>::storage_.value_); }
#   endif
# else
  DXLE_CONSTEXPR const T& contained_val() const { return OptionalBase<T>::storage_.value_; }
  T& contained_val() { return OptionalBase<T>::storage_.value_; }
# endif

  void clear() DXLE_NOEXCEPT_OR_NOTHROW {
    if (initialized()) dataptr()->T::~T();
    OptionalBase<T>::init_ = false;
  }
  
  template <class... Args>
  void initialize(Args&&... args) DXLE_NOEXCEPT_IF_EXPR(T(std::forward<Args>(args)...))
  {
    assert(!OptionalBase<T>::init_);
    ::new (static_cast<void*>(dataptr())) T(std::forward<Args>(args)...);
    OptionalBase<T>::init_ = true;
  }

  template <class U, class... Args>
  void initialize(std::initializer_list<U> il, Args&&... args) DXLE_NOEXCEPT_IF_EXPR(T(il, std::forward<Args>(args)...))
  {
    assert(!OptionalBase<T>::init_);
    ::new (static_cast<void*>(dataptr())) T(il, std::forward<Args>(args)...);
    OptionalBase<T>::init_ = true;
  }

public:
  typedef T value_type;

  // 20.5.5.1, constructors
  DXLE_CONSTEXPR_CLASS optional() DXLE_NOEXCEPT_OR_NOTHROW : OptionalBase<T>()  {};
  DXLE_CONSTEXPR_CLASS optional(nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW : OptionalBase<T>() {};

  optional(const optional& rhs)
  : OptionalBase<T>()
  {
    if (rhs.initialized()) {
        ::new (static_cast<void*>(dataptr())) T(*rhs);
        OptionalBase<T>::init_ = true;
    }
  }

  optional(optional&& rhs) DXLE_NOEXCEPT_IF(is_nothrow_move_constructible<T>::value)
  : OptionalBase<T>()
  {
    if (rhs.initialized()) {
        ::new (static_cast<void*>(dataptr())) T(std::move(*rhs));
        OptionalBase<T>::init_ = true;
    }
  }

  DXLE_CONSTEXPR_CLASS optional(const T& v) : OptionalBase<T>(v) {}

  DXLE_CONSTEXPR_CLASS optional(T&& v) : OptionalBase<T>(constexpr_move(v)) {}

  template <class... Args>
  explicit DXLE_CONSTEXPR_CLASS optional(in_place_t, Args&&... args)
  : OptionalBase<T>(in_place_t{}, constexpr_forward<Args>(args)...) {}

  template <class U, class... Args, TR2_OPTIONAL_REQUIRES(is_constructible<T, std::initializer_list<U>>)>
  OPTIONAL_CONSTEXPR_INIT_LIST explicit optional(in_place_t, std::initializer_list<U> il, Args&&... args)
  : OptionalBase<T>(in_place_t{}, il, constexpr_forward<Args>(args)...) {}

  // 20.5.4.2, Destructor
  ~optional() = default;

  // 20.5.4.3, assignment
  optional& operator=(nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
  {
    clear();
    return *this;
  }
  
  optional& operator=(const optional& rhs)
  {
    if      (initialized() == true  && rhs.initialized() == false) clear();
    else if (initialized() == false && rhs.initialized() == true)  initialize(*rhs);
    else if (initialized() == true  && rhs.initialized() == true)  contained_val() = *rhs;
    return *this;
  }
  
  optional& operator=(optional&& rhs)
  DXLE_NOEXCEPT_IF(is_nothrow_move_assignable<T>::value && is_nothrow_move_constructible<T>::value)
  {
    if      (initialized() == true  && rhs.initialized() == false) clear();
    else if (initialized() == false && rhs.initialized() == true)  initialize(std::move(*rhs));
    else if (initialized() == true  && rhs.initialized() == true)  contained_val() = std::move(*rhs);
    return *this;
  }

  template <class U>
  auto operator=(U&& v)
  -> typename enable_if
  <
    is_same<typename decay<U>::type, T>::value,
    optional&
  >::type
  {
    if (initialized()) { contained_val() = std::forward<U>(v); }
    else               { initialize(std::forward<U>(v));  }
    return *this;
  }
  
  
  template <class... Args>
  void emplace(Args&&... args)
  {
    clear();
    initialize(std::forward<Args>(args)...);
  }
  
  template <class U, class... Args>
  void emplace(initializer_list<U> il, Args&&... args)
  {
    clear();
    initialize<U, Args...>(il, std::forward<Args>(args)...);
  }
  
  // 20.5.4.4, Swap
  void swap(optional<T>& rhs) DXLE_NOEXCEPT_IF(is_nothrow_move_constructible<T>::value && DXLE_NOEXCEPT_EXPR(swap(declval<T&>(), declval<T&>())))
  {
    if      (initialized() == true  && rhs.initialized() == false) { rhs.initialize(std::move(**this)); clear(); }
    else if (initialized() == false && rhs.initialized() == true)  { initialize(std::move(*rhs)); rhs.clear(); }
    else if (initialized() == true  && rhs.initialized() == true)  { using std::swap; swap(**this, *rhs); }
  }

  // 20.5.4.5, Observers
  
  explicit DXLE_CONSTEXPR operator bool() const DXLE_NOEXCEPT_OR_NOTHROW{ return initialized(); }
  
  DXLE_CONSTEXPR T const* operator ->() const {
    return TR2_OPTIONAL_ASSERTED_EXPRESSION(initialized(), dataptr());
  }
  
# if OPTIONAL_HAS_MOVE_ACCESSORS == 1

  OPTIONAL_MUTABLE_CONSTEXPR T* operator ->() {
    assert (initialized());
    return dataptr();
  }
  
  constexpr T const& operator *() const& {
    return TR2_OPTIONAL_ASSERTED_EXPRESSION(initialized(), contained_val());
  }
  
  OPTIONAL_MUTABLE_CONSTEXPR T& operator *() & {
    assert (initialized());
    return contained_val();
  }
  
  OPTIONAL_MUTABLE_CONSTEXPR T&& operator *() && {
    assert (initialized());
    return constexpr_move(contained_val());
  }

  constexpr T const& value() const& {
    return initialized() ? contained_val() : (throw bad_optional_access("bad optional access"), contained_val());
  }
  
  OPTIONAL_MUTABLE_CONSTEXPR T& value() & {
    return initialized() ? contained_val() : (throw bad_optional_access("bad optional access"), contained_val());
  }
  
  OPTIONAL_MUTABLE_CONSTEXPR T&& value() && {
    if (!initialized()) throw bad_optional_access("bad optional access");
	return std::move(contained_val());
  }
  
# else

  T* operator ->() {
    assert (initialized());
    return dataptr();
  }
  
  DXLE_CONSTEXPR T const& operator *() const {
    return TR2_OPTIONAL_ASSERTED_EXPRESSION(initialized(), contained_val());
  }
  
  T& operator *() {
    assert (initialized());
    return contained_val();
  }
  
  DXLE_CONSTEXPR T const& value() const {
    return initialized() ? contained_val() : (throw bad_optional_access("bad optional access"), contained_val());
  }
  
  T& value() {
    return initialized() ? contained_val() : (throw bad_optional_access("bad optional access"), contained_val());
  }
  
# endif
  
# if OPTIONAL_HAS_THIS_RVALUE_REFS == 1

  template <class V>
  constexpr T value_or(V&& v) const&
  {
    return *this ? **this : detail_::convert<T>(constexpr_forward<V>(v));
  }
  
#   if OPTIONAL_HAS_MOVE_ACCESSORS == 1

  template <class V>
  OPTIONAL_MUTABLE_CONSTEXPR T value_or(V&& v) &&
  {
    return *this ? constexpr_move(const_cast<optional<T>&>(*this).contained_val()) : detail_::convert<T>(constexpr_forward<V>(v));
  }

#   else
 
  template <class V>
  T value_or(V&& v) &&
  {
    return *this ? constexpr_move(const_cast<optional<T>&>(*this).contained_val()) : detail_::convert<T>(constexpr_forward<V>(v));
  }
  
#   endif
  
# else
  
  template <class V>
  DXLE_CONSTEXPR T value_or(V&& v) const
  {
    return *this ? **this : detail_::convert<T>(constexpr_forward<V>(v));
  }

# endif

};


template <class T>
class optional<T&>
{
  static_assert( !std::is_same<T, nullopt_t>::value, "bad T" );
  static_assert( !std::is_same<T, in_place_t>::value, "bad T" );
  T* ref;
  
public:

  // 20.5.5.1, construction/destruction
  DXLE_CONSTEXPR_CLASS optional() DXLE_NOEXCEPT_OR_NOTHROW : ref(nullptr) {}
  
  DXLE_CONSTEXPR_CLASS optional(nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW : ref(nullptr) {}
   
  DXLE_CONSTEXPR_CLASS optional(T& v) DXLE_NOEXCEPT_OR_NOTHROW : ref(detail_::static_addressof(v)) {}
  
  optional(T&&) = delete;
  
  DXLE_CONSTEXPR_CLASS optional(const optional& rhs) DXLE_NOEXCEPT_OR_NOTHROW : ref(rhs.ref) {}
  
  explicit DXLE_CONSTEXPR_CLASS optional(in_place_t, T& v) DXLE_NOEXCEPT_OR_NOTHROW : ref(detail_::static_addressof(v)) {}
  
  explicit optional(in_place_t, T&&) = delete;
  
  ~optional() = default;
  
  // 20.5.5.2, mutation
  optional& operator=(nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW {
    ref = nullptr;
    return *this;
  }
  
  // optional& operator=(const optional& rhs) DXLE_NOEXCEPT_OR_NOTHROW {
    // ref = rhs.ref;
    // return *this;
  // }
  
  // optional& operator=(optional&& rhs) DXLE_NOEXCEPT_OR_NOTHROW {
    // ref = rhs.ref;
    // return *this;
  // }
  
  template <typename U>
  auto operator=(U&& rhs) DXLE_NOEXCEPT_OR_NOTHROW
  -> typename enable_if
  <
    is_same<typename decay<U>::type, optional<T&>>::value,
    optional&
  >::type
  {
    ref = rhs.ref;
    return *this;
  }
  
  template <typename U>
  auto operator=(U&& rhs) DXLE_NOEXCEPT_OR_NOTHROW
  -> typename enable_if
  <
    !is_same<typename decay<U>::type, optional<T&>>::value,
    optional&
  >::type
  = delete;
  
  void emplace(T& v) DXLE_NOEXCEPT_OR_NOTHROW {
    ref = detail_::static_addressof(v);
  }
  
  void emplace(T&&) = delete;
  
  
  void swap(optional<T&>& rhs) DXLE_NOEXCEPT_OR_NOTHROW
  {
    std::swap(ref, rhs.ref);
  }
    
  // 20.5.5.3, observers
  DXLE_CONSTEXPR T* operator->() const {
    return TR2_OPTIONAL_ASSERTED_EXPRESSION(ref, ref);
  }
  
  DXLE_CONSTEXPR T& operator*() const {
    return TR2_OPTIONAL_ASSERTED_EXPRESSION(ref, *ref);
  }
  
  DXLE_CONSTEXPR T& value() const {
    return ref ? *ref : (throw bad_optional_access("bad optional access"), *ref);
  }
  
  explicit DXLE_CONSTEXPR operator bool() const DXLE_NOEXCEPT_OR_NOTHROW{
    return ref != nullptr;
  }
  
  template <class V>
  DXLE_CONSTEXPR typename decay<T>::type value_or(V&& v) const
  {
    return *this ? **this : detail_::convert<typename decay<T>::type>(constexpr_forward<V>(v));
  }
};


template <class T>
class optional<T&&>
{
  static_assert( sizeof(T) == 0, "optional rvalue references disallowed" );
};


// 20.5.8, Relational operators
template <class T> DXLE_CONSTEXPR bool operator==(const optional<T>& x, const optional<T>& y)
{
  return bool(x) != bool(y) ? false : bool(x) == false ? true : *x == *y;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const optional<T>& x, const optional<T>& y)
{
  return !(x == y);
}

template <class T> DXLE_CONSTEXPR bool operator<(const optional<T>& x, const optional<T>& y)
{
  return (!y) ? false : (!x) ? true : *x < *y;
}

template <class T> DXLE_CONSTEXPR bool operator>(const optional<T>& x, const optional<T>& y)
{
  return (y < x);
}

template <class T> DXLE_CONSTEXPR bool operator<=(const optional<T>& x, const optional<T>& y)
{
  return !(y < x);
}

template <class T> DXLE_CONSTEXPR bool operator>=(const optional<T>& x, const optional<T>& y)
{
  return !(x < y);
}


// 20.5.9, Comparison with nullopt
template <class T> DXLE_CONSTEXPR bool operator==(const optional<T>& x, nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return (!x);
}

template <class T> DXLE_CONSTEXPR bool operator==(nullopt_t, const optional<T>& x) DXLE_NOEXCEPT_OR_NOTHROW
{
  return (!x);
}

template <class T> DXLE_CONSTEXPR bool operator!=(const optional<T>& x, nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return bool(x);
}

template <class T> DXLE_CONSTEXPR bool operator!=(nullopt_t, const optional<T>& x) DXLE_NOEXCEPT_OR_NOTHROW
{
  return bool(x);
}

template <class T> DXLE_CONSTEXPR bool operator<(const optional<T>&, nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return false;
}

template <class T> DXLE_CONSTEXPR bool operator<(nullopt_t, const optional<T>& x) DXLE_NOEXCEPT_OR_NOTHROW
{
  return bool(x);
}

template <class T> DXLE_CONSTEXPR bool operator<=(const optional<T>& x, nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return (!x);
}

template <class T> DXLE_CONSTEXPR bool operator<=(nullopt_t, const optional<T>&) DXLE_NOEXCEPT_OR_NOTHROW
{
  return true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const optional<T>& x, nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return bool(x);
}

template <class T> DXLE_CONSTEXPR bool operator>(nullopt_t, const optional<T>&) DXLE_NOEXCEPT_OR_NOTHROW
{
  return false;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const optional<T>&, nullopt_t) DXLE_NOEXCEPT_OR_NOTHROW
{
  return true;
}

template <class T> DXLE_CONSTEXPR bool operator>=(nullopt_t, const optional<T>& x) DXLE_NOEXCEPT_OR_NOTHROW
{
  return (!x);
}



// 20.5.10, Comparison with T
template <class T> DXLE_CONSTEXPR bool operator==(const optional<T>& x, const T& v)
{
  return bool(x) ? *x == v : false;
}

template <class T> DXLE_CONSTEXPR bool operator==(const T& v, const optional<T>& x)
{
  return bool(x) ? v == *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const optional<T>& x, const T& v)
{
  return bool(x) ? *x != v : true;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const T& v, const optional<T>& x)
{
  return bool(x) ? v != *x : true;
}

template <class T> DXLE_CONSTEXPR bool operator<(const optional<T>& x, const T& v)
{
  return bool(x) ? *x < v : true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const T& v, const optional<T>& x)
{
  return bool(x) ? v > *x : true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const optional<T>& x, const T& v)
{
  return bool(x) ? *x > v : false;
}

template <class T> DXLE_CONSTEXPR bool operator<(const T& v, const optional<T>& x)
{
  return bool(x) ? v < *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const optional<T>& x, const T& v)
{
  return bool(x) ? *x >= v : false;
}

template <class T> DXLE_CONSTEXPR bool operator<=(const T& v, const optional<T>& x)
{
  return bool(x) ? v <= *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator<=(const optional<T>& x, const T& v)
{
  return bool(x) ? *x <= v : true;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const T& v, const optional<T>& x)
{
  return bool(x) ? v >= *x : true;
}


// Comparison of optional<T&> with T
template <class T> DXLE_CONSTEXPR bool operator==(const optional<T&>& x, const T& v)
{
  return bool(x) ? *x == v : false;
}

template <class T> DXLE_CONSTEXPR bool operator==(const T& v, const optional<T&>& x)
{
  return bool(x) ? v == *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const optional<T&>& x, const T& v)
{
  return bool(x) ? *x != v : true;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const T& v, const optional<T&>& x)
{
  return bool(x) ? v != *x : true;
}

template <class T> DXLE_CONSTEXPR bool operator<(const optional<T&>& x, const T& v)
{
  return bool(x) ? *x < v : true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const T& v, const optional<T&>& x)
{
  return bool(x) ? v > *x : true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const optional<T&>& x, const T& v)
{
  return bool(x) ? *x > v : false;
}

template <class T> DXLE_CONSTEXPR bool operator<(const T& v, const optional<T&>& x)
{
  return bool(x) ? v < *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const optional<T&>& x, const T& v)
{
  return bool(x) ? *x >= v : false;
}

template <class T> DXLE_CONSTEXPR bool operator<=(const T& v, const optional<T&>& x)
{
  return bool(x) ? v <= *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator<=(const optional<T&>& x, const T& v)
{
  return bool(x) ? *x <= v : true;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const T& v, const optional<T&>& x)
{
  return bool(x) ? v >= *x : true;
}

// Comparison of optional<T const&> with T
template <class T> DXLE_CONSTEXPR bool operator==(const optional<const T&>& x, const T& v)
{
  return bool(x) ? *x == v : false;
}

template <class T> DXLE_CONSTEXPR bool operator==(const T& v, const optional<const T&>& x)
{
  return bool(x) ? v == *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const optional<const T&>& x, const T& v)
{
  return bool(x) ? *x != v : true;
}

template <class T> DXLE_CONSTEXPR bool operator!=(const T& v, const optional<const T&>& x)
{
  return bool(x) ? v != *x : true;
}

template <class T> DXLE_CONSTEXPR bool operator<(const optional<const T&>& x, const T& v)
{
  return bool(x) ? *x < v : true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const T& v, const optional<const T&>& x)
{
  return bool(x) ? v > *x : true;
}

template <class T> DXLE_CONSTEXPR bool operator>(const optional<const T&>& x, const T& v)
{
  return bool(x) ? *x > v : false;
}

template <class T> DXLE_CONSTEXPR bool operator<(const T& v, const optional<const T&>& x)
{
  return bool(x) ? v < *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const optional<const T&>& x, const T& v)
{
  return bool(x) ? *x >= v : false;
}

template <class T> DXLE_CONSTEXPR bool operator<=(const T& v, const optional<const T&>& x)
{
  return bool(x) ? v <= *x : false;
}

template <class T> DXLE_CONSTEXPR bool operator<=(const optional<const T&>& x, const T& v)
{
  return bool(x) ? *x <= v : true;
}

template <class T> DXLE_CONSTEXPR bool operator>=(const T& v, const optional<const T&>& x)
{
  return bool(x) ? v >= *x : true;
}


// 20.5.12, Specialized algorithms
template <class T>
void swap(optional<T>& x, optional<T>& y) DXLE_NOEXCEPT_IF_EXPR(x.swap(y))
{
  x.swap(y);
}


template <class T>
DXLE_CONSTEXPR_CLASS optional<typename decay<T>::type> make_optional(T&& v)
{
  return optional<typename decay<T>::type>(constexpr_forward<T>(v));
}

template <class X>
DXLE_CONSTEXPR_CLASS optional<X&> make_optional(reference_wrapper<X> v)
{
  return optional<X&>(v.get());
}


} // namespace experimental
} // namespace std

namespace std
{
  template <typename T>
  struct hash<std::experimental::optional<T>>
  {
    typedef typename hash<T>::result_type result_type;
    typedef std::experimental::optional<T> argument_type;
    
    DXLE_CONSTEXPR result_type operator()(argument_type const& arg) const {
      return arg ? std::hash<T>{}(*arg) : result_type{};
    }
  };
  
  template <typename T>
  struct hash<std::experimental::optional<T&>>
  {
    typedef typename hash<T>::result_type result_type;
    typedef std::experimental::optional<T&> argument_type;
    
    DXLE_CONSTEXPR result_type operator()(argument_type const& arg) const {
      return arg ? std::hash<T>{}(*arg) : result_type{};
    }
  };
}

# undef TR2_OPTIONAL_REQUIRES
# undef TR2_OPTIONAL_ASSERTED_EXPRESSION

# endif //___OPTIONAL_HPP___
