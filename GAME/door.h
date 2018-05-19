#pragma once
#include "StaticElement.h"
#include "map.h"

class Door : public StaticElement {
public:
	int next_map;//下一张地图
	int next_x;//人物出现在下一张地图的初始位置
	int next_y;//人物出现在下一张地图的初始位置

	Door(std::string data) {
		//读取数据...
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		width = str2int(datas[2]);
		height = str2int(datas[3]);
		next_map = str2int(datas[4]);
		next_x = str2int(datas[5]);
		next_y = str2int(datas[6]);
	}

	//因为ElementFactory,map无法相互调用
	//所以它会给GameMessageBox输出一个信息
	void run(Player &player, GameMessageBox &box) {
		if (!check(player.x, player.y))
			return;
		box.add("点击空格进入下一张地图", 30);
		if (box.element_message == (PLAYER | CHECK_TRUE)) {
			box.element_message = DOOR + next_map;
			player.x = next_x;
			player.y = next_y;
		}
			
			
	}
private:
	//使用c作为分隔符切割字符串s
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