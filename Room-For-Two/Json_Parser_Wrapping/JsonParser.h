#pragma once

/**
 * @file Parser.h
 * @brief JSON 파싱 기능을 제공하는 Parser 클래스를 정의하는 헤더 파일입니다.
 * @author YourName (혹은 프로젝트/회사 이름)
 * @version 1.0.0
 * @date 2025-06-26
 */

#include <string>
#include <vector>
#include "JsonParserType.h"
#include <memory>

/**
 * @namespace JsonParser
 * @brief JSON 파싱 관련 기능들을 모아놓은 네임스페이스입니다.
 */
namespace JsonParser
{
	class IParserImpl; // 전방 선언 (Forward declaration)

	/**
	 * @class Parser
	 * @brief JSON 파일을 읽고, 데이터를 파싱하여 값을 추출하는 기능을 제공하는 클래스입니다.
	 * @details Pimpl(Pointer to implementation) 패턴을 사용하여 구현 세부 사항을 숨깁니다.
	 * * @warning 이 클래스는 스레드 안전성(thread-safe)을 보장하지 않습니다. 
	 * - 여러 스레드에서 동일한 Parser 인스턴스에 동시에 접근하지 마십시오.
	 * - Json에서 array타입은 사용하지 마십시오. 
	 * - 시작은 항상 Object타입으로 시작하십시오.
	 * * @note 사용법
	 * 1. Parser 객체를 생성합니다.
	 * 2. `ReadFile()`을 호출하여 JSON 파일을 파싱합니다.
	 * 3. `IsVaild()`로 파싱 성공 여부를 확인합니다.
	 * 4. `GetValue()`, `HasValue()` 등의 함수로 데이터에 접근합니다.
	 * 5. `ReadFile()`이나 `GetValue()` 등이 false를 반환하면, `GetLastError()`로 오류의 원인을 파악할 수 있습니다.
	 */
	class Parser
	{
	public:
		/**
		 * @brief Parser 클래스의 기본 생성자입니다.
		 * @details 내부 구현 객체(pImpl)를 초기화합니다.
		 */
		Parser();

		/**
		 * @brief Parser 클래스의 소멸자입니다.
		 * @details 동적으로 할당된 리소스를 해제합니다.
		 */
		~Parser();

		/**
		 * @brief 지정된 경로의 JSON 파일을 읽어 파싱합니다.
		 * @param[in] jsonFile 읽어올 JSON 파일의 경로와 이름입니다.
		 * @return 파일 읽기 및 파싱에 성공하면 true, 실패하면 false를 반환합니다.
		 */
		bool ReadFile(const std::string& jsonFile);

		/**
		 * @brief 현재 파서가 유효한 JSON 데이터를 가지고 있는지 확인합니다.
		 * @details ReadFile()이 성공적으로 완료된 후에 호출되어야 합니다.
		 * @return 파서가 유효하면 true, 그렇지 않으면 false를 반환합니다.
		 */
		bool IsVaild() const;

		/**
		 * @brief 주어진 키 경로에 해당하는 값이 JSON 데이터에 존재하는지 확인합니다.
		 * @param[in] key 값의 위치를 나타내는 문자열 벡터입니다. (예: {"a", "b", 0} -> a.b[0])
		 * @return 키에 해당하는 값이 존재하면 true, 그렇지 않으면 false를 반환합니다.
		 */
		bool HasValue(const std::vector<std::string>& key) const;

		/**
		 * @brief 주어진 키 경로에 해당하는 값의 타입을 반환합니다.
		 * @param[in] key 값의 위치를 나타내는 문자열 벡터입니다.
		 * @return 해당 키의 값 타입을 나타내는 EParserValueType 열거형 값을 반환합니다. 키가 존재하지 않으면 EParserValueType::None을 반환할 수 있습니다.
		 */
		EParserValueType GetValueType(const std::vector<std::string>& key) const;

		/**
		 * @brief 가장 최근에 발생한 오류에 대한 설명을 문자열로 반환합니다.
		 * @return 오류 메시지 문자열을 반환합니다. 오류가 없었다면 빈 문자열일 수 있습니다.
		 */
		std::string GetLastError() const;

		/**
		 * @brief 주어진 키 경로에 해당하는 값을 가져옵니다.
		 * @tparam T 가져올 값의 타입 (e.g., int, float, std::string, bool).
		 * @param[in] key 값의 위치를 나타내는 문자열 벡터입니다.
		 * @param[out] oValue 값을 저장할 출력 변수입니다.
		 * @return 값 가져오기에 성공하면 true, 실패하면 (키가 없거나 타입이 일치하지 않는 경우) false를 반환합니다.
		 */
		template <typename T>
		bool GetValue(const std::vector<std::string>& key, T& oValue) const;

	private:
		/**
		 * @var pImpl
		 * @brief Parser의 실제 구현을 가리키는 unique_ptr입니다. (Pimpl Idiom)
		 */
		std::unique_ptr<IParserImpl> pImpl;

		/**
		 * @var LastError
		 * @brief 가장 최근에 발생한 오류 메시지를 저장하는 문자열입니다.
		 * @note mutable 키워드를 사용하여 const 멤버 함수 내에서도 값을 변경할 수 있도록 합니다.
		 */
		mutable std::string LastError;
	};

} // namespace JsonParser