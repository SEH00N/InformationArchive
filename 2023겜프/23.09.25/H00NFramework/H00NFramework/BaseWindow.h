#pragma once
class BaseWindow
{
public:
	BaseWindow(POINT resolution);
	~BaseWindow();

private:
	HWND		hWnd;
	HINSTANCE	hInstance;
	POINT		resolution;

public:
	int				Run(HINSTANCE hInstance, int cmdShow);

private:
	ATOM					MyRegisterClass();
	void					WindowCreate();
	void					WindowShow(int cmdShow);
	void					WindowUpdate();
	int						MessageLoop();
	static LRESULT CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

