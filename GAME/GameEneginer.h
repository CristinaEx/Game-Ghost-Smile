#pragma once
#include "windows.h"
#include "MusicPlayer.h"
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
	GameEneginer(HWND &hwnd, MusicPlayer &py) : box(hwnd){
		this->hwnd = hwnd;
		map = Map(py);
		player = Player(box);
	}
	//��Ϸ���ݳ�ʼ��
	//��data_pathΪNULL���򴴽�����Ϸ
	void init(std::string data_path = "") {
		if (data_path.empty()) {
			//��������Ϸ
			map.init(1608);
			player.init();
		}
		else {
			//������Ϸ
		}
	}
	//���л
	void run() {
		//�������������Ϣ
		if (player.hp_now <= 0)
			over();
		else {
			paintPic(map.background);
			//���������Ϣ
			player.run();
			//��ͼԪ��
			map.run(player, box);
			dealMeaasge();
			map.paint(hwnd);
			player.paint(hwnd);
		}
		box.run();
	}
private:

	//����ͼƬ
	void paintPic(HBITMAP &bg , int x = 0,int y = 0) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//��ͼƬ�ŵ�HDC��  
		BitBlt(g_hdc, x, y, 960, 640, mmhdc, 0, 0, SRCCOPY);//�������豸������  
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}

	//��������
	void over() {
		box.add("Game Over ! (�����밴�ո�,���ر��⻭���밴�س�)", 30);
		if (player.hp_now == 0) {
			map.player.close();
			CImage img;
			img.Load("img\\over.jpg");
			HBITMAP bg = img.Detach();
			paintPic(bg);
			map.player.play("bgm\\start.wav");
			player.hp_now = -1;
			box.element_message = GAMEENEGINER | CHECK_EMPTY;
			DeleteObject(bg);
			img.Destroy();
		}
		else{
			if (box.element_message == (PLAYER | CHECK_TRUE)) {
				player.hp_now = player.hp_max;
				map.init(map.map_mode);
			}
		}
	}

	//����messagebox����Ϣ
	void dealMeaasge() {
		if (box.mode == 0)
			return;
		switch (box.element_message & 0xf000) {
		case PLAYER:
			break;
		case DOOR:
			map.init(0x0fff & box.element_message);
			box.element_message = CHECK_EMPTY;
			break;
		default:
			break;
		}
	}
};