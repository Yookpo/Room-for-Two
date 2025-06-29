// Test.cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include "Window.h" // �츮�� ���� Window.h ���

// Win32 GUI ���ø����̼ǿ��� �ܼ� â�� ����ϱ� ���� ���� �Լ�
void CreateConsole()
{
	AllocConsole();
	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	freopen_s(&pFile, "CONIN$", "r", stdin);
	std::cout << "--- �̺�Ʈ �α� �ܼ� ---" << std::endl;
}

// ���ø����̼��� �̺�Ʈ ó�� ������ ����� �Լ� (�Ǵ� ����)
void OnEvent(Event& e)
{
	// �̺�Ʈ �޽��� ������ ���� �б��Ͽ� ó���մϴ�.
	switch (e.uMsg)
	{
		case WM_KEYDOWN:
		{
			// wParam�� ���� Ű �ڵ尡 ��� �ɴϴ�.
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
			// lParam�� ���콺�� ��ǥ�� ��� �ɴϴ�.
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
			// ���⼭ "�����Ͻðڽ��ϱ�?" ���� ������ ������ �� �ֽ��ϴ�.
			// ���� ����� Window Ŭ������ WM_DESTROY���� ó���˴ϴ�.
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
	// 1. ����� �� �α� ����� ���� �ܼ� â ����
	CreateConsole();

	// 2. Window �ν��Ͻ� ����
	Window window(hInstance); //

	// 3. �̺�Ʈ �ݹ� �Լ� ���
	//    window.SetEventCallback�� ����Ͽ� �츮�� ���� OnEvent �Լ��� "���"�մϴ�.
	//    �������� window���� �߻��ϴ� ��� �̺�Ʈ�� OnEvent �Լ��� ���޵˴ϴ�.
	window.SetEventCallback(OnEvent); //

	// 4. ������ �ʱ�ȭ �� ����
	if (!window.Initialize(1280, 720, L"�̺�Ʈ �׽�Ʈ")) //
	{
		return -1;
	}

	// 5. ���� ���� ����
	//    ProcessMessages()�� WM_QUIT �޽����� ���� ������ true�� ��ȯ�մϴ�.
	while (window.ProcessMessages())
	{
		// ���� ���� �� ������ �ڵ尡 ��ġ�� ��...
		// �� ���������� �ݹ� ó���� Ȯ���ϹǷ� ����Ӵϴ�.
	}

	return 0;
}