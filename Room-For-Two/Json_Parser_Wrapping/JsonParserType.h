#pragma once


namespace JsonParser
{
	enum class EParserValueType
	{
		None = 0,
		Int,
		UInt,
		Float,
		Double,
		LongLong,
		ULongLong,
		Bool,
		String,
	};

	

	const char * GetParserValueString(EParserValueType type);



}