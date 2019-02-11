#pragma once


/**
 * key-valueの構造。keyがないときに読み取りをスキップする
 */
template<class T>
class OptionalNameValuePair {
public:
	OptionalNameValuePair(const char* name, T& value)
		: m_name(name)
		, m_value(value)
	{
	}

	const char* m_name;
	T& m_value;
};

template <class T>
OptionalNameValuePair<T> make_optional_nvp(const char* name, T& value)
{
	return { name, value };
}

template <class T>
OptionalNameValuePair<T> make_optional_nvp(const char* name, T&& value)
{
	return { name, value };	// 一時変数用だけど残すかどうか微妙
}

