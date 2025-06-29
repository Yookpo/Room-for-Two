// Test.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include "Window.h" // 우리가 만든 Window.h 헤더

// Win32 GUI 애플리케이션에서 콘솔 창을 사용하기 위한 헬퍼 함수
void CreateConsole()
{
	AllocConsole();
	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	freopen_s(&pFile, "CONIN$", "r", stdin);
	std::cout << "--- 이벤트 로그 콘솔 ---" << std::endl;
}

// 애플리케이션의 이벤트 처리 로직을 담당할 함수 (또는 람다)
void OnEvent(Event& e)
{
	// 이벤트 메시지 종류에 따라 분기하여 처리합니다.
	switch (e.uMsg)
	{
		case WM_KEYDOWN:
		{
			// wParam에 가상 키 코드가 담겨 옵니다.
			unsigned char keyCode = static_cast<unsigned char>(e.wParam);
			std::cout << "[Event] KeyDown: " << keyCode << std::endl;
			break;
		}
		case WM_KEYUP:
		{
			unsigned char keyCode = static_cast<unsigned char>(e.wParam);
			std::cout << "[Event] KeyUp: " << keyCode << std::endl;
			break;
		}
		case WM_MOUSEMOVE:
		{
			// lParam에 마우스의 좌표가 담겨 옵니다.
			int x = LOWORD(e.lParam);
			int y = HIWORD(e.lParam);
			std::cout << "[Event] MouseMove: (" << x << ", " << y << ")" << std::endl;
			break;
		}
		case WM_LBUTTONDOWN:
		{
			std::cout << "[Event] LeftMouseButtonDown" << std::endl;
			break;
		}
		case WM_CLOSE:
		{
			std::cout << "[Event] Window is closing..." << std::endl;
			// 여기서 "저장하시겠습니까?" 같은 로직을 수행할 수 있습니다.
			// 실제 종료는 Window 클래스의 WM_DESTROY에서 처리됩니다.
			break;
		}
	}
}

int WINAPI WinMain(
	_In_ HINSTANCE	   hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR		   lpCmdLine,
	_In_ int		   nCmdShow)
{
	// 1. 디버깅 및 로그 출력을 위한 콘솔 창 생성
	CreateConsole();

	// 2. Window 인스턴스 생성
	Window window(hInstance); //

	// 3. 이벤트 콜백 함수 등록
	//    window.SetEventCallback을 사용하여 우리가 만든 OnEvent 함수를 "등록"합니다.
	//    이제부터 window에서 발생하는 모든 이벤트는 OnEvent 함수로 전달됩니다.
	window.SetEventCallback(OnEvent); //

	// 4. 윈도우 초기화 및 생성
	if (!window.Initialize(1280, 720, L"이벤트 테스트")) //
	{
		return -1;
	}

	// 5. 메인 루프 실행
	//    ProcessMessages()는 WM_QUIT 메시지를 받을 때까지 true를 반환합니다.
	while (window.ProcessMessages())
	{
		// 게임 로직 및 렌더링 코드가 위치할 곳...
		// 이 예제에서는 콜백 처리만 확인하므로 비워둡니다.
	}

	return 0;
}