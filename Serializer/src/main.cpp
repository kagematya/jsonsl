#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include <iostream>
#include <sstream>

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
	}

	const string& result = s.str();
	cout << result;
}

int main() {

	cout << "test" << endl;

	rapidjson_test();
	json_writer();
	jsonoutputarchive();

	char c;
	cin >> c;

	return 0;
}

