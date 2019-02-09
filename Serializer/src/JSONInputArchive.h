#pragma once

#include "traits.h"
#include "NameValuePair.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <stack>

/**
 * JSON形式を読み取る
 */
class JSONInputArchive {
public:
	JSONInputArchive(std::istream& stream)
		: m_readStream(stream)
		, m_document()
	{
		m_document.ParseStream(m_readStream);
		assert(!m_document.HasParseError());
		assert(!m_document.IsArray());

		m_stack.push(&m_document);	// 最初のノードをルートに設定する
	}

	~JSONInputArchive()
	{
	}

#if 0
	template<class T>
	JSONInputArchive& operator()(T& t) {	// 配列出力用
		loadValue(t);
		return *this;
	}
#endif

	template<class T>
	JSONInputArchive& operator()(NameValuePair<T>& nvp) {
		// keyを探す
		rapidjson::Value::MemberIterator it = m_stack.top()->FindMember(nvp.m_name);
		assert(it != m_stack.top()->MemberEnd());
		
		m_stack.push(&(it->value));
		loadValue(nvp.m_value);
		m_stack.pop();
		
		return *this;
	}


private:
	void loadValue(bool& b)			{ b = m_stack.top()->GetBool();		}
	void loadValue(int& i)			{ i = m_stack.top()->GetInt();		}
	void loadValue(unsigned& u)		{ u = m_stack.top()->GetUint();		}
	void loadValue(int64_t& i64)	{ i64 = m_stack.top()->GetInt64();	}
	void loadValue(uint64_t& u64)	{ u64 = m_stack.top()->GetUint64();	}
	void loadValue(double& d)		{ d = m_stack.top()->GetDouble();	}
	//void loadValue(const char* s)	{ m_writer.String(s);				}
	void loadValue(std::string& s)	{ s = m_stack.top()->GetString();	}
	//void loadValue(std::nullptr_t&)	{ m_writer.Null();		}

	template<class T, std::enable_if_t<has_memfun_serialize<T, JSONInputArchive>::value>* = nullptr>
	void loadValue(T& t) {	// serializeメンバ関数を持ってればこっちにくる
		//m_writer.StartObject();
		t.serialize(*this);
		//m_writer.EndObject();
	}

#if 0
	template<class T, std::enable_if_t<has_fun_serialize<T, JSONInputArchive>::value>* = nullptr>
	void loadValue(T& t) {	// serialize(Arcive&, T&)があるならばこっちにくる
		m_writer.StartObject();
		serialize(*this, t);
		m_writer.EndObject();
	}

	template<class T, std::enable_if_t<has_fun_serialize_array<T, JSONInputArchive>::value>* = nullptr>
	void loadValue(T& t) {	// serialize_array(Arcive&, T&)があるならばこっちにくる
		m_writer.StartArray();
		serialize_array(*this, t);
		m_writer.EndArray();
	}
#endif

private:
	rapidjson::IStreamWrapper m_readStream;
	rapidjson::Document m_document;
	
	std::stack<rapidjson::Value*> m_stack;	//ノードの階層をたどるため、スタックに積んでいく
};

