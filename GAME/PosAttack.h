#pragma once
#include "SpecialAttack.h"
#include <math.h>

class PosAttack : public SpecialAttack {
public:
	//count : 30~15->Ԥ�� 15~0->����
	int sleep = 10;//����˺������ʱ

	PosAttack(int x, int y ,int demage) {
		this->x = x;
		this->y = y;
		this->demage = demage;
	}

	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		if (count >= 15) {
			//����ʵ�ߣ����Ϊ2����ɫ�ı�
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			//����ѡ��DC
			HPEN hOldPen = (HPEN)SelectObject(g_hdc, hPen);
			MoveToEx(g_hdc, x, y, NULL);
			LineTo(g_hdc, x + 50, y);
			MoveToEx(g_hdc, x + 50, y, NULL);
			LineTo(g_hdc, x + 50, y + 50);
			MoveToEx(g_hdc, x + 50, y + 50, NULL);
			LineTo(g_hdc, x, y + 50);
			MoveToEx(g_hdc, x, y + 50, NULL);
			LineTo(g_hdc, x, y);
		}
		else if(count != 0){
			CImage img;
			img.Load("img\\attack\\pos_attack.jpg");
			HDC mmhdc = CreateCompatibleDC(g_hdc);
			SelectObject(mmhdc,img.Detach());//��ͼƬ�ŵ�HDC��  
			TransparentBlt(g_hdc, x, y, 50, 50, mmhdc, 0, 0, 50, 50, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ 
			DeleteDC(mmhdc);
		}
		ReleaseDC(hwnd, g_hdc);
	}
	void run(Player &player) {
		if (count == 0)return;
		else if (count <= 15 && count != 0) {
			if (pow(player.x - x, 2) + pow(player.y - y, 2) <= 2500 && sleep <= 0)
			{
				sleep = 10;
				player.hp_now -= demage;
			}
			else
				sleep--;
		}
		count--;
	}
};