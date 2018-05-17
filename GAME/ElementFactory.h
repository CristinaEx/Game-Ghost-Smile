#pragma once
#include<string>
#include"wall.h"
#include<vector>

//��Ϸ�ڶ�̬��̬��ԱԪ�ع���
//ͨ��getClass��ȡÿ��Ԫ�ص�ʵ��
class ElementFactory {
public:
	static Element* getClass(std::string class_name,std::string data) {
		if (class_name.compare("Wall") == 0) {
			return new Wall(data);
		}
		//...
	}
private:
	//ʹ��c��Ϊ�ָ����и��ַ���s
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