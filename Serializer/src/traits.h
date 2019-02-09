#pragma once

#include <type_traits>


// T型がserialize()というメンバ関数を持っているかどうかを判別
template<typename T, typename Archive>
class has_memfun_serialize {
private:
	template<typename U, typename A>
	static auto check(U v, A& a) -> decltype(v.serialize(a), std::true_type());

	static std::false_type check(...);		// 定義がないときはこちらが有効になる

public:
	static constexpr bool value = decltype(check(std::declval<T>(), std::declval<Archive&>()))::value;
};


// T型に対してserialize(Arcive&, T&)という関数が用意されているかどうかを判定
template<typename T, typename Archive>
class has_fun_serialize {
private:
	template <typename U, typename A>
	static auto check(U& v, A& a) -> decltype(serialize(a, v), std::true_type());

	static std::false_type check(...);		// 定義がないときはこちらが有効になる

public:
	static constexpr bool value = decltype(check(std::declval<T&>(), std::declval<Archive&>()))::value;
};

// T型に対してserialize_array(Arcive&, T&)という関数が用意されているかどうかを判定
template<typename T, typename Archive>
class has_fun_serialize_array {
private:
	template <typename U, typename A>
	static auto check(U& v, A& a) -> decltype(serialize_array(a, v), std::true_type());

	static std::false_type check(...);		// 定義がないときはこちらが有効になる

public:
	static constexpr bool value = decltype(check(std::declval<T&>(), std::declval<Archive&>()))::value;
};
