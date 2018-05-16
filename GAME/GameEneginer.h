#pragma once
#include "windows.h"
#include "MusicPlayer.h"

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
};