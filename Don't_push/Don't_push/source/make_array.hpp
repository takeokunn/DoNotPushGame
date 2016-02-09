#pragma once
#include <array>
#include <functional>
namespace std_future {
	//https://gist.github.com/lichray/6034753
	template <typename... T>
	using common_type_t = typename std::common_type<T...>::type;

	template <typename T>
	using remove_cv_t = typename std::remove_cv<T>::type;

	template <bool, typename T, typename... U>
	struct lazy_conditional_c;

	template <typename T>
	struct lazy_conditional_c<true, T>
	{
		using type = typename T::type;
	};

	template <typename T, typename U>
	struct lazy_conditional_c<true, T, U>
	{
		using type = typename T::type;
	};

	template <typename T, typename U>
	struct lazy_conditional_c<false, T, U>
	{
		using type = typename U::type;
	};

	template <typename V, typename T, typename... U>
	using if_else = lazy_conditional_c<V::value, T, U...>;

	template <typename V, typename T, typename... U>
	using If = typename if_else<V, T, U...>::type;

	template <typename T>
	struct identity_of
	{
		using type = T;
	};

	template <template <typename> class F, typename... T>
	struct no_type : std::true_type {};

	template <template <typename> class F, typename T1, typename... T2>
	struct no_type<F, T1, T2...> :
		std::integral_constant
		<
		bool,
		!F<T1>::value && no_type<F, T2...>::value
		>
	{};

	template <template <typename> class F, template <typename> class G>
	struct composed
	{
		template <typename T>
		using call = F<typename G<T>::type>;
	};

	template <typename T>
	struct _is_reference_wrapper : std::false_type {};

	template <typename T>
	struct _is_reference_wrapper<std::reference_wrapper<T>> : std::true_type {};

	template <typename T>
	using is_reference_wrapper =
		composed<_is_reference_wrapper, std::remove_cv>::call<T>;

	template <typename V = void, typename... T>
	constexpr auto make_array(T&&... t)
		->std::array
		<
		If
		<
		std::is_void<V>,
		std::common_type<T...>,
		identity_of<V>
		>,
		sizeof...(T)
		>
	{
		static_assert(!std::is_void<V>() ||
			no_type
			<
			composed
			<
			is_reference_wrapper,
			std::decay
			>
			::call,
			T...
			>(), "T shall not be reference_wrapper");

		return{ { std::forward<T>(t)... } };
	}

	template <size_t... I>
	struct _indices {};

	template <size_t N, size_t... I>
	struct _build_indices : _build_indices<N - 1, N - 1, I...> {};

	template <size_t... I>
	struct _build_indices<0, I...> : _indices<I...> {};

	template <typename T, size_t N, size_t... I>
	constexpr auto _to_array(T(&arr)[N], _indices<I...>)
		->std::array<remove_cv_t<T>, N>
	{
		return{ { arr[I]... } };
	}

	template <typename T, size_t N>
	constexpr auto to_array(T(&arr)[N])
		->std::array<remove_cv_t<T>, N>
	{
		return _to_array(arr, _build_indices<N>());
	}
}
