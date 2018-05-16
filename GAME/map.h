#pragma once
#include <windows.h>
#include <iostream>  
#include <fstream>  
#include <sstream>
#include <atlimage.h>

#define MAP_START 1601

class Map {
public:
	HBITMAP background;//地图的背景
	MusicPlayer player;//音乐播放
	int map_mode = 0;
	Map() {}
	Map(MusicPlayer player) {
		this->player = player;
	}
	//载入map
	void init(int map_mode = MAP_START) {
		this->map_mode = map_mode;
		//载入地图
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
				//文件第二行为bgm
				player.play(str);
				mode++;
				break;
			default:
				//其余行为map内成员
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