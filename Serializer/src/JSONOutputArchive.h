#pragma once

#include "traits.h"
#include "SizeTag.h"
#include "NameValuePair.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include <string>


/**
 * JSON形式で出力する
 */
class JSONOutputArchive {
public:
	JSONOutputArchive(std::ostream& stream)
		: m_writeStream(stream)
		, m_writer(m_writeStream)
	{
		m_writer.StartObject();
	}
	~JSONOutputArchive()
	{
		m_writer.EndObject();
	}

	
	template<class T>
	JSONOutputArchive& operator()(T& t) {	// 配列出力用
		static_assert(!std::is_pointer<T>::value || std::is_same<T, const char*>::value, "Pointer is not serialized");	// ポインタはシリアライズ非対応

		saveValue(t);
		return *this;
	}

	template<class T>
	JSONOutputArchive& operator()(NameValuePair<T>& nvp) {
		static_assert(!std::is_pointer<T>::value || std::is_same<T, const char*>::value, "Pointer is not serialized");	// ポインタはシリアライズ非対応

		m_writer.Key(nvp.m_name);
		saveValue(nvp.m_value);
		return *this;
	}

	template<class T>
	JSONOutputArchive& operator()(SizeTag<T>& sizetag) {
		return *this;	/*特にやることはない*/
	}


private:
	void saveValue(bool b)			{ m_writer.Bool(b);		}
	void saveValue(int i)			{ m_writer.Int(i);		}
	void saveValue(unsigned u)		{ m_writer.Uint(u);		}
	void saveValue(int64_t i64)		{ m_writer.Int64(i64);	}
	void saveValue(uint64_t u64)	{ m_writer.Uint64(u64);	}
	void saveValue(double d)		{ m_writer.Double(d);	}
	void saveValue(const char* s)	{ m_writer.String(s);	}
	void saveValue(const std::string& s) { m_writer.String(s.c_str(), static_cast<rapidjson::SizeType>(s.size())); }
	//void saveValue(std::nullptr_t)	{ m_writer.Null();		}

	template<class T, std::enable_if_t<has_memfun_serialize<T, JSONOutputArchive>::value>* = nullptr>
	void saveValue(T& t) {	// serializeメンバ関数を持ってればこっちにくる
		m_writer.StartObject();
		t.serialize(*this);
		m_writer.EndObject();
	}

	template<class T, std::enable_if_t<has_fun_serialize<T, JSONOutputArchive>::value>* = nullptr>
	void saveValue(T& t) {	// serialize(Arcive&, T&)があるならばこっちにくる
		m_writer.StartObject();
		serialize(*this, t);
		m_writer.EndObject();
	}
	
	template<class T, std::enable_if_t<has_fun_serialize_array<T, JSONOutputArchive>::value>* = nullptr>
	void saveValue(T& t) {	// serialize_array(Arcive&, T&)があるならばこっちにくる
		m_writer.StartArray();
		serialize_array(*this, t);
		m_writer.EndArray();
	}


private:
	rapidjson::OStreamWrapper m_writeStream;
	rapidjson::Writer<rapidjson::OStreamWrapper> m_writer;
};

