#pragma once


#include"JsonParserType.h"
#include<string>
#include<vector>
#include<unordered_map>
namespace JsonParser
{

	class IParserImpl
	{

	public:
		IParserImpl()=default;
		virtual ~IParserImpl() = 0;

		// 파일을 읽는다.
		virtual bool ReadFile(const std::string& jsonFile) = 0;
		virtual bool IsVaild() const = 0; // 현재 파서가 유효하여 value를 얻는게 가능한지여부

		virtual bool HasValue(const std::vector<std::string>& key) const = 0;

		virtual EParserValueType GetValueType(const std::vector<std::string>& key) const = 0;

		virtual bool GetIntValue(const std::vector<std::string>& key, int& oValue) const = 0;
		virtual bool GetUIntValue(const std::vector<std::string>& key, unsigned int& oValue) const = 0;
		virtual bool GetFloatValue(const std::vector<std::string>& key, float& oValue) const = 0;
		virtual bool GetDoubleValue(const std::vector<std::string>& key, double& oValue) const = 0;
		virtual bool GetLongLongValue(const std::vector<std::string>& key, long long& oValue) const = 0;
		virtual bool GetULongLongValue(const std::vector<std::string>& key, unsigned long long& oValue) const = 0;
		virtual bool GetStringValue(const std::vector<std::string>& key, std::string& oValue) const = 0;
		virtual bool GetBoolValue(const std::vector<std::string>& key, bool & oValue) const = 0;


		// 바로 전동작이 실패했을경우 그 실패에대한 정보를 문자열로 리턴해준다.
		virtual std::string GetLastError() const = 0;



	private:

	};
} // namespace JsonParser
