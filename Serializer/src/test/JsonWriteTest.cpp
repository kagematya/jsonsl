#include "JSONOutputArchive.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

namespace{
struct Hoge {
	//Hoge(int i) {}
	int a = 999;
	const char* c = "bbb";
	double d = 123.4;

	void serialize(JSONOutputArchive& archive) {
		archive(make_nvp("a", a));
		archive(make_nvp("c", c));
		archive(make_nvp("d", d));
	}
};

struct Fuga {
	Hoge h;
	Hoge hh;
	void serialize(JSONOutputArchive& archive) {
		archive(make_nvp("h", h));
		archive(make_nvp("hh", hh));
	}
};

struct Vector2 {
	int x = 3;
	int y = 4;
};

// 非侵入型
void serialize(JSONOutputArchive& archive, Vector2& v)
{
	archive(make_nvp("x", v.x));
	archive(make_nvp("y", v.y));
}


template<class T, class A>
void serialize_array(JSONOutputArchive& archive, vector<T, A>& v)
{
	archive(make_size_tag(v.size()));
	for (T& t : v) {
		archive(t);
	}
}
} //namespace

void jsonWriteTest() {
	ostringstream s;
	{
		JSONOutputArchive archive(s);
		//int val = 3;
		//archive(val);
		//archive("aaa");
		//char a = 'a';	// intになるっぽい
		//archive(a);
		//size_t size = 9;	// unsignedになるっぽい
		//archive(size);
		//archive(string("aaa"));

		int val = 333;
		archive(make_nvp("name1", val));
		archive(make_nvp("name2", val));
		archive(make_nvp("name3", 999));
		archive(make_nvp("name4", 123));
		archive(make_nvp("name5", "aaa"));
		archive(make_nvp("name6", string("str")));
		archive(make_nvp("name7", 3.3f));
		archive(make_nvp("name8", 3.333));

		Hoge hoge;
		archive(make_nvp("hoge", hoge));

		Fuga fuga;
		archive(make_nvp("fuga", fuga));

		Vector2 vec;
		archive(make_nvp("vec", vec));

		vector<int> iii = { 1,2,3,4,5 };
		archive(make_nvp("iii", iii));

		vector<Fuga> fff(3);
		archive(make_nvp("fff", fff));

		vector<Vector2> vvv(3);
		archive(make_nvp("vvv", vvv));

		vector<vector<int>> vecvec = { { 1,2,3 },{ 4,5,6 } };
		archive(make_nvp("vecvec", vecvec));
	}

	const string& result = s.str();
	cout << result;
}

