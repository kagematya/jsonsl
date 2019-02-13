#pragma once
#include "SizeTag.h"
#include <list>

namespace jsonsl {


template <class Archive, class T, class A>
void save_array(Archive& ar, std::list<T, A>& list)
{
	ar( make_size_tag(list.size()) );
	for (auto& v : list) {
		ar(v);
	}
}

template <class Archive, class T, class A>
void load_array(Archive& ar, std::list<T, A>& list)
{
	size_t size;
	ar( make_size_tag(size) );
	
	list.resize(size);
	for (auto& v : list) {
		ar(v);
	}
}

} // namespace jsonsl
