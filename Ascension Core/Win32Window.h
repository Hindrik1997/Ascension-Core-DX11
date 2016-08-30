//
// Created by Hindrik Stegenga on 7/28/2016.
//

#ifndef ASCENSION_CORE_WIN32_WINDOW_H
#define ASCENSION_CORE_WIN32_WINDOW_H

#include <string>
#include "SimpleInput.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Keyboard.h>
#include <Mouse.h>

template<typename T>
class Win32Window
{
public:

	HWND hWnd;
	HINSTANCE hInstance;
	T* WindowRenderer;
	int Width;
	int Height;
	SimpleInput Input;

	Win32Window(int width, int height) : Width(width), Height(height)
	{
		hInstance = GetModuleHandle(NULL);
		std::wstring WndClassName = L"ENGINE";

		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = StaticWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_HAND);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = WndClassName.c_str();
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		if (!RegisterClassEx(&wc)) {
			MessageBox(NULL, L"Error registering class", L"Error", MB_OK);
			throw;
		}

		hWnd = CreateWindowEx(WS_EX_APPWINDOW, WndClassName.c_str(), L"ASCENSION GAME ENGINE", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, this);

		if (!hWnd)
		{
			MessageBox(NULL, L"Error Creating Window", L"Error", MB_OK | MB_ICONERROR);
			throw;
		}

		ShowWindow(hWnd, 1);
		UpdateWindow(hWnd);
		
	};
	~Win32Window()
	{
		UnregisterClass(L"ENGINE", hInstance);
	};

	bool ProcessMessages()
	{

		MSG msg = { 0 };
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return false;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
	};
	LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			/*
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
			Mouse::ProcessMessage(msg, wParam, lParam);
			return 0;
*/
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(0, L"Are you sure you want to quit", L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
					DestroyWindow(hwnd);
			}
			else
			{
				Input.KeyDown(static_cast<unsigned int>(wParam));
			}
		} return 0;

		case WM_KEYUP:
		{
			Input.KeyUp(static_cast<unsigned int>(wParam));
		} break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} return 0;
		case WM_SIZE:
		{
			if (WindowRenderer)
			{
				RECT t;
				GetClientRect(hWnd, &t);
				Width = t.right - t.left;
				Height = t.bottom - t.top;
				//resizen enz.
				//WindowRenderer->SwapChain->ResizeBuffers();
			}
		} break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	};
	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Win32Window<T>* parent;

		if (msg == WM_CREATE)
		{
			parent = (Win32Window<T>*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)parent);
		}
		else
		{
			parent = (Win32Window<T>*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (!parent) return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		parent->hWnd = hwnd;
		return parent->WindowProcedure(hwnd, msg, wParam, lParam);
	};
};

#endif