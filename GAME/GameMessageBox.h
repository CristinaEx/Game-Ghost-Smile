#pragma once

#include<Windows.h>
#include<string>

class GameMessageBox {
public:
	int mode = 0;//��ʼ״̬δ����
	int end_mode = 360;//Ĭ��360֡�����
	std::string word;//��ʾ��Ϣ
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
	//���һ����Ϣ��
	void add(std::string word,int end_mode = 360) {
		this->end_mode = end_mode;
		this->word = word;
	}
};