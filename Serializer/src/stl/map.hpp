#pragma once
#include "SizeTag.h"
#include "pair.hpp"
#include <map>


template <class Archive, class K, class T, class C, class A>
void save_array(Archive& ar, std::map<K, T, C, A>& map)
{
	ar(make_size_tag(map.size()));

	for (auto& v : map) {
		ar(v);
	}
}

template <class Archive, class K, class T, class C, class A>
void load_array(Archive& ar, std::map<K, T, C, A>& map)
{
	size_t size;
	ar(make_size_tag(size));

	map.clear();

	for (size_t i = 0; i < size; ++i){
		std::pair<K, T> v;
		
		ar(v);
		map.insert(std::move(v));
	}
}
