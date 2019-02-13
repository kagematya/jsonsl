#pragma once
#include "SizeTag.h"
#include <vector>
//todo:vector<bool>

namespace jsonsl {


template <class Archive, class T, class A>
void save_array(Archive& ar, std::vector<T, A>& vector)
{
	ar(make_size_tag(vector.size()));
	for (auto& v : vector) {
		ar(v);
	}
}

template <class Archive, class T, class A>
void load_array(Archive& ar, std::vector<T, A>& vector)
{
	size_t size;
	ar(make_size_tag(size));
	
	vector.resize(size);
	for (auto& v : vector) {
		ar(v);
	}
}

} // namespace jsonsl
