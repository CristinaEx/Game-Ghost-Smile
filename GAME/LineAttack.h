#pragma once

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
	LineAttack(int x, int y, int demage,int mode) {
		this->x = x;
		this->y = y;
		this->demage = demage;
		mode = mode;
	}
	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		if (mode != 0 && count != 0) {
			CImage img;
			switch (mode) {
			case LINE_RIGHT:
				img.Load("img\\attack\\line_attack_right.jpg");
				break;
			case LINE_BUTTON:
				img.Load("img\\attack\\line_attack_button.jpg");
				break;
			case LINE_LEFT:
				img.Load("img\\attack\\line_attack_left.jpg");
				break;
			case LINE_TOP:
				img.Load("img\\attack\\line_attack_top.jpg");
				break;
			default:
				img.Load("img\\attack\\line_attack_right.jpg");
				break;
			}
			//旋转
			SelectObject(mmhdc, img.Detach());//将图片放到HDC上  
			TransparentBlt(g_hdc, x, y, 50, 50, mmhdc, 0, 0, 50, 50, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色 
			//绘制攻击图片
			if (count <= 15) {
				//创建一个黑色的刷子
				HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
				HBRUSH hOldBrush = (HBRUSH)SelectObject(g_hdc, hBrush);
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
		CImage img;
		img.Load("img\\attack\\line_attack.jpg");
		//旋转
		SelectObject(mmhdc, img.Detach());//将图片放到HDC上  
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				//计算旋转后的坐标
				int destx = (int)(i * cos(alpha*PI/180) - j * sin(alpha*PI/180));
				int desty = (int)(i * sin(alpha*PI/180) + j * cos(alpha*PI/180));
				if(i < width && j < height)BitBlt(g_hdc, destx + x, desty + y, 1, 1, mmhdc, i, j, SRCCOPY);
			}
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
};