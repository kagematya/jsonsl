#pragma once
#include "SizeTag.h"
#include <deque>

namespace jsonsl {


template <class Archive, class T, class A>
void save_array(Archive& ar, std::deque<T, A>& deque)
{
	ar( make_size_tag(deque.size()) );
	
	for (auto& v : deque) {
		ar(v);
	}
}


template <class Archive, class T, class A>
void load_array(Archive& ar, std::deque<T, A>& deque )
{
	size_t size;
	ar(make_size_tag(size));
	
	deque.resize(size);
	for (auto& v : deque) {
		ar(v);
	}
}

} // namespace jsonsl
