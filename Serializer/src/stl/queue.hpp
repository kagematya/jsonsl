#pragma once
#include "NameValuePair.h"
#include <queue>

//todo:std::priority_queue


template <class Archive, class T, class C>
void save(Archive& ar, std::queue<T, C>& queue)
{
	const C& container = queue._Get_container();
	C* p = const_cast<C*>(&container);
	ar(make_nvp("container", *p));
}

template <class Archive, class T, class C>
void load(Archive& ar, std::queue<T, C>& queue)
{
	C container;
	ar(make_nvp("container", container));

	queue = std::queue<T, C>( std::move(container) );
}

