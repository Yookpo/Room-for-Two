#pragma once

#include<JsonParser.h>

namespace Json_Parser_Wrapping_Test
{

	class TestClass
	{
	public:
		TestClass() =default;
		~TestClass() =default;

		bool ReadFile(const std::string& filePath);

		bool TestAndPrint(const std::vector<std::string>& key);

		bool HasValue(const std::vector<std::string>& key);

		JsonParser::EParserValueType GetValueType(const std::vector<std::string>& key);

		template<typename T>
		T GetValue(const std::vector<std::string>& key);

	private:
		JsonParser::Parser Parser;

	};

	template <typename T>
	inline T TestClass::GetValue(const std::vector<std::string>& key)
	{
		T value;
		Parser.GetValue<T>(key, value);
		return value;
	}

} // namespace Json_Parser_Wrapping_Test