#pragma once
#include "SizeTag.h"
#include "pair.hpp"
#include <unordered_map>


template <class Archive, class K, class T, class H, class P, class A>
void save_array(Archive& ar, std::unordered_map<K, T, H, P, A>& unordered_map)
{
	ar(make_size_tag(unordered_map.size()));

	for (auto& v : unordered_map) {
		ar(v);
	}
}

template <class Archive, class K, class T, class H, class P, class A>
void load_array(Archive& ar, std::unordered_map<K, T, H, P, A>& unordered_map)
{
	size_t size;
	ar(make_size_tag(size));

	unordered_map.clear();

	for (size_t i = 0; i < size; ++i) {
		std::pair<K, T> v;

		ar(v);
		unordered_map.insert(std::move(v));
	}
}
