#pragma once
#include "SpecialAttack.h"
#include <math.h>

class FallAttack : public SpecialAttack {
public:
	//count : 30~15->Ԥ�� 15~0->����
	int sleep = 10;//����˺������ʱ
	HBITMAP img;

	FallAttack(int x, int y, int demage) {
		this->x = x;
		this->y = y;
		this->demage = demage;
		CImage img;
		img.Load("img\\attack\\fall_attack.png");
		this->img = img.Detach();
		img.Destroy();
	}

	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		if (count >= 15) {
			//����ʵ�ߣ����Ϊ2����ɫ�ı�
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			//����ѡ��DC
			HPEN *hOldPen = (HPEN*)SelectObject(g_hdc, hPen);
			MoveToEx(g_hdc, x, y, NULL);
			LineTo(g_hdc, x + 25, y);
			MoveToEx(g_hdc, x + 25, y, NULL);
			LineTo(g_hdc, x + 25, y + 50);
			MoveToEx(g_hdc, x + 25, y + 50, NULL);
			LineTo(g_hdc, x, y + 50);
			MoveToEx(g_hdc, x, y + 50, NULL);
			LineTo(g_hdc, x, y);
			SelectObject(g_hdc, hOldPen);
			DeleteObject(hPen);
		}
		else if (count != 0) {
			HDC mmhdc = CreateCompatibleDC(g_hdc);
			HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, img);//��ͼƬ�ŵ�HDC��  
			TransparentBlt(g_hdc, x, y, 25, 50, mmhdc, 0, 0, 25, 50, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ 
			SelectObject(g_hdc, hp);
			DeleteDC(mmhdc);
		}
		ReleaseDC(hwnd, g_hdc);
	}
	void run(Player &player) {
		if (count == 0)return;
		else if (count <= 15 && count != 0) {
			if ((abs(player.x - x) <= 25 && abs(player.y - y) <= 50 ) && sleep <= 0)
			{
				sleep = 10;
				player.hp_now -= demage;
			}
			else
				sleep--;
		}
		count--;
	}
private:
	~FallAttack() {
		DeleteObject(img);
	}
};