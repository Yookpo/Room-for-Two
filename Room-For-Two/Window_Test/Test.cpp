#include "window.h"
#include <memory>
#include <Windows.h> // UNREFERENCED_PARAMETER 매크로를 위해 포함

int WINAPI WinMain(
	_In_ HINSTANCE	   hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR		   lpCmdLine,
	_In_ int		   nCmdShow)
{
	// 사용하지 않는 매개변수라고 명시적으로 표시하여 경고를 제거합니다.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow); // nCmdShow도 사용하지 않는다면 추가

	auto testWindow = std::make_unique<Window>(hInstance);

	if (!testWindow->Initialize(640, 480, L"Window Library Test"))
	{
		MessageBox(nullptr, L"Window 초기화 실패!", L"테스트 에러", MB_OK);
		return -1;
	}

	bool isRunning = true;
	while (isRunning)
	{
		if (!testWindow->ProcessMessages())
		{
			isRunning = false;
		}
	}

	return 0;
}