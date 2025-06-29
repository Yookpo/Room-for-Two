




#include<Logger.h>
#include<iostream>

int main()
{

	Log::Logger  & logger = Log::Logger::GetInstance();

	bool initResult = logger.Initialize("LogFile.txt");

	if (!initResult)
	{
		std::cout << "파일열기 실패";
		return 0 ;
	}


	logger.RegisterCallback([](const std::string& log) { std::cout << log; });

	logger.Log(Log::ELogLevel::Error, "Asset", "해당Asset이 유효하지않아 올바르게 작동되지않았습니다.");
	logger.Log(Log::ELogLevel::Critical, "Render", "렌더시스템코어에서 Gpu리소스가 유효하지않았습니다.");


	return 0;
}