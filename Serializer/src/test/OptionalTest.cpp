#include "JSONInputArchive.h"
#include "JSONOutputArchive.h"
#include <iostream>
#include <sstream>
using namespace std;

static const char* s_json = R"(
{
    "hoge" : {
		"a" : 999,
		"c" : 777
	}
}
)";

namespace {
struct Hoge {
	int a = 111;
	int b = 222;
	int c = 333;

	template<class Archive>
	void serialize(Archive& ar) {
		ar(make_optional_nvp("a", a));
		ar(make_optional_nvp("b", b));
		ar(make_optional_nvp("c", c));
	}
};
} // namespace


void optionalTest()
{
	ostringstream oss;
	{
		JSONOutputArchive archive(oss);

		Hoge hoge;
		archive(make_nvp("hoge", hoge));
	}
	const string& result = oss.str();
	cout << result << endl;
	cout << endl;


	istringstream iss(s_json);
	{
		JSONInputArchive archive(iss);

		Hoge hoge;
		archive(make_nvp("hoge", hoge));

		cout << "a:" << hoge.a << endl;
		cout << "b:" << hoge.b << endl;
		cout << "c:" << hoge.c << endl;
	}
}

