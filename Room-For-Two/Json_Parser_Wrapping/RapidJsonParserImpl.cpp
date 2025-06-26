#include "pch.h"
#include "RapidJsonParserImpl.h"
#include"include/rapidjson/filereadstream.h"
#include"include/rapidjson/encodedstream.h"
#include<stdio.h>


namespace JsonParser
{

	RapidJsonParserImpl::RapidJsonParserImpl()
		: ParserValidFlag(false)
	{
		pDocument = std::make_unique<rapidjson::Document>();
	}

	RapidJsonParserImpl::~RapidJsonParserImpl()
	{
		
		
	}

	bool RapidJsonParserImpl::ReadFile(const std::string& jsonFile)
	{
		FILE* fp = nullptr;
		if (fopen_s(&fp, jsonFile.c_str(), "rb") != 0)
		{
			SetLastErrorStr(jsonFile + " 파일읽기 실패\n");
			return false;
		}


		char buffer[1024];
		rapidjson::FileReadStream fileReadStream(fp, buffer, sizeof(buffer));



		rapidjson::AutoUTFInputStream<unsigned int, rapidjson::FileReadStream> autoUTFInputStream(fileReadStream);


		pDocument->ParseStream<rapidjson::kParseNoFlags, rapidjson::AutoUTF<unsigned int>>(autoUTFInputStream);

			
		std::fclose(fp);
		ParserValidFlag = !pDocument->HasParseError();

		if (ParserValidFlag == false)
		{
			//log기록
			SetLastErrorStr(jsonFile + "파일 파싱 실패\n");
			return false;
		}


		return true;


	

	}

	bool RapidJsonParserImpl::IsVaild() const
	{

		if (ParserValidFlag == false)
		{
			SetLastErrorStr("파싱이 유효하지않다\n ");
		}

		return ParserValidFlag;


	}

	bool RapidJsonParserImpl::HasValue(const std::vector<std::string>& keyVector) const
	{
		return	FindValueByKeyPath(keyVector);
	}

	EParserValueType RapidJsonParserImpl::GetValueType(const std::vector<std::string>& keyVector) const
	{
		const rapidjson::Value* value = FindValueByKeyPath(keyVector);

		return GetValueType(value);
	}



	bool RapidJsonParserImpl::GetIntValue(const std::vector<std::string>& key, int& oValue) const
	{
		const rapidjson::Value* value =  FindValueByKeyPath(key);
		if (value == nullptr)
			return false;


		if (!value->IsInt())
		{
			//error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::Int));
			return false;
		}

		oValue =  value->GetInt();
		return true;
	}

	bool RapidJsonParserImpl::GetUIntValue(const std::vector<std::string>& key, unsigned int& oValue) const
	{
		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;
		if (!value->IsUint())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::UInt));
			return false;
		}

		oValue = value->GetUint();
		return true;

	}

	bool RapidJsonParserImpl::GetFloatValue(const std::vector<std::string>& key, float& oValue) const
	{


		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;
		if (!value->IsFloat())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::Float));
			return false;
		}

		oValue = value->GetFloat();
		return true;
	}

	bool RapidJsonParserImpl::GetDoubleValue(const std::vector<std::string>& key, double& oValue) const
	{
		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;
		if (!value->IsDouble())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::Double));
			return false;
		}

		oValue = value->GetDouble();
		return true;
	}

	bool RapidJsonParserImpl::GetLongLongValue(const std::vector<std::string>& key, long long& oValue) const
	{

		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;
		if (!value->IsInt64())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::LongLong));
			return false;
		}

		oValue = value->GetInt64();
		return true;
	}

	bool RapidJsonParserImpl::GetULongLongValue(const std::vector<std::string>& key, unsigned long long& oValue) const
	{
		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;

		if (!value->IsUint64())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::ULongLong));
			return false;
		}

		oValue = value->GetUint64();
		return true;
	}

	bool RapidJsonParserImpl::GetStringValue(const std::vector<std::string>& key, std::string& oValue) const
	{
		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;

		if (!value->IsString())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::String));
			return false;
		}

		oValue = value->GetString();
		return true;
	}

	bool RapidJsonParserImpl::GetBoolValue(const std::vector<std::string>& key, bool& oValue) const
	{

		const rapidjson::Value* value = FindValueByKeyPath(key);
		if (value == nullptr)
			return false;


		if (!value->IsBool())
		{
			// error log 기록
			SetGettingValueErrorLog(key, JsonParser::GetParserValueString(EParserValueType::Bool));
			return false;
		}

		oValue = value->GetBool();
		return true;
	}

	
	std::string RapidJsonParserImpl::GetLastError() const
	{
		return LastErrorString;
	}

	EParserValueType RapidJsonParserImpl::GetValueType(const rapidjson::Value* value) const
	{
		if (value == nullptr)
			return EParserValueType::None;

		if (value->IsInt())
		{
			return EParserValueType::Int;
		}
		else if (value->IsFloat())
		{
			return EParserValueType::Float;
		}
		else if (value->IsUint())
		{
			return EParserValueType::UInt;
		}
		else if (value->IsBool())
		{
			return EParserValueType::Bool;
		}
		else if (value->IsDouble())
		{
			return EParserValueType::Double;
		}
		else if (value->IsInt64())
		{
			return EParserValueType::LongLong;
		}
		else if (value->IsUint64())
		{
			return EParserValueType::ULongLong;
		}
		else if (value->IsString())
		{

			return EParserValueType::String;
		}
		else
		{
			return EParserValueType::None;
		}

	}

	const rapidjson::Value* RapidJsonParserImpl::FindValueByKeyPath(const std::vector<std::string>& keyPath) const
	{
		if (IsVaild() == false)
		{
			return nullptr;
		}


		if (keyPath.size() == 0)
		{
			// error 기록
			return nullptr;
		}
		const rapidjson::Value* value = pDocument.get();

		for (const auto& keyElement : keyPath)
		{
			if (!value->IsObject())
			{
				// error 기록 object type아님

				return nullptr;
			}

			rapidjson::Value::ConstMemberIterator it = value->FindMember(keyElement.c_str());

			if (it == value->MemberEnd())
			{
				// Error 기록	그런 멤버가없음
				SetLastErrorStr(keyElement +"멤버가 없습니다.\n");
				return nullptr;
			}

			value = &it->value;
		}

		return value;

	}

	void RapidJsonParserImpl::SetLastErrorStr(const std::string& log) const
	{
		LastErrorString = log;
	}

	void RapidJsonParserImpl::SetGettingValueErrorLog(const std::vector<std::string>& keyVector, const std::string& type) const
	{
		std::string keyStr = "";

		for (const auto& keyElement : keyVector)
		{
			keyStr += keyElement + ">";
		}
	
		SetLastErrorStr(keyStr + "의 value타입이 " + type + "이 아닙니다.\n");

	}



} // namespace JsonParser