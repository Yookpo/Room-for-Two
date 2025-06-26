#include "pch.h"
#include "JsonParser.h"
#include "RapidJsonParserImpl.h"



namespace JsonParser
{

	Parser::Parser()
	{
		pImpl = std::make_unique<RapidJsonParserImpl>();
	}

	Parser::~Parser()
	{
	}

	bool Parser::ReadFile(const std::string& jsonFile)
	{
		return pImpl->ReadFile(jsonFile);
	}

	bool Parser::IsVaild() const
	{
		return pImpl->IsVaild();
	}

	bool Parser::HasValue(const std::vector<std::string>& key) const
	{
		return pImpl->HasValue(key);
	}

	EParserValueType Parser::GetValueType(const std::vector<std::string>& key) const
	{
		return pImpl->GetValueType(key);
	}

	std::string Parser::GetLastError() const
	{
		if (!pImpl)
		{
			LastError = "Parser에 올바른 Impl이 없습니다.";
			return LastError;
		}

		LastError = pImpl->GetLastError();
		return LastError;
	}


	template <typename T>
	inline bool Parser::GetValue(const std::vector<std::string>& key, T& oValue) const
	{
		
		if (!pImpl)
		{
			return false;
		}


		if constexpr (std::is_same_v<T, int>)
		{
			return pImpl->GetIntValue(key, oValue);
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			return pImpl->GetFloatValue(key,oValue);

		}
		else if constexpr (std::is_same_v<T, double>)
		{
			return pImpl->GetDoubleValue(key, oValue);
		}
		else if constexpr (std::is_same_v<T, unsigned int>)
		{
			return  pImpl->GetUIntValue(key,oValue);
		}
		else if constexpr (std::is_same_v<T, unsigned long long>)
		{
			return pImpl->GetULongLongValue(key,oValue);
		}
		else if constexpr (std::is_same_v<T, long long>)
		{
			return pImpl->GetLongLongValue(key, oValue);
		}
		else if constexpr (std::is_same_v<T, bool>)
		{
			return pImpl->GetBoolValue(key, oValue);
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			return pImpl->GetStringValue(key, oValue);

		}else
		{	

			//아직 구현안한 타입
			return false;
		}


	}


	template bool Parser::GetValue<int>(const std::vector<std::string>& key, int & oValue) const;
	template bool Parser::GetValue<float>(const std::vector<std::string>& key, float& oValue) const;
	template bool Parser::GetValue<double>(const std::vector<std::string>& key, double& oValue) const;
	template bool Parser::GetValue<unsigned int>(const std::vector<std::string>& key, unsigned int& oValue) const;
	template bool Parser::GetValue<unsigned long long>(const std::vector<std::string>& key, unsigned long long& oValue) const;
	template bool Parser::GetValue<bool>(const std::vector<std::string>& key, bool& oValue) const;
	template bool Parser::GetValue<std::string>(const std::vector<std::string>& key, std::string& oValue) const;

} // namespace JsonParser