#pragma once
#include "NameValuePair.h"
#include <utility>

template <class Archive, class T1, class T2>
void serialize(Archive& ar, std::pair<T1, T2>& pair)
{
	ar(make_nvp("first", pair.first));
	ar(make_nvp("second", pair.second));
}

