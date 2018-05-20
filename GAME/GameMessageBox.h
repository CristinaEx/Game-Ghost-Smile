#pragma once

#include<Windows.h>
#include<string>

#define CHECK_EMPTY 0x0000

#define CHECK_TRUE 0x0001
#define CHECK_FALSE 0x0002

#define PLAYER 0x1000
#define DOOR 0x2000
#define GAMEENEGINER 0x3000

class GameMessageBox {
public:
	int element_message;//�жϰ���ѡ��
	int mode = 0;//��ʼ״̬δ����
	int end_mode =240;//Ĭ��240֡�����
	std::string word;//��ʾ��Ϣ
	HWND hwnd;
	GameMessageBox(){}
	GameMessageBox(HWND &hwnd) {
		this->hwnd = hwnd;
		element_message = CHECK_EMPTY;
	}
	void run() {
		if (mode == end_mode) {
			mode = 0;
			element_message = CHECK_EMPTY;
		}	
		if (mode) {
			//...paint message
			HDC g_hdc = GetDC(hwnd);
			//����ʵ�ߣ����Ϊ2����ɫ�ı�
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
			//����ѡ��DC
			HPEN *hOldPen = (HPEN*)SelectObject(g_hdc, hPen);
			//����һ����ɫ��ˢ��
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
			HBRUSH *oldBrush = (HBRUSH*)SelectObject(g_hdc, hBrush);
			//���ƾ��Σ���Ϊ��û�л������Ի��Ƶ��ǰ�ɫ�߿򣬺�ɫ����ľ���
			Rectangle(g_hdc, 150, 545, 750, 570);
			SetTextColor(g_hdc, RGB(255, 255, 255));
			SetBkColor(g_hdc, RGB(0, 0, 0));
			TextOut(g_hdc, 200, 550, word.c_str(), word.length());
			ReleaseDC(hwnd, g_hdc);
			SelectObject(g_hdc, oldBrush);
			DeleteObject(hBrush);
			SelectObject(g_hdc, hOldPen);
			DeleteObject(hPen);
			mode++;
		}
	}
	//���һ����Ϣ��
	void add(std::string word,int end_mode = 240) {
		this->mode = 1;
		this->end_mode = end_mode;
		this->word = word;
	}
};