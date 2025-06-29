// window.cpp
#include "window.h"

// �����ڴ� ���� ��� ������ ������ �⺻������ �ʱ�ȭ�ϴ� ���Ҹ� �մϴ�.
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
	// Ŭ������ ���������� ��ϵǾ��� ���� ��� ������ �õ��մϴ�.
	if (IsClassRegistered)
	{
		UnregisterClass(ClassName.c_str(), Hinstance);
	}
}

// ������ �ʱ�ȭ �޼���. ��� �ʱ�ȭ ������ ����(Orchestrate)�մϴ�.
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

	// ��� ������ ���������� â�� �����ݴϴ�.
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
	// ... ������ ���� ...

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
		this // WindowProc�� �� �ν��Ͻ��� �����͸� ����
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

// ���� �޽��� ó���� �� ��� �Լ����� ��
LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

			// ���� WM_KEYDOWN, WM_MOUSEMOVE �� �ٸ� �޽������� �̰��� �߰�
	}

	return DefWindowProc(Hwnd, uMsg, wParam, lParam);
}
