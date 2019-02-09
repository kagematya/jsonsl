#include "JSONInputArchive.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#if 0
struct Hoge {
	//Hoge(int i) {}
	int a = 999;
	const char* c = "bbb";
	double d = 123.4;

	void serialize(JSONInputArchive& archive) {
		archive(make_nvp("a", a));
		archive(make_nvp("c", c));
		archive(make_nvp("d", d));
	}
};

struct Fuga {
	Hoge h;
	Hoge hh;
	void serialize(JSONInputArchive& archive) {
		archive(make_nvp("h", h));
		archive(make_nvp("hh", hh));
	}
};

struct Vector2 {
	int x = 3;
	int y = 4;
};

// 非侵入型
void serialize(JSONInputArchive& archive, Vector2& v)
{
	archive(make_nvp("x", v.x));
	archive(make_nvp("y", v.y));
}


template<class T, class A>
void serialize_array(JSONInputArchive& archive, vector<T, A>& v)
{
	//archive(size_tag(v.size()));
	for (T& t : v) {
		archive(t);
	}
}
#endif

void jsonReadTest() {
#if 0
	istringstream s;
	{
		JSONInputArchive archive(s);
		int val = 333;
		archive(make_nvp("name", val));
		archive(make_nvp("name", val));
		archive(make_nvp("name", 999));
		archive(make_nvp("name", 123));
		archive(make_nvp("name", "aaa"));
		archive(make_nvp("name", string("str")));
		archive(make_nvp("name", 3.3f));
		archive(make_nvp("name", 3.333));

		//Hoge hoge;
		//archive(make_nvp("hoge", hoge));
	}

	const string& result = s.str();
	cout << result;
#endif
}

