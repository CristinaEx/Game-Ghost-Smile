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
	int element_message;//判断按键选项
	int mode = 0;//初始状态未触发
	int end_mode =240;//默认240帧后结束
	std::string word;//显示消息
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
			//创建实线，宽度为2，白色的笔
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
			//将笔选入DC
			HPEN *hOldPen = (HPEN*)SelectObject(g_hdc, hPen);
			//创建一个黑色的刷子
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
			HBRUSH *oldBrush = (HBRUSH*)SelectObject(g_hdc, hBrush);
			//绘制矩形，因为笔没有换，所以绘制的是白色边框，黑色区域的矩形
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
	//添加一个消息框
	void add(std::string word,int end_mode = 240) {
		this->mode = 1;
		this->end_mode = end_mode;
		this->word = word;
	}
};