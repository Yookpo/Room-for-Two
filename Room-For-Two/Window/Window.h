/**
 * @file window.h
 * @brief Win32 ������ ���� �� ������ ���� Window Ŭ������ �����մϴ�.
 * @author Yookpo
 * @date 2025-06-27
 */
#pragma once

#include <Windows.h>
#include <string>

/**
 * @class Window
 * @brief Win32 API�� ĸ��ȭ�Ͽ� �������� ����, �ʱ�ȭ, �޽��� ó���� ����ϴ� Ŭ����.
 * @details
 * �� Ŭ������ ��ü ������ ���� ������ ������ �и��ϴ� 2�ܰ� �ʱ�ȭ ������ ����մϴ�.
 * �����ӿ�ũ�� �ٽ� ���� ��ҷ�, �������� �Է� ������ �� �ٸ� ��⿡
 * ������ �ڵ�(HWND)�� �����ϴ� ��� ������ �մϴ�.
 */
class Window
{
public:
	/**
	 * @brief Window Ŭ������ �������Դϴ�.
	 * @details ��� ������ �ʱ�ȭ������, ���� �����츦 ���������� �ʽ��ϴ�.
	 * @param[in] hInstance ���ø����̼��� �ν��Ͻ� �ڵ��Դϴ�. WinMain���κ��� ���޹޽��ϴ�.
	 */
	explicit Window(HINSTANCE hInstance);

	/**
	 * @brief Window Ŭ������ �Ҹ����Դϴ�.
	 * @details ������ �����츦 �ı��ϰ� ��ϵ� ������ Ŭ������ �����Ͽ� ���ҽ��� �����մϴ�.
	 */
	~Window();

	// ���� �� ���� �����ڴ� ���ϼ��� �����ϱ� ���� �����մϴ�.
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	/**
	 * @brief �����츦 �ʱ�ȭ�ϰ� ȭ�鿡 ǥ���մϴ�.
	 * @details
	 * ���������� RegisterWindowClass�� CreateActualWindow�� ȣ���Ͽ� ������ ������
	 * ��� ������ ó���մϴ�. ���������� �����Ǹ� ShowWindow�� ���� â�� ȭ�鿡 ǥ���մϴ�.
	 * @param[in] width ������ �������� Ŭ���̾�Ʈ ���� �ʺ��Դϴ�.
	 * @param[in] height ������ �������� Ŭ���̾�Ʈ ���� �����Դϴ�.
	 * @param[in] title �������� ���� ǥ���ٿ� ǥ�õ� �ؽ�Ʈ�Դϴ�.
	 * @return �ʱ�ȭ�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.
	 */
	bool Initialize(int width, int height, const std::wstring& title);

	/**
	 * @brief ������ �޽��� ť�� ó���մϴ�.
	 * @details
	 * ���� ���� ������ �� ������ ȣ��Ǿ�� �մϴ�. PeekMessage�� ����Ͽ�
	 * �񵿱������� �޽����� ó���ϹǷ�, �޽����� ��� ���α׷��� ������ �ʽ��ϴ�.
	 * @return ���ø����̼��� ��� ����Ǿ�� �ϸ� true, WM_QUIT �޽����� �޾� �����ؾ� �ϸ� false�� ��ȯ�մϴ�.
	 */
	bool ProcessMessages();

	/**
	 * @brief ������ �ڵ�(HWND)�� ��ȯ�մϴ�.
	 * @return �� �ν��Ͻ��� �����ϴ� �������� �ڵ��Դϴ�. ������ �� �ٸ� ��⿡�� �ʿ��մϴ�.
	 */
	HWND GetHWND() const { return Hwnd; }

private:
	/**
	 * @brief ������ Ŭ����(WNDCLASSEX)�� Windows�� ����ϴ� ���� �޼����Դϴ�.
	 * @return Ŭ���� ��Ͽ� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.
	 */
	bool RegisterWindowClass();

	/**
	 * @brief ��ϵ� ������ Ŭ������ ������� ���� �����츦 �����ϴ� ���� �޼����Դϴ�.
	 * @return ������ ������ �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.
	 */
	bool CreateActualWindow();

	/**
	 * @brief Windows�κ��� �޽����� �����Ͽ� ó���ϴ� ���� �ݹ� �Լ�(������ ���ν���)�Դϴ�.
	 * @details
	 * C-��Ÿ�� �ݹ� �Լ��̹Ƿ� static���� ����Ǿ����ϴ�.
	 * WM_NCCREATE �޽��� �������� lParam���� ���޵� this �����͸� GWLP_USERDATA�� �����Ͽ�
	 * C++ Ŭ���� �ν��Ͻ��� ���� �����츦 �����ϴ� ������ �մϴ�.
	 * @param hWnd �޽����� �߻��� �������� �ڵ��Դϴ�.
	 * @param uMsg �޽����� ������ ��Ÿ���� �ĺ����Դϴ�.
	 * @param wParam �޽����� ���� �߰� �����Դϴ�. (WPARAM)
	 * @param lParam �޽����� ���� �߰� �����Դϴ�. (LPARAM)
	 * @return �޽��� ó�� ����Դϴ�. DefWindowProc�� ȣ���Ͽ� �⺻ ó���� ������ �� �ֽ��ϴ�.
	 */
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND		 Hwnd = nullptr;	  ///< ������ �������� ���� �ڵ��Դϴ�.
	HINSTANCE	 Hinstance = nullptr; ///< ���ø����̼��� �ν��Ͻ� �ڵ��Դϴ�.
	int			 Width = 0;			  ///< ������ Ŭ���̾�Ʈ ������ �ʺ��Դϴ�.
	int			 Height = 0;		  ///< ������ Ŭ���̾�Ʈ ������ �����Դϴ�.
	std::wstring Title;				  ///< �������� �����Դϴ�.
	std::wstring ClassName;			  ///< ������ Ŭ������ �̸��Դϴ�.
	bool		 IsClassRegistered;	  ///< ������ Ŭ������ ��� ���� ���θ� �����ϴ� �÷����Դϴ�.
};