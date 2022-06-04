#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM 1024
int rects[NUM][4];

int main() {


	//找到桌面的资源句柄
	HWND hwnd = GetDesktopWindow();
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
	//在切割之前，把窗口锁定
	if (LockWindowUpdate(hwnd) == false) {
		return 1;
	}

	//准备切割

	//1.获取桌面设备上下文
	HDC hdcSrc = GetDCEx(hwnd, NULL, DCX_CACHE/*高速缓存窗口中的设备上下文*/ | DCX_LOCKWINDOWUPDATE/*锁住窗口更新*/);
	//2.创建一个内存设备上下文 与窗口设备相兼容
	HDC hdcMem = CreateCompatibleDC(hdcSrc);
	//3.切多大 （窗口 宽度 高度）
	int cx = GetSystemMetrics(SM_CXSCREEN) / 10;//切割小块的宽度
	int cy = GetSystemMetrics(SM_CYSCREEN) / 10;//切割小块的高度

	//4.创建一个和窗口设备相关的位图
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSrc, cx, cy);

	//5.把位图和内存设备关联起来
	 SelectObject(hdcMem, hBitmap);


	// 开始切割！！\\
	//设置切割区域
	srand(GetCurrentTime());//使用当前时间 作为时间种子

	for (int i = 0; i < NUM; i++)
	{
		rects[i][0] = cx * (rand() % 10);
		rects[i][1] = cy * (rand() % 10);
		rects[i][2] = cx * (rand() % 10);
		rects[i][3] = cy * (rand() % 10);

	}
	//切割
	for (int i = 0; i < NUM; i++) {
		//绘图
		BitBlt(hdcMem,/*目标设备*/0, 0,/*目标区域的左上角坐标*/cx, cy, hdcSrc, rects[i][0], rects[i][1], SRCCOPY/*拷贝方式*/);
		BitBlt(hdcSrc, rects[i][2], rects[i][3], cx, cy, hdcMem, 0, 0, SRCCOPY);
		Sleep(1);
	}

	//清理资源

	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdcSrc);
	DeleteObject(hBitmap);

	return 0;
}


