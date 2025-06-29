#include "Logger.h"

#include<sstream>


#include<mutex>






void Log::Logger::RegisterCallback(std::function<void(const std::string&)> callback)
{

	{
		std::lock_guard<std::mutex> lock_guard(LogMutex);
		CallbackVector.push_back(std::move(callback));
	}

}

bool Log::Logger::IsValid() const
{
	return ValidState;
}

Log::Logger::Logger()
	: ValidState(false)
{
	
	ToLogLevelStringTable[ELogLevel::Warning] = "[Warning]";
	ToLogLevelStringTable[ELogLevel::Error] = "[Error]";
	ToLogLevelStringTable[ELogLevel::Critical] = "[Critical]";
	ToLogLevelStringTable[ELogLevel::Info] = "[Info]";

}

Log::Logger& Log::Logger::GetInstance()
{
	static Logger log;

	return log;
}

Log::Logger::~Logger()
{


}

bool Log::Logger::Initialize(const std::string& outputFile)
{
	//스레드 안정성 확보할것

	Ofstream.open(outputFile);
	if (!Ofstream.is_open())
	{
		//파일열기실패;
		return false;
	}
	ValidState = true;
	return true;
}

void Log::Logger::Log(ELogLevel level, const std::string& category, const std::string& message)
{
	
	std::stringstream log;
		
	log << ToLogLevelStringTable[level] << "[" << category <<"]" << ":" << message << "\n";


	{
		std::lock_guard<std::mutex> lock_guard(LogMutex);

		Ofstream.write(log.str().c_str(), log.str().size());
		for (auto& callback : CallbackVector)
		{
			callback(log.str());
		}

	}


}
