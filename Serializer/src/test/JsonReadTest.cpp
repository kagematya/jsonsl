#include "JSONInputArchive.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

static const char* s_json = R"(
{
    "string" : "hogehoge",
    "number" : 123,
    "array" : [0,1,2,3,4,5],
    "hoge" : {
        "a" : 111,
        "s" : "sssss",
        "d" : 0.123
    },
	"fuga" : {
		"h" : {
	        "a" : 222,
	        "s" : "ddddd",
	        "d" : 0.321
	    },
		"hh" : {
	        "a" : 333,
	        "s" : "fffff",
	        "d" : 0.234
	    }
	},
	"vec2" : {
		"x" : 888,
		"y" : 777
	},
	"arrayarray" : [[0,1,2,3,4,5], [6,7,8,9,10]]
}
)";

namespace{
struct Hoge {
	int a = 999;
	string s = "bbb";
	double d = 123.4;

	void serialize(JSONInputArchive& archive) {
		archive(make_nvp("a", a));
		archive(make_nvp("s", s));
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
	size_t size;
	archive(make_size_tag(size));

	v.resize(size);
	for (T& t : v) {
		archive(t);
	}
}

// load版
struct Piyo {
	int a = 999;
	string s = "bbb";
	double d = 123.4;

	void load(JSONInputArchive& archive) {
		archive(make_nvp("a", a));
		archive(make_nvp("s", s));
		archive(make_nvp("d", d));
	}
	//void serialize(JSONInputArchive& archive) {}		// 両方定義するとコンパイルエラーになる
};
} //namespace

void jsonReadTest() {

	istringstream s(s_json);
	{
		JSONInputArchive archive(s);
		string str;
		int num;

		archive(make_nvp("string", str));
		archive(make_nvp("number", num));

		//struct Obj {

		//};
		//Obj obj;
		//archive(make_nvp("object", obj));

		cout << "str:" << str << endl;
		cout << "num:" << num << endl;

		Hoge h;
		archive(make_nvp("hoge", h));

		Fuga f;
		archive(make_nvp("fuga", f));
		cout << f.hh.d << endl;

		Vector2 vec2;
		archive(make_nvp("vec2", vec2));
		cout << "Vec2(" << vec2.x << ", " << vec2.y << ")" << endl;

		vector<int> arr;
		archive(make_nvp("array", arr));
		for (int i : arr) {
			cout << i << ", ";
		}
		cout << endl;

		vector<vector<int>> arrarr;
		archive(make_nvp("arrayarray", arrarr));
		for (auto& ar : arrarr) {
			for (int i : ar) {
				cout << i << ", ";
			}
			cout << endl;
		}
		cout << endl;

		Piyo piyo;
		archive(make_nvp("hoge", piyo));
		cout << "piyo:" << piyo.a << ", " << piyo.s << ", " << piyo.d << endl;

		//int val;
		//archive(make_nvp("pointer", &val));	// これはstatic_assertになる
	}
}

