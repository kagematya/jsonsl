#pragma once
#include "SizeTag.h"
#include <unordered_set>

namespace jsonsl {


// unordered_set
template <class Archive, class K, class H, class P, class A>
void save_array(Archive& ar, std::unordered_set<K, H, P, A>& unordered_set)
{
	ar(make_size_tag(unordered_set.size()));

	for (auto& v : unordered_set) {
		ar(v);
	}
}

template <class Archive, class K, class H, class P, class A>
void load_array(Archive& ar, std::unordered_set<K, H, P, A>& unordered_set)
{
	size_t size;
	ar(make_size_tag(size));

	unordered_set.clear();
	unordered_set.reserve(size);

	for (size_t i = 0; i < size; ++i){
		typename std::unordered_set<K, H, P, A>::key_type key;

		ar(key);
		unordered_set.emplace(std::move(key));
	}
}


// unordered_multiset <-- unordered_setのコピペ
template <class Archive, class K, class H, class P, class A>
void save_array(Archive& ar, std::unordered_multiset<K, H, P, A>& unordered_multiset)
{
	ar(make_size_tag(unordered_multiset.size()));

	for (auto& v : unordered_multiset) {
		ar(v);
	}
}

template <class Archive, class K, class H, class P, class A>
void load_array(Archive& ar, std::unordered_multiset<K, H, P, A>& unordered_multiset)
{
	size_t size;
	ar(make_size_tag(size));

	unordered_multiset.clear();
	unordered_multiset.reserve(size);

	for (size_t i = 0; i < size; ++i) {
		typename std::unordered_multiset<K, H, P, A>::key_type key;

		ar(key);
		unordered_multiset.emplace(std::move(key));
	}
}

} // namespace jsonsl
