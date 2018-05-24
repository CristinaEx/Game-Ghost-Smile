#pragma once
#include <string>
#include "wall.h"
#include "door.h"
#include "map"
#include "Comment.h"
#include "dog.h"
#include "Sans.h"
#include "papyrus.h"
#include "undyne.h"

//游戏内动态或静态成员元素工厂
//通过getClass获取每个元素的实例

class ElementFactory {
public:
	static Element* getClass(std::string class_name,std::string data) {
		if (class_name.compare("Wall") == 0) {
			return new Wall(data);
		}
		else if (class_name.compare("Door") == 0) {
			return new Door(data);
		}
		else if (class_name.compare("Comment") == 0) {
			return new Comment(data);
		}
		else if (class_name.compare("Dog") == 0) {
			return new Dog(data);
		}
		else if (class_name.compare("Sans") == 0) {
			return new Sans(data);
		}
		else if (class_name.compare("Papyrus") == 0) {
			return new Papyrus(data);
		}
		else if (class_name.compare("Undyne") == 0) {
			return new Undyne(data);
		}
		//...
	}
private:
	//使用c作为分隔符切割字符串s
	static std::vector<std::string> splitString(const std::string& s, const char c)
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
};