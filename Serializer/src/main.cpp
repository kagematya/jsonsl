#include <iostream>
#include <map>
#include <functional>
using namespace std;

extern void rapidjsonReadTest();
extern void rapidjsonWriteTest();
extern void traitsTest();
extern void jsonWriteTest();
extern void jsonReadTest();


void helpMain()
{
	cout << "h: helpMain" << endl;
	cout << "1: rapidjsonReadTest" << endl;
	cout << "2: rapidjsonWriteTest" << endl;
	cout << "3: traitsTest" << endl;
	cout << "4: jsonWriteTest" << endl;
	cout << "5: jsonReadTest" << endl;
}

void parseKey(char key)
{
	static const map<char, function<void()>> func = {
		{'h', helpMain},
		{'1', rapidjsonReadTest},
		{'2', rapidjsonWriteTest},
		{'3', traitsTest},
		{'4', jsonWriteTest},
		{'5', jsonReadTest},
	};
	
	auto it = func.find(key);
	if (it != func.end()) {
		it->second();
	}
}

int main() {
	cout << "Serialize Test" << endl;

	while (true) {
		cout << endl;
		cout << "help: h,   quit: q" << endl;
		cout << "please input key:" << endl;

		char key;
		cin >> key;

		if (key == 'q') {
			break;
		}

		parseKey(key);
	}

	return 0;
}

