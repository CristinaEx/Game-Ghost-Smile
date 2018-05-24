#pragma once
#include "SpecialAttack.h"
#include <math.h>

class MoveAttack : public SpecialAttack {
public:
	int sleep = 0;
	//从x = 0到x = 760
	HBITMAP img;
	MoveAttack(int y,int demage) {
		this->x = 0;
		this->y = y;
		this->demage = demage;
		CImage img;
		img.Load("img\\attack\\move_attack.png");
		this->img = img.Detach();
		img.Destroy();
		count = 0;
	}
	void paint(HWND &hwnd) {
		if (count <= 0)
			return;
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, img);//将图片放到HDC上  
		TransparentBlt(g_hdc, x, y, 200, 35, mmhdc, 0, 0, 200, 35, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色 
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	void run(Player &player) {
		if (count == 0)return;
		else if (count <= 20) {
			if (abs(player.x - x) <= 200 && abs(player.y - y) <= 35 && sleep <= 0) {
				sleep = 10;
				player.hp_now -= demage;
			}
			else
				sleep--;
			x += 40;
		}		
		count--;
	}
};