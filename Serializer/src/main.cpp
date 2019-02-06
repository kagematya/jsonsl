#include <iostream>
#include "rapidjson/document.h"
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

int main() {

	cout << "test" << endl;

	rapidjson_test();


	char c;
	cin >> c;

	return 0;
}

