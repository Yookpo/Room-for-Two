/**
 * @file window.h
 * @brief Win32 윈도우 생성 및 관리를 위한 Window 클래스를 선언합니다.
 * @author Yookpo
 * @date 2025-06-27
 */
#pragma once

#include <Windows.h>
#include <string>

/**
 * @class Window
 * @brief Win32 API를 캡슐화하여 윈도우의 생성, 초기화, 메시지 처리를 담당하는 클래스.
 * @details
 * 이 클래스는 객체 생성과 실제 윈도우 생성을 분리하는 2단계 초기화 패턴을 사용합니다.
 * 프레임워크의 핵심 구성 요소로, 렌더러나 입력 관리자 등 다른 모듈에
 * 윈도우 핸들(HWND)을 제공하는 기반 역할을 합니다.
 */
class Window
{
public:
	/**
	 * @brief Window 클래스의 생성자입니다.
	 * @details 멤버 변수를 초기화하지만, 실제 윈도우를 생성하지는 않습니다.
	 * @param[in] hInstance 애플리케이션의 인스턴스 핸들입니다. WinMain으로부터 전달받습니다.
	 */
	explicit Window(HINSTANCE hInstance);

	/**
	 * @brief Window 클래스의 소멸자입니다.
	 * @details 생성된 윈도우를 파괴하고 등록된 윈도우 클래스를 해제하여 리소스를 정리합니다.
	 */
	~Window();

	// 복사 및 대입 연산자는 유일성을 보장하기 위해 삭제합니다.
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	/**
	 * @brief 윈도우를 초기화하고 화면에 표시합니다.
	 * @details
	 * 내부적으로 RegisterWindowClass와 CreateActualWindow를 호출하여 윈도우 생성의
	 * 모든 과정을 처리합니다. 성공적으로 생성되면 ShowWindow를 통해 창을 화면에 표시합니다.
	 * @param[in] width 생성할 윈도우의 클라이언트 영역 너비입니다.
	 * @param[in] height 생성할 윈도우의 클라이언트 영역 높이입니다.
	 * @param[in] title 윈도우의 제목 표시줄에 표시될 텍스트입니다.
	 * @return 초기화에 성공하면 true, 실패하면 false를 반환합니다.
	 */
	bool Initialize(int width, int height, const std::wstring& title);

	/**
	 * @brief 윈도우 메시지 큐를 처리합니다.
	 * @details
	 * 게임 루프 내에서 매 프레임 호출되어야 합니다. PeekMessage를 사용하여
	 * 비동기적으로 메시지를 처리하므로, 메시지가 없어도 프로그램이 멈추지 않습니다.
	 * @return 애플리케이션이 계속 실행되어야 하면 true, WM_QUIT 메시지를 받아 종료해야 하면 false를 반환합니다.
	 */
	bool ProcessMessages();

	/**
	 * @brief 윈도우 핸들(HWND)을 반환합니다.
	 * @return 이 인스턴스가 관리하는 윈도우의 핸들입니다. 렌더러 등 다른 모듈에서 필요합니다.
	 */
	HWND GetHWND() const { return Hwnd; }

private:
	/**
	 * @brief 윈도우 클래스(WNDCLASSEX)를 Windows에 등록하는 내부 메서드입니다.
	 * @return 클래스 등록에 성공하면 true, 실패하면 false를 반환합니다.
	 */
	bool RegisterWindowClass();

	/**
	 * @brief 등록된 윈도우 클래스를 기반으로 실제 윈도우를 생성하는 내부 메서드입니다.
	 * @return 윈도우 생성에 성공하면 true, 실패하면 false를 반환합니다.
	 */
	bool CreateActualWindow();

	/**
	 * @brief Windows로부터 메시지를 수신하여 처리하는 정적 콜백 함수(윈도우 프로시저)입니다.
	 * @details
	 * C-스타일 콜백 함수이므로 static으로 선언되었습니다.
	 * WM_NCCREATE 메시지 시점에서 lParam으로 전달된 this 포인터를 GWLP_USERDATA에 저장하여
	 * C++ 클래스 인스턴스와 실제 윈도우를 연결하는 역할을 합니다.
	 * @param hWnd 메시지가 발생한 윈도우의 핸들입니다.
	 * @param uMsg 메시지의 종류를 나타내는 식별자입니다.
	 * @param wParam 메시지에 대한 추가 정보입니다. (WPARAM)
	 * @param lParam 메시지에 대한 추가 정보입니다. (LPARAM)
	 * @return 메시지 처리 결과입니다. DefWindowProc을 호출하여 기본 처리를 위임할 수 있습니다.
	 */
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND		 Hwnd = nullptr;	  ///< 생성된 윈도우의 고유 핸들입니다.
	HINSTANCE	 Hinstance = nullptr; ///< 애플리케이션의 인스턴스 핸들입니다.
	int			 Width = 0;			  ///< 윈도우 클라이언트 영역의 너비입니다.
	int			 Height = 0;		  ///< 윈도우 클라이언트 영역의 높이입니다.
	std::wstring Title;				  ///< 윈도우의 제목입니다.
	std::wstring ClassName;			  ///< 윈도우 클래스의 이름입니다.
	bool		 IsClassRegistered;	  ///< 윈도우 클래스의 등록 성공 여부를 추적하는 플래그입니다.
};