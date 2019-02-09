#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
//#include "rapidjson/prettywriter.h"
#include <iostream>
#include <sstream>
using namespace std;
using namespace rapidjson;

void rapidjsonWriteTest()
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
