#pragma once
#include "SizeTag.h"
#include <set>

namespace jsonsl {


// set
template <class Archive, class K, class C, class A>
void save_array(Archive& ar, std::set<K, C, A>& set)
{
	ar(make_size_tag(set.size()));
	for (auto& v : set) {
		ar(v);
	}
}

template <class Archive, class K, class C, class A>
void load_array(Archive& ar, std::set<K, C, A>& set)
{
	size_t size;
	ar(make_size_tag(size));

	set.clear();

	auto hint = set.begin();
	for (size_t i = 0; i < size; ++i){
		std::set<K, C, A>::key_type key;

		ar(key);
		hint = set.emplace_hint(hint, std::move(key));
	}
}


// multiset <-- setのコピペ
template <class Archive, class K, class C, class A>
void save_array(Archive& ar, std::multiset<K, C, A>& multiset)
{
	ar(make_size_tag(multiset.size()));
	for (auto& v : multiset) {
		ar(v);
	}
}

template <class Archive, class K, class C, class A>
void load_array(Archive& ar, std::multiset<K, C, A>& multiset)
{
	size_t size;
	ar(make_size_tag(size));

	multiset.clear();

	auto hint = multiset.begin();
	for (size_t i = 0; i < size; ++i) {
		std::multiset<K, C, A>::key_type key;

		ar(key);
		hint = multiset.emplace_hint(hint, std::move(key));
	}
}

} // namespace jsonsl
