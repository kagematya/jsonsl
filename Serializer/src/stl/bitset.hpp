#pragma once
#include "NameValuePair.h"
#include <bitset>

namespace jsonsl {


template <class Archive, size_t N>
void save(Archive& ar, std::bitset<N>& bits)
{
	ar(make_nvp("data", bits.to_string()));
}

template <class Archive, size_t N>
void load(Archive& ar, std::bitset<N>& bits)
{
	std::string data;
	ar(make_nvp("data", data));
	bits = std::bitset<N>(data);
}

} // namespace jsonsl
