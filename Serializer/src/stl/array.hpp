#pragma once
#include <array>

namespace jsonsl {


template <class Archive, class T, size_t N>
void save_array(Archive& ar, std::array<T, N>& array)
{
	for (auto& v : array) {
		ar(v);
	}
}

template <class Archive, class T, size_t N>
void load_array(Archive& ar, std::array<T, N>& array)
{
	for (auto& v : array) {
		ar(v);
	}
}

} // namespace jsonsl
