#pragma once

#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include <string>

namespace jsonsl {

class JsonslUtil {
public:

	static std::string reformat(const char* json, int indentCharCount = 2) {
		rapidjson::Reader reader;
		rapidjson::StringBuffer buf;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
		
		writer.SetFormatOptions(rapidjson::PrettyFormatOptions::kFormatSingleLineArray);
		writer.SetIndent(' ', indentCharCount);

		bool succeeded = reader.Parse(rapidjson::StringStream(json), writer);
		if (succeeded) {
			return buf.GetString();
		}
		return json;
	}
};

} // namespace jsonsl
