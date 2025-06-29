// window.cpp
#include "window.h"

// 생성자는 이제 멤버 변수를 안전한 기본값으로 초기화하는 역할만 합니다.
Window::Window(HINSTANCE hInstance)
	: Hinstance(hInstance), Hwnd(nullptr), Width(0), Height(0), ClassName(L""), IsClassRegistered(false)
{
}

Window::~Window()
{
	if (Hwnd)
	{
		DestroyWindow(Hwnd);
	}
	// 클래스가 성공적으로 등록되었을 때만 등록 해제를 시도합니다.
	if (IsClassRegistered)
	{
		UnregisterClass(ClassName.c_str(), Hinstance);
	}
}

// 공개된 초기화 메서드. 모든 초기화 과정을 조율(Orchestrate)합니다.
bool Window::Initialize(int width, int height, const std::wstring& title)
{
	Width = width;
	Height = height;
	Title = title;

	this->ClassName = L"Window Test";

	if (!RegisterWindowClass())
	{
		return false;
	}

	if (!CreateActualWindow())
	{
		return false;
	}

	// 모든 과정이 성공했으면 창을 보여줍니다.
	ShowWindow(Hwnd, SW_SHOWDEFAULT);
	UpdateWindow(Hwnd);

	return true;
}

bool Window::RegisterWindowClass()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = Hinstance;
	wc.lpszClassName = ClassName.c_str();
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// ... 아이콘 설정 ...

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Window Class Registration Failed!", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	IsClassRegistered = true;
	return true;
}

bool Window::CreateActualWindow()
{
	RECT wr = { 0, 0, Width, Height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	Hwnd = CreateWindowEx(
		0,
		ClassName.c_str(),
		Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		Hinstance,
		this // WindowProc에 이 인스턴스의 포인터를 전달
	);

	if (!Hwnd)
	{
		MessageBox(nullptr, L"Window Creation Failed!", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

bool Window::ProcessMessages()
{
	MSG msg = { 0 };

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
		pWindow->Hwnd = hWnd;
	}
	else
	{
		pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pWindow)
	{
		return pWindow->HandleMessage(uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// 실제 메시지 처리는 이 멤버 함수에서 함
LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

			// 향후 WM_KEYDOWN, WM_MOUSEMOVE 등 다른 메시지들을 이곳에 추가
	}

	return DefWindowProc(Hwnd, uMsg, wParam, lParam);
}
