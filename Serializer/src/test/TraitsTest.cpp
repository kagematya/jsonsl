﻿#include "traits.h"
#include "JSONOutputArchive.h"
#include <iostream>
using namespace std;

struct Hoge {
	int a;

	void serialize(JSONOutputArchive& archive) {
		archive(make_nvp("a", a));
	}
};


void traitsTest()
{
	cout << "has_memfun_serialize<Hoge, JSONOutputArchive>::value " << has_memfun_serialize<Hoge, JSONOutputArchive>::value << endl;
	cout << "has_memfun_serialize<int, JSONOutputArchive>::value " << has_memfun_serialize<int, JSONOutputArchive>::value << endl;
}