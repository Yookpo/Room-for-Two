#pragma once


#include"IParserImpl.h"

#include"include/rapidjson/document.h"
#include<memory>
namespace JsonParser
{
	

	class RapidJsonParserImpl:public IParserImpl
	{
	public:
		RapidJsonParserImpl();
		virtual ~RapidJsonParserImpl();

		virtual bool ReadFile(const std::string& jsonFile) override;
		virtual bool IsVaild() const override; // 현재 파서가 유효하여 value를 얻는게 가능한지여부

		virtual bool HasValue(const std::vector<std::string>& key) const override;

		virtual EParserValueType GetValueType(const std::vector<std::string>& key) const override;

		virtual bool GetIntValue(const std::vector<std::string>& key, int& oValue) const override;
		virtual bool GetUIntValue(const std::vector<std::string>& key, unsigned int& oValue) const override;
		virtual bool GetFloatValue(const std::vector<std::string>& key, float& oValue) const override;
		virtual bool GetDoubleValue(const std::vector<std::string>& key, double& oValue) const override;
		virtual bool GetLongLongValue(const std::vector<std::string>& key, long long& oValue) const override;
		virtual bool GetULongLongValue(const std::vector<std::string>& key, unsigned long long& oValue) const override;
		virtual bool GetStringValue(const std::vector<std::string>& key, std::string& oValue) const override;
		virtual bool GetBoolValue(const std::vector<std::string>& key, bool& oValue) const override;
		// 바로 전동작이 실패했을경우 그 실패에대한 정보를 문자열로 리턴해준다.
		virtual std::string GetLastError() const override;

	private:

		EParserValueType		GetValueType(const rapidjson::Value* value) const;
		const rapidjson::Value* FindValueByKeyPath(const std::vector<std::string>& keyPath) const;
		
		void SetLastErrorStr(const std::string& log) const;
		void SetGettingValueErrorLog(const std::vector<std::string>& keyVector, const std::string& type) const;

	private:
		std::unique_ptr<rapidjson::Document> pDocument;
		mutable std::string					 LastErrorString;
		bool								 ParserValidFlag;
	};

} // namespace JsonParser