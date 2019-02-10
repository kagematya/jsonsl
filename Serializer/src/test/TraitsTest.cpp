#include "traits.h"
#include "JSONOutputArchive.h"
#include <iostream>
using namespace std;

namespace {
struct Hoge {
	int a;

	void serialize(JSONOutputArchive& archive) {
		archive(make_nvp("a", a));
	}
};
struct Fuga {
	int a;

	void save(JSONOutputArchive& archive) {
		archive(make_nvp("a", a));
	}
	void load(JSONOutputArchive& archive) {
		archive(make_nvp("a", a));
	}
};
} //namespace

void traitsTest()
{
	cout << "has_memfun_serialize<Hoge, JSONOutputArchive>::value " << has_memfun_serialize<Hoge, JSONOutputArchive>::value << endl;
	cout << "has_memfun_serialize<int, JSONOutputArchive>::value " << has_memfun_serialize<int, JSONOutputArchive>::value << endl;

	cout << "has_memfun_serialize<Fuga, JSONOutputArchive>::value " << has_memfun_serialize<Fuga, JSONOutputArchive>::value << endl;
	cout << "has_memfun_save<Fuga, JSONOutputArchive>::value " << has_memfun_save<Fuga, JSONOutputArchive>::value << endl;
	cout << "has_memfun_load<Fuga, JSONOutputArchive>::value " << has_memfun_load<Fuga, JSONOutputArchive>::value << endl;
}
