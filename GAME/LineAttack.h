#pragma once

#include "SpecialAttack.h"

#define LINE_AUTO 0
#define LINE_LEFT 1
#define LINE_RIGHT 2
#define LINE_TOP 3
#define LINE_BUTTON 4

class LineAttack : public SpecialAttack {
public:
	//count : 30~15->Ԥ�� 15~0->����
	int mode;//mode == 0
	LineAttack(int x, int y, int demage,int mode) {
		this->x = x;
		this->y = y;
		this->demage = demage;
		mode = mode;
	}
	void paint(HWND &hwnd) {
		if (count >= 15) {
			HDC g_hdc = GetDC(hwnd);
			HDC mmhdc = CreateCompatibleDC(g_hdc);
			CImage img;
			img.Load("img\\attack\\line_attack.jpg");
			SelectObject(mmhdc, img.Detach());//��ͼƬ�ŵ�HDC��  
			TransparentBlt(g_hdc, x, y, 50, 75, mmhdc, 0, 0, 50, 75, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  															   //BitBlt(g_hdc, x, y, 100, 150, mmhdc, 0, 0, SRCCOPY);//�������豸������  
			DeleteDC(mmhdc);
			ReleaseDC(hwnd, g_hdc);
		}
	}
	void run(Player &player) {
		if (count == 0)return;
		count--;
	}
};