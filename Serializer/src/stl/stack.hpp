#pragma once
#include "NameValuePair.h"
#include <stack>


template <class Archive, class T, class C>
void save(Archive& ar, std::stack<T, C>& stack)
{
	const C& container = stack._Get_container();
	C* p = const_cast<C*>(&container);
	ar(make_nvp("container", *p));
}

template <class Archive, class T, class C>
void load(Archive& ar, std::stack<T, C>& stack)
{
	C container;
	ar(make_nvp("container", container));
	stack = std::stack<T, C>( std::move(container) );
}
