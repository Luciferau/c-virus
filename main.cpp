#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM 1024
int rects[NUM][4];

int main() {


	//�ҵ��������Դ���
	HWND hwnd = GetDesktopWindow();
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
	//���и�֮ǰ���Ѵ�������
	if (LockWindowUpdate(hwnd) == false) {
		return 1;
	}

	//׼���и�

	//1.��ȡ�����豸������
	HDC hdcSrc = GetDCEx(hwnd, NULL, DCX_CACHE/*���ٻ��洰���е��豸������*/ | DCX_LOCKWINDOWUPDATE/*��ס���ڸ���*/);
	//2.����һ���ڴ��豸������ �봰���豸�����
	HDC hdcMem = CreateCompatibleDC(hdcSrc);
	//3.�ж�� ������ ��� �߶ȣ�
	int cx = GetSystemMetrics(SM_CXSCREEN) / 10;//�и�С��Ŀ��
	int cy = GetSystemMetrics(SM_CYSCREEN) / 10;//�и�С��ĸ߶�

	//4.����һ���ʹ����豸��ص�λͼ
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSrc, cx, cy);

	//5.��λͼ���ڴ��豸��������
	 SelectObject(hdcMem, hBitmap);


	// ��ʼ�и��\\
	//�����и�����
	srand(GetCurrentTime());//ʹ�õ�ǰʱ�� ��Ϊʱ������

	for (int i = 0; i < NUM; i++)
	{
		rects[i][0] = cx * (rand() % 10);
		rects[i][1] = cy * (rand() % 10);
		rects[i][2] = cx * (rand() % 10);
		rects[i][3] = cy * (rand() % 10);

	}
	//�и�
	for (int i = 0; i < NUM; i++) {
		//��ͼ
		BitBlt(hdcMem,/*Ŀ���豸*/0, 0,/*Ŀ����������Ͻ�����*/cx, cy, hdcSrc, rects[i][0], rects[i][1], SRCCOPY/*������ʽ*/);
		BitBlt(hdcSrc, rects[i][2], rects[i][3], cx, cy, hdcMem, 0, 0, SRCCOPY);
		Sleep(1);
	}

	//������Դ

	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdcSrc);
	DeleteObject(hBitmap);

	return 0;
}


