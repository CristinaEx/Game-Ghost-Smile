#pragma once

#include <vector>
#include "SpecialAttack.h"

#define LINE_AUTO 0
#define LINE_RIGHT 1
#define LINE_BUTTON 2
#define LINE_LEFT 3
#define LINE_TOP 4


#define PI 3.14159265

class LineAttack : public SpecialAttack {
public:
	//count : 45~15->预警 15~0->攻击
	int mode;//mode = 0
	int sleep = 0;
	std::vector<HBITMAP> imgs;
	LineAttack(int x, int y, int demage,int mode) {
		this->x = x;
		this->y = y;
		this->demage = demage;
		mode = mode;
		CImage img;
		img.Load("img\\attack\\line_attack_right.jpg");
		imgs.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\attack\\line_attack_button.jpg");
		imgs.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\attack\\line_attack_left.jpg");
		imgs.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\attack\\line_attack_top.jpg");
		imgs.push_back(img.Detach());
		img.Destroy();
	}
	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		if (mode != 0 && count != 0) {
			int index;
			switch (mode) {
			case LINE_RIGHT:
				index = 0;
				break;
			case LINE_BUTTON:
				index = 1;
				break;
			case LINE_LEFT:
				index = 2;
				break;
			case LINE_TOP:
				index = 3;
				break;
			default:
				break;
			}
			//旋转
			SelectObject(mmhdc, imgs[index]);//将图片放到HDC上  
			TransparentBlt(g_hdc, x, y, 50, 50, mmhdc, 0, 0, 50, 50, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色 
			//绘制攻击图片
			if (count <= 15) {
				//创建一个黑色的刷子
				HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
				HBRUSH *oldBrush = (HBRUSH*)SelectObject(g_hdc, hBrush);
				switch (mode) {
				case LINE_RIGHT:
					Rectangle(g_hdc, 0, y, 900, y+50);
					break;
				case LINE_BUTTON:
					Rectangle(g_hdc, x, 0, x+50, 500);
					break;
				case LINE_LEFT:
					Rectangle(g_hdc, 50, y, 950, y+50);
					break;
				case LINE_TOP:
					Rectangle(g_hdc, x, 150, x+50, 600);
					break;
				default:
					break;
				}
				SelectObject(g_hdc, oldBrush);
				DeleteObject(hBrush);
			}
		}
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	void run(Player &player) {
		if (count == 0)return;
		if (count <= 15) {
			switch (mode) {
			case LINE_RIGHT:
				if (sleep <= 0 && abs(player.y - y) <= 50) {
					sleep = 10;
					player.hp_now -= demage;
				}
				else
					sleep--;
				break;
			case LINE_BUTTON:
				if (sleep <= 0 && abs(player.x - x) <= 50) {
					sleep = 10;
					player.hp_now -= demage;
				}
				else
					sleep--;
				break;
			case LINE_LEFT:
				if (sleep <= 0 && abs(player.y - y) <= 50) {
					sleep = 10;
					player.hp_now -= demage;
				}
				else
					sleep--;
				break;
			case LINE_TOP:
				if (sleep <= 0 && abs(player.x - x) <= 50) {
					sleep = 10;
					player.hp_now -= demage;
				}
				else
					sleep--;
				break;
			default:
				break;
			}
		}
		count--;
	}
private:
	//alpha角度相位
	void paintTranspose(int width, int height, int alpha,HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		//旋转
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, imgs[3]);//将图片放到HDC上  
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				//计算旋转后的坐标
				int destx = (int)(i * cos(alpha*PI/180) - j * sin(alpha*PI/180));
				int desty = (int)(i * sin(alpha*PI/180) + j * cos(alpha*PI/180));
				if(i < width && j < height)BitBlt(g_hdc, destx + x, desty + y, 1, 1, mmhdc, i, j, SRCCOPY);
			}
		SelectObject(g_hdc,hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	~LineAttack() {
		for (HBITMAP hp : imgs)
			DeleteObject(hp);
	}
};