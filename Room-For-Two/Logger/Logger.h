#pragma once
/**
 * @file Logger.h
 * @brief 싱글턴(Singleton) 패턴을 사용한 로거 클래스를 정의합니다.
 * @details 파일 로깅, 콜백 등록, 다중 스레드 환경에서의 로그 기록 동기화 기능을 제공합니다.
 * @author akflfldh (작성자 이름)
 * @version 1.0.0
 * @date 2025-06-29
 */

#include <string>
#include <functional>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <type_traits> // for std::is_class_v

namespace Log
{
	/**
	 * @enum ELogLevel
	 * @brief 로그 메시지의 심각도 수준을 나타내는 열거형입니다.
	 */
	enum class ELogLevel
	{
		Info = 0, ///< 정보성 로그. 일반적인 진행 상황을 나타냅니다.
		Warning,  ///< 경고성 로그. 잠재적인 문제를 나타내지만 에러는 아닙니다.
		Error,	  ///< 오류 로그. 프로그램 실행에 영향을 미치는 오류를 나타냅니다.
		Critical  ///< 치명적인 오류 로그. 프로그램 실행을 중단시킬 수 있는 심각한 오류입니다.
	};

	/**
	 * @class Logger
	 * @brief 싱글턴 로거 클래스입니다. 파일 및 콜백으로 로그를 출력합니다.
	 * @warning 이 클래스는 싱글턴이므로, 사용하기 전에 반드시 Initialize() 함수를 호출하여 초기화해야 합니다.
	 * @note Log() 함수는 뮤텍스를 통해 스레드에 안전하게(thread-safe) 설계되었습니다.
	 */
	class Logger
	{
	public:
		/**
		 * @brief Logger의 유일한 인스턴스를 반환합니다.
		 * @return Logger 클래스의 싱글턴 인스턴스에 대한 참조.
		 */
		static Logger& GetInstance();

		/**
		 * @brief Logger 소멸자입니다.
		 * @details 열려 있는 로그 파일을 닫습니다.
		 */
		~Logger();

		/**
		 * @brief 로거를 초기화합니다. 로그 파일을 열고 상태를 유효하게 설정합니다.
		 * @details 이 함수는 로깅을 시작하기 전에 단 한 번만 호출되어야 합니다.
		 * @param[in] outputFile 로그를 기록할 파일의 경로.
		 * @return 초기화에 성공하면 true, 실패하면(파일 열기 실패 등) false를 반환합니다.
		 */
		bool Initialize(const std::string& outputFile);

		/**
		 * @brief 지정된 레벨과 카테고리로 로그 메시지를 기록합니다.
		 * @details 이 함수는 스레드에 안전합니다.
		 * @details [level][category]:message 형태로 메시지를 기록합니다.
		 * @param[in] level 로그의 심각도 수준 (ELogLevel).
		 * @param[in] category 로그의 분류 (예: "Network", "Renderer").
		 * @param[in] message 기록할 실제 로그 내용.
		 */
		void Log(ELogLevel level, const std::string& category, const std::string& message);

		/**
		 * @brief 로그 메시지가 생성될 때 호출될 콜백 함수를 등록합니다.
		 * @details UI 업데이트나 다른 로깅 시스템으로 로그를 전달할 때 유용합니다.
		 * @param[in] callback std::function 형태의 콜백 함수. 포맷팅된 로그 문자열을 인자로 받습니다.
		 */
		void RegisterCallback(std::function<void(const std::string&)> callback);

		/**
		 * @brief 특정 객체의 멤버 함수를 콜백으로 등록하기 위한 템플릿 헬퍼 함수입니다.
		 * @tparam T 콜백 멤버 함수를 소유한 객체의 클래스 타입.
		 * @param[in] ob 콜백을 호출할 객체의 포인터.
		 * @param[in] callback 등록할 멤버 함수 포인터.
		 */
		template <typename T>
		void RegisterCallback(T* ob, void (T::*callback)(const std::string&));

		/**
		 * @brief 현재 로거가 유효한 상태인지(초기화되었는지) 확인합니다.
		 * @return 로거가 유효하면 true, 그렇지 않으면 false를 반환합니다.
		 */
		bool IsValid() const;

	private:
		/**
		 * @brief private 생성자 (싱글턴 패턴).
		 */
		Logger();

		/// @brief 등록된 콜백 함수들을 저장하는 벡터.
		std::vector<std::function<void(const std::string&)>> CallbackVector;

		/// @brief 로그 파일 출력을 위한 파일 스트림 객체.
		std::ofstream Ofstream;

		/// @brief ELogLevel 열거형을 문자열로 변환하기 위한 매핑 테이블.
		std::unordered_map<ELogLevel, std::string> ToLogLevelStringTable;

		/// @brief Log() 함수 내부의 동기화를 위한 뮤텍스 객체.
		std::mutex LogMutex;

		/// @brief 로거의 현재 상태 (Initialize가 성공적으로 호출되었는지 여부).
		bool ValidState;
	};

	/**
	 * @brief 멤버 함수 포인터를 std::function으로 변환하여 콜백 벡터에 등록합니다.
	 * @details std::bind를 사용하여 멤버 함수와 객체 인스턴스를 바인딩합니다.
	 * static_assert를 통해 T가 반드시 클래스 타입인지 컴파일 타임에 확인합니다.
	 */
	template <typename T>
	inline void Logger::RegisterCallback(T* ob, void (T::*callback)(const std::string&))
	{
		static_assert(std::is_class_v<T>, "T는 반드시 클래스 타입이어야합니다.");
		RegisterCallback(std::bind(callback, ob, std::placeholders::_1));
	}

} // namespace Log