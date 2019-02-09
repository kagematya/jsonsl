#pragma once


/**
 * 配列のサイズを取得するための構造
 */
struct SizeTag {
	SizeTag(size_t& size) : m_size(size){}
	size_t& m_size;
};

SizeTag make_size_tag(size_t& size) {
	return SizeTag(size);
}
