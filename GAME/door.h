#pragma once
#include "StaticElement.h"
#include "GameMessageBox.h"

class Door : public StaticElement {
public:
	int next_map;
	Door(std::string data) {
		//��ȡ����...
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		width = str2int(datas[2]);
		height = str2int(datas[3]);
		next_map = str2int(datas[4]);
	}
	void run(Player &player, GameMessageBox &box) {
		if (!check(player.x, player.y))
			return;
	}
private:
	//ʹ��c��Ϊ�ָ����и��ַ���s
	std::vector<std::string> splitString(const std::string& s, const char c)
	{
		std::vector<std::string> result;
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while (std::string::npos != pos2)
		{
			result.push_back(s.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 1;
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			result.push_back(s.substr(pos1));
		return result;
	}

	//string -> int
	int str2int(const std::string &string_temp)
	{
		std::stringstream stream(string_temp);
		int int_temp;
		stream >> int_temp;
		return int_temp;
	}

};