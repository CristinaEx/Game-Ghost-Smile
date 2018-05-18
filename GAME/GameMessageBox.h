#pragma once

#include<Windows.h>
#include<string>

class GameMessageBox {
public:
	int mode = 0;//初始状态未触发
	int end_mode = 360;//默认360帧后结束
	std::string word;//显示消息
	HWND hwnd;
	GameMessageBox(){}
	GameMessageBox(HWND &hwnd) {
		this->hwnd = hwnd;
	}
	void run() {
		if (mode == end_mode)
			mode = 0;
		if (mode) {
			//...paint message
			HDC g_hdc = GetDC(hwnd);
			TextOut(g_hdc, 200, 550, word.c_str(), word.length());
			ReleaseDC(hwnd, g_hdc);
			mode++;
		}
	}
	//添加一个消息框
	void add(std::string word,int end_mode = 360) {
		this->end_mode = end_mode;
		this->word = word;
	}
};