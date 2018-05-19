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
			TextOut(g_hdc, 200, 550, word.c_str(), word.length());
			ReleaseDC(hwnd, g_hdc);
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