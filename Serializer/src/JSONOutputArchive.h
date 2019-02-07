#pragma once

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
	}
	~JSONOutputArchive()
	{
	}

	template<class T>
	JSONOutputArchive& operator()(T& t) {
		saveValue(t);
		return *this;
	}



private:
	void saveValue(bool b)			{ m_writer.Bool(b);		}
	void saveValue(int i)			{ m_writer.Int(i);		}
	void saveValue(unsigned u)		{ m_writer.Uint(u);		}
	void saveValue(int64_t i64)		{ m_writer.Int64(i64);	}
	void saveValue(uint64_t u64)	{ m_writer.Uint64(u64);	}
	void saveValue(double d)		{ m_writer.Double(d);	}
	void saveValue(char const * s)	{ m_writer.String(s);	}
	void saveValue(std::string const & s) { m_writer.String(s.c_str(), static_cast<rapidjson::SizeType>(s.size())); }
	//void saveValue(std::nullptr_t)	{ m_writer.Null();		}


private:
	rapidjson::OStreamWrapper m_writeStream;
	rapidjson::Writer<rapidjson::OStreamWrapper> m_writer;
};

