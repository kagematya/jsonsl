#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include <iostream>
#include <sstream>
#include <vector>

#include "JSONOutputArchive.h"

using namespace std;
using namespace rapidjson;


static const char* s_json = R"(
{
    "string" : "hogehoge",
    "number" : 123,
    "array" : [0,1,2,3,4,5],
    "object" : {
        "foo" : "bar",
        "baz" : 456,
        "double" : 0.123
    }
}
)";


void rapidjson_test()
{
	Document doc;

	doc.Parse(s_json);
	if (doc.HasParseError()) {
		cout << "HasParseError" << endl;
		return;
	}

	const char* str = doc["string"].GetString();
	cout << str << endl;
	
	int num = doc["number"].GetInt();
	cout << num;
	
	const Value& arr = doc["array"];
	SizeType size = arr.Size();

	for (SizeType i = 0; i < size; i++) {
		cout << arr[i].GetInt() << ", ";
	}
	cout << endl;
	
	{
		const Value& obj = doc["object"];

		// メンバを全て調べる
		for (Value::ConstMemberIterator it = obj.MemberBegin(); it != obj.MemberEnd(); it++){
			const char* name = it->name.GetString();
			const Value& value = it->value;

			cout << "name(" << name << "), ";

			Type type = value.GetType();
			switch (type) {
			case kStringType:
				cout << "value(" << value.GetString() << ")" << endl;
				break;

			case kNumberType:
				if (value.IsDouble())
					cout << "value(" << value.GetDouble() << ")" << endl;
				else
					cout << "value(" << value.GetInt() << ")" << endl;
				break;

			default:
				cout << "value(" << "type=" << type << ")" << endl;	//他のタイプもあるよ！
				break;
			}
		}
	}
}


void json_writer()
{
	ostringstream s;
	OStreamWrapper osw(s);
	Writer<OStreamWrapper> writer(osw);

	//StringBuffer s;
	//Writer<StringBuffer> writer(s);

	//PrettyWriter<StringBuffer> writer(s);
	//writer.SetIndent('\t', 1);


	writer.StartObject();

	writer.Key("key");
	writer.String("value");

	writer.Key("object");
	writer.StartObject();
		writer.Key("key");
		writer.Int(123);
	writer.EndObject();
	
	writer.Key("array");
	writer.StartArray();
		writer.Int(1);
		writer.Int(2);
		writer.Int(3);
		writer.Int(4);
		writer.Int(5);
	writer.EndArray();

	writer.EndObject();

	//const char* result = s.GetString();
	osw.Flush();
	const string& result = s.str();
	cout << result << endl;
}


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

void jsonoutputarchive() {
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
		archive(make_nvp("name", val));
		archive(make_nvp("name", val));
		archive(make_nvp("name", 999));
		archive(make_nvp("name", 123));
		archive(make_nvp("name", "aaa"));
		archive(make_nvp("name", string("str")));
		archive(make_nvp("name", 3.3f));
		archive(make_nvp("name", 3.333));
		
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

		vector<vector<int>> vecvec = { {1,2,3},{4,5,6} };
		archive(make_nvp("vecvec", vecvec));
	}

	const string& result = s.str();
	cout << result;
}


template<typename T, enable_if_t<is_integral<T>::value>* = nullptr>
void func(T t) {
	std::cout << t << "は整数だよ" << std::endl;
}

void func(...) {
	std::cout << "引数は整数じゃないよ" << std::endl;
}



template<class T, class A>
void serialize_array(JSONOutputArchive& archive, vector<T, A>& v)
{
	//archive(size_tag(v.size()));
	for (T& t : v){
		archive(t);
	}
}


int main() {

	func(10);       // 10は整数だよ
	func('c');      // cは整数だよ
	func(3.14f);    // 引数は整数じゃないよ


	cout << "test" << endl;
	cout << has_memfun_serialize<Hoge, JSONOutputArchive>::value << endl;
	cout << has_memfun_serialize<int, JSONOutputArchive>::value << endl;

	rapidjson_test();
	json_writer();
	jsonoutputarchive();

	char c;
	cin >> c;

	return 0;
}

