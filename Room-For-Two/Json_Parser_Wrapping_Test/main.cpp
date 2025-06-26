
#include<JsonParser.h>

#include"TestClass.h"
#include<iostream>
int main()
{

	Json_Parser_Wrapping_Test::TestClass test;

	std::vector<std::string> keyName = { "Object", "Name" };
	std::vector<std::string> keyID = { "Object", "ID" };
	std::vector<std::string> keyWeight = { "Object", "Weight" };
	std::vector<std::string> keyDetailAge = { "Object", "Detail", "Age2" };
	test.ReadFile("Test.json");

	if (test.TestAndPrint(keyName))
	{
		std::string value = test.GetValue<std::string>(keyName);
		std::cout << value << "\n";
	}

	if (test.TestAndPrint(keyID))
	{
		int value = test.GetValue<int>(keyID);
		std::cout << value << "\n";
	}

	if (test.TestAndPrint(keyWeight))
	{
		float value = test.GetValue<float>(keyWeight);
		std::cout << value << "\n";
	}

	if (test.TestAndPrint(keyDetailAge))
	{
		int value = test.GetValue<int>(keyDetailAge);
		std::cout << value << "\n";
	}
}