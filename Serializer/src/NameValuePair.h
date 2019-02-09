#pragma once


/**
 * key-valueの構造
 */
template<class T>
class NameValuePair {
public:
	NameValuePair(const char* name, T& value)
		: m_name(name)
		, m_value(value)
	{
	}

	const char* m_name;
	T& m_value;
};

template <class T>
NameValuePair<T> make_nvp(const char* name, T& value)
{
	return { name, value };
}

template <class T>
NameValuePair<T> make_nvp(const char* name, T&& value)
{
	return { name, value };	// 一時変数用だけど残すかどうか微妙
}

