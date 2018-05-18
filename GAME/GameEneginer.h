#pragma once
#include "windows.h"
#include "MusicPlayer.h"
#include "player.h"
#include "GameMessageBox.h"
#include "map.h"

//��Ϸ����
class GameEneginer {
public:
	HWND hwnd;//�����ھ��
	Map map;//��ͼ
	Player player;//���
	GameMessageBox box;//��Ϣ��
	GameEneginer() {}
	GameEneginer(HWND &hwnd, MusicPlayer &player) : box(hwnd){
		this->hwnd = hwnd;
		map = Map(player);
	}
	//��Ϸ���ݳ�ʼ��
	//��data_pathΪNULL���򴴽�����Ϸ
	void init(std::string data_path = "") {
		if (data_path.empty()) {
			//��������Ϸ
			map.init();
			player.init();
		}
		else {
			//������Ϸ
		}
	}
	//���л
	void run() {
		paintPic(map.background);
		//���������Ϣ
		player.run();
		//��ͼԪ��
		map.run(player,box);
		player.paint(hwnd);
	}
private:
	//����ͼƬ
	void paintPic(HBITMAP &bg , int x = 0,int y = 0) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		SelectObject(mmhdc, bg);//��ͼƬ�ŵ�HDC��  
		BitBlt(g_hdc, x, y, 960, 640, mmhdc, 0, 0, SRCCOPY);//�������豸������  
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
};