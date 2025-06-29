// Main.cpp
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Window.h" // ������ Window Ŭ���� ���

/**
 * @brief Win32 ���ø����̼��� �� �������Դϴ�.
 * @param hInstance ���ø����̼��� �ν��Ͻ� �ڵ��Դϴ�.
 * @param hPrevInstance ���� �ν��Ͻ��� �ڵ��Դϴ�. (����� ������ ����)
 * @param lpCmdLine Ŀ�ǵ� ���� �����Դϴ�.
 * @param nCmdShow â�� ǥ���ϴ� ����� �����մϴ�.
 * @return ���ø����̼� ���� �ڵ��Դϴ�.
 */
int WINAPI WinMain(
	_In_ HINSTANCE	   hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR		   lpCmdLine,
	_In_ int		   nCmdShow)
{
	// 1. Window Ŭ���� �ν��Ͻ� ����
	// �����ڿ� WinMain�� ���� �ν��Ͻ� �ڵ��� �����մϴ�.
	Window myWindow(hInstance);

	// 2. ������ �ʱ�ȭ
	// Initialize �Լ��� ȣ���Ͽ� ���� �����츦 �����ϰ� ȭ�鿡 ǥ���մϴ�.
	// ������ ��� -1�� ��ȯ�ϰ� ���α׷��� �����մϴ�.
	if (!myWindow.Initialize(1280, 720, L"�׽�Ʈ ������ - My Game Engine"))
	{
		MessageBox(nullptr, L"Window �ʱ�ȭ ����!", L"����", MB_OK | MB_ICONERROR);
		return -1;
	}

	// 3. ���� ���� (���� ����)
	// ProcessMessages()�� false�� ��ȯ�� ������ (��, WM_QUIT �޽����� ���� ������)
	// ������ ��� �����մϴ�.
	bool isRunning = true;
	while (isRunning)
	{
		// �޽��� ť�� �ִ� ��� �޽����� ó���մϴ�.
		// false�� ��ȯ�Ǹ� ������ �����մϴ�.
		if (!myWindow.ProcessMessages())
		{
			isRunning = false;
		}

		// --- ���� ���� ������Ʈ�� ���⿡ ---
		// (��: �÷��̾� ��ġ ������Ʈ, �浹 ���� ��)

		// --- ������ �ڵ�� ���⿡ ---
		// (��: ȭ�鿡 ������Ʈ �׸���)
	}

	return 0;
}