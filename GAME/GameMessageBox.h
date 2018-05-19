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
	int element_message;//�жϰ���ѡ��
	int mode = 0;//��ʼ״̬δ����
	int end_mode =240;//Ĭ��240֡�����
	std::string word;//��ʾ��Ϣ
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
	//���һ����Ϣ��
	void add(std::string word,int end_mode = 240) {
		this->mode = 1;
		this->end_mode = end_mode;
		this->word = word;
	}
};