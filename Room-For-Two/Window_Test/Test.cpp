#include "window.h"
#include <memory>
#include <Windows.h> // UNREFERENCED_PARAMETER ��ũ�θ� ���� ����

int WINAPI WinMain(
	_In_ HINSTANCE	   hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR		   lpCmdLine,
	_In_ int		   nCmdShow)
{
	// ������� �ʴ� �Ű�������� ��������� ǥ���Ͽ� ��� �����մϴ�.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow); // nCmdShow�� ������� �ʴ´ٸ� �߰�

	auto testWindow = std::make_unique<Window>(hInstance);

	if (!testWindow->Initialize(640, 480, L"Window Library Test"))
	{
		MessageBox(nullptr, L"Window �ʱ�ȭ ����!", L"�׽�Ʈ ����", MB_OK);
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