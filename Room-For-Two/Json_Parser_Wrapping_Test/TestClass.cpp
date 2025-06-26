#include "TestClass.h"


#include<iostream>

bool Json_Parser_Wrapping_Test::TestClass::ReadFile(const std::string& filePath)
{
	bool result = Parser.ReadFile(filePath);
	if (result)
	{

		std::cout << filePath << "를 옳바르게 읽음\n";

	}
	else
	{
		std::cout << Parser.GetLastError()<<std::endl;
	}

	return result;
}

bool Json_Parser_Wrapping_Test::TestClass::TestAndPrint(const std::vector<std::string>& key)
{

	if (HasValue(key) == false)
		return false;
	
	if (GetValueType(key) == JsonParser::EParserValueType::None)
		return false;



}

bool Json_Parser_Wrapping_Test::TestClass::HasValue(const std::vector<std::string>& key)
{

	bool		result = Parser.HasValue(key);
	std::string keyPath;

	if (result == false)
	{
		std::cout << Parser.GetLastError() << "\n";
	}

	for (const auto& keyelement : key)
	{
		keyPath += keyelement + ".";
	}

	if (result)
	{

		std::cout << "해당 키 :" << keyPath << "가 존재함\n";
	}
	//else
	//{

	//	std::cout << "해당" << keyPath << "가 존재하지않음\n";
	//}

	return result;
}

JsonParser::EParserValueType Json_Parser_Wrapping_Test::TestClass::GetValueType(const std::vector<std::string>& key)
{
	JsonParser::EParserValueType type  = Parser.GetValueType(key);
	std::string keyPath;


	if (type == JsonParser::EParserValueType::None)
	{
		std::cout << Parser.GetLastError() << "\n";
	}
	else
	{
		std::cout << "해당 키의 타입은 :" << JsonParser::GetParserValueString(type) << "입니다.\n";
	}




	return type;
}
