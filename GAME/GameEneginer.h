#pragma once
#include "windows.h"
#include "MusicPlayer.h"
#include "StaticElement.h"

//��Ϸ����
class GameEneginer {
public:
	HWND hwnd;//�����ھ��
	Map map;//��ͼ
	GameEneginer() {}
	GameEneginer(HWND &hwnd, MusicPlayer &player) {
		this->hwnd = hwnd;
		map = Map(player);
	}
	//��Ϸ���ݳ�ʼ��
	//��data_pathΪNULL���򴴽�����Ϸ
	void init(std::string data_path = "") {
		if (data_path.empty()) {
			//��������Ϸ
			map.init();
		}
		else {
			//������Ϸ
		}
	}
	//���л
	void run() {
		paintPic(map.background);
	}
private:
	//����ͼƬ
	void paintPic(HBITMAP &bg , int x = 0,int y = 0) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		SelectObject(mmhdc, bg);//��ͼƬ�ŵ�HDC��  
		BitBlt(g_hdc, x, y, 960, 640, mmhdc, 0, 0, SRCCOPY);//�������豸������  
		DeleteDC(mmhdc);
		DeleteObject(bg);
		ReleaseDC(hwnd, g_hdc);
	}
};