#pragma once

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

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
		assert(m_document.IsArray());
	}

	~JSONInputArchive()
	{
	}


private:
	rapidjson::IStreamWrapper m_readStream;
	rapidjson::Document m_document;
};

