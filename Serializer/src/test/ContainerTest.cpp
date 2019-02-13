#include "JSONInputArchive.h"
#include "JSONOutputArchive.h"
#include "stl/array.hpp"
#include "stl/bitset.hpp"
#include "stl/deque.hpp"
#include "stl/forward_list.hpp"
#include "stl/list.hpp"
#include "stl/map.hpp"
#include "stl/pair.hpp"
#include "stl/queue.hpp"
#include "stl/set.hpp"
#include "stl/stack.hpp"
#include "stl/unordered_map.hpp"
#include "stl/unordered_set.hpp"
#include "stl/vector.hpp"
#include <iostream>
#include <sstream>
using namespace std;
using namespace jsonsl;

namespace {
struct Hoge {
	Hoge(int count)
		: bitset(count)
		, pair(count, count*count)
	{
		array.fill(count);
		
		for (int i = 0; i < count; i++) {
			int val = i * i;
			deque.push_back(val);
			forward_list.push_front(val);
			list.push_back(val);
			map[i] = val;
			queue.push(val);
			set.insert(val);
			multiset.insert(val);
			stack.push(val);
			unordered_map[i] = val;
			unordered_set.insert(val);
			unordered_multiset.insert(val);
			vector.push_back(val);
		}
	}

	array<int, 5> array;
	bitset<5> bitset;
	deque<int> deque;
	forward_list<int> forward_list;
	list<int> list;
	map<int, int> map;
	pair<int, int> pair;
	queue<int> queue;
	set<int> set;
	multiset<int> multiset;
	stack<int> stack;
	unordered_map<int, int> unordered_map;
	unordered_set<int> unordered_set;
	unordered_multiset<int> unordered_multiset;
	vector<int> vector;

	template<class Archive>
	void serialize(Archive& ar) {
		ar(make_nvp("array", array));
		ar(make_nvp("bitset", bitset));
		ar(make_nvp("deque", deque));
		ar(make_nvp("forward_list", forward_list));
		ar(make_nvp("list", list));
		ar(make_nvp("map", map));
		ar(make_nvp("pair", pair));
		ar(make_nvp("queue", queue));
		ar(make_nvp("set", set));
		ar(make_nvp("multiset", multiset));
		ar(make_nvp("stack", stack));
		ar(make_nvp("unordered_map", unordered_map));
		ar(make_nvp("unordered_set", unordered_set));
		ar(make_nvp("unordered_multiset", unordered_multiset));
		ar(make_nvp("vector", vector));
	}
};
} // namespace


void containerTest() {
	ostringstream oss;
	{
		JSONOutputArchive archive(oss);

		Hoge hoge(5);
		archive(make_nvp("hoge", hoge));
	}
	const string& result = oss.str();
	cout << result << endl;
	cout << endl;


	istringstream iss(result);
	Hoge hoge2(0);
	{
		JSONInputArchive archive(iss);
		archive(make_nvp("hoge", hoge2));
	}


	ostringstream oss2;
	{
		JSONOutputArchive archive(oss2);
		archive(make_nvp("hoge", hoge2));
	}
	cout << oss2.str() << endl;
}
