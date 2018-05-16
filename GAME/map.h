#pragma once
#include <windows.h>
#include <iostream>  
#include <fstream>  
#include <sstream>
#include <atlimage.h>

#define MAP_START 1601

class Map {
public:
	HBITMAP background;//��ͼ�ı���
	MusicPlayer player;//���ֲ���
	int map_mode = 0;
	Map() {}
	Map(MusicPlayer player) {
		this->player = player;
	}
	//����map
	void init(int map_mode = MAP_START) {
		this->map_mode = map_mode;
		//�����ͼ
		std::string str;
		std::ifstream in("map\\" + int2str(map_mode) + ".dat", std::ios::in);
		int mode = 0;
		CImage img;
		while (!in.eof())
		{
			getline(in,str);
			switch (mode) {
			case 0:
				img.Load(str.c_str());
				background = img.Detach();
			case 1:
				//�ļ��ڶ���Ϊbgm
				player.play(str);
				mode++;
				break;
			default:
				//������Ϊmap�ڳ�Ա
				mode++;
				break;
			}
		}
	}
private:
	std::string int2str(const int &int_temp)
	{
		std::stringstream stream;
		stream << int_temp;
		return stream.str(); 
	}
};