#pragma once
#include "boss.h"
#include <math.h>

#define DOG_ATTACK_MODE 0x2000
#define DOG_TIRED_MODE 0x3000
#define DOG_END_MODE 0x4000

class Dog : public Boss {
public:
	//����ģʽ�����ĵ�
	int attack_x;
	int attack_y;
	int count = 0;//��¼��ǰ����
	int sleep = 0;//�������
	Dog(std::string data) {
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		mode = START_MODE | LEFT;
		CImage img;
		img.Load("img\\dog\\right_dog.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\dog\\left_dog.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\dog\\pre_dog.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\dog\\tired_dog.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
	}

	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		int index;
		switch (mode & 0xf000) {
		case START_MODE:
			index = 2;
			break;
		case DOG_TIRED_MODE:
			index = 3;
			break;
		case DOG_END_MODE:
			index = 3;
			break;
		default:
			switch (mode & 0x000f) {
			case RIGHT:
				index = 0;
				break;
			case LEFT:
				index = 1;
				break;
			default:
				index = 0;
				break;
			}
		}
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[index]);//��ͼƬ�ŵ�HDC��  
		TransparentBlt(g_hdc, x, y, 50, 50, mmhdc, 0, 0, 50, 50, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  	
		SelectObject(g_hdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}

	void run(Player &player, GameMessageBox &box) {
		switch (count) {
		case 40:
			box.add("�ݵ��Ϻ�����һֻ�ɰ���С����", 30);
			break;
		case 80:
			box.add("����������һֻ���õ�С����!", 30);
			break;
		case 120:
			box.add("������ע�⵽����!", 30);
			break;
		case 160:
			box.add("��������...����", 30);
			break;
		case 200:
			mode = (mode & 0x0fff) | NORMAL_MODE;
			break;
		case 1000:
			box.add("���������е����ˡ�", 30);
			break;
		case 1300:
			box.add("���������ۻ��ˡ�", 30);
			mode = (mode & 0x0fff) | DOG_TIRED_MODE;
			box.element_message = CHECK_EMPTY;
			break;
		case 1330:
			box.add("������ۻ���ʱ����������!��", 30);
			break;
		case 1360:
			box.add("(�߽������ո�)", 900);
			break;
		case 2160:
			count = 120;
			break;
		default:
			break;
		}
		switch (mode & 0xf000) {
		case START_MODE:
			break;
		case NORMAL_MODE:
			if (x > player.x)mode = (mode & 0xfff0) | LEFT;
			else mode = (mode & 0xfff0) | RIGHT;

			if (sleep < 0 && pow(x - player.x,2) + pow(y - player.y,2) <= 22500) {
				mode = (mode & 0x0fff) | DOG_ATTACK_MODE;
				attack_x = player.x;
				attack_y = player.y;
				sleep = 30;//����ģʽ���30֡
			}
			else {
				if (abs(x - player.x) > abs(y - player.y))
					x += (x > player.x ? -5 : 5);
				else
					y += (y > player.y ? -5 : 5);
				sleep--;
			}
			break;
		case DOG_ATTACK_MODE:
			if (pow(x - player.x, 2) + pow(y - player.y, 2) <= 1600) {
				player.hp_now -= 1;
			}
			if(abs(x - attack_x) <= 20 && abs(y - attack_y) <= 20)
				mode = (mode & 0x0fff) | NORMAL_MODE;
			else {
				x += (x > attack_x ? -20 : 20);
				y += (y > attack_y ? -20 : 20);
			}
			break;
		case DOG_TIRED_MODE:
			if (pow(x - player.x, 2) + pow(y - player.y, 2) <= 1600 && (box.element_message == (PLAYER | CHECK_TRUE))) {
				player.exp_now += 20;
				box.add("Ц����ͷ��", 30);
				mode = (mode & 0x0fff) | DOG_END_MODE;
			}
			break;
		case DOG_END_MODE:
			break;
		default:
			break;
		}
		count++;
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
	~Dog() {
		for (HBITMAP hp : pic)
			DeleteObject(hp);
	}
};