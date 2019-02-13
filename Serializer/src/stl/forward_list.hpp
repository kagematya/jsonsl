#pragma once
#include "SizeTag.h"
#include <algorithm>
#include <forward_list>

namespace jsonsl {


template <class Archive, class T, class A>
void save_array(Archive& ar, std::forward_list<T, A>& forward_list)
{
	// size()が用意されてないのでこれでなんとかする
	size_t size = std::distance(forward_list.begin(), forward_list.end());
	ar(make_size_tag(size));
	
	for (auto& v : forward_list) {
		ar(v);
	}
}

template <class Archive, class T, class A>
void load_array(Archive& ar, std::forward_list<T, A>& forward_list)
{
	size_t size;
	ar(make_size_tag(size));
	
	forward_list.resize(size);
	for (auto& v : forward_list) {
		ar(v);
	}
}

} // namespace jsonsl
