#pragma once
#include "SpecialAttack.h"
#include <math.h>

class FallAttack : public SpecialAttack {
public:
	//count : 30~15->预警 15~0->攻击
	int sleep = 10;//造成伤害后的延时
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
			//创建实线，宽度为2，红色的笔
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			//将笔选入DC
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
			HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, img);//将图片放到HDC上  
			TransparentBlt(g_hdc, x, y, 25, 50, mmhdc, 0, 0, 25, 50, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色 
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