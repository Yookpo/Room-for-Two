// Main.cpp
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Window.h" // 제작한 Window 클래스 헤더

/**
 * @brief Win32 애플리케이션의 주 진입점입니다.
 * @param hInstance 애플리케이션의 인스턴스 핸들입니다.
 * @param hPrevInstance 이전 인스턴스의 핸들입니다. (현재는 사용되지 않음)
 * @param lpCmdLine 커맨드 라인 인자입니다.
 * @param nCmdShow 창을 표시하는 방법을 지정합니다.
 * @return 애플리케이션 종료 코드입니다.
 */
int WINAPI WinMain(
	_In_ HINSTANCE	   hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR		   lpCmdLine,
	_In_ int		   nCmdShow)
{
	// 1. Window 클래스 인스턴스 생성
	// 생성자에 WinMain이 받은 인스턴스 핸들을 전달합니다.
	Window myWindow(hInstance);

	// 2. 윈도우 초기화
	// Initialize 함수를 호출하여 실제 윈도우를 생성하고 화면에 표시합니다.
	// 실패할 경우 -1을 반환하고 프로그램을 종료합니다.
	if (!myWindow.Initialize(1280, 720, L"테스트 윈도우 - My Game Engine"))
	{
		MessageBox(nullptr, L"Window 초기화 실패!", L"에러", MB_OK | MB_ICONERROR);
		return -1;
	}

	// 3. 메인 루프 (게임 루프)
	// ProcessMessages()가 false를 반환할 때까지 (즉, WM_QUIT 메시지를 받을 때까지)
	// 루프를 계속 실행합니다.
	bool isRunning = true;
	while (isRunning)
	{
		// 메시지 큐에 있는 모든 메시지를 처리합니다.
		// false가 반환되면 루프를 종료합니다.
		if (!myWindow.ProcessMessages())
		{
			isRunning = false;
		}

		// --- 게임 로직 업데이트는 여기에 ---
		// (예: 플레이어 위치 업데이트, 충돌 감지 등)

		// --- 렌더링 코드는 여기에 ---
		// (예: 화면에 오브젝트 그리기)
	}

	return 0;
}