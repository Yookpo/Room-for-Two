
#include"pch.h"
#include "JsonParserType.h"

const char* JsonParser::GetParserValueString(EParserValueType type)
{
	switch (type)
	{
		case EParserValueType::None:
			return "None";
		case EParserValueType::Int:

			return "Int";

		case EParserValueType::UInt:

			return "UInt";

		case EParserValueType::Float:

			return "Float";
		case EParserValueType::Double:

			return "Double";
		case EParserValueType::LongLong:
			return "LongLong";

		case EParserValueType::ULongLong:
			return "ULongLong";

		case EParserValueType::Bool:

			return "Bool";

		case EParserValueType::String:
			return "String";

	}

	return nullptr;
}
