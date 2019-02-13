#pragma once

namespace jsonsl {

/**
 * 配列のサイズを取得するための構造
 */
template<class T>
struct SizeTag {
	SizeTag(T& size) : m_size(size){}
	T& m_size;
};

template<class T>
SizeTag<T> make_size_tag(T& size) {
	return { size };
}

template<class T>
SizeTag<T> make_size_tag(T&& size) {
	return { size };	// 一時変数用
}

} // namespace jsonsl
