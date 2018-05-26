#pragma once

#include "boss.h"
#include "DataDealer.h"

#define ASRIEL_START_MODE 0x0001
#define ASRIEL_TALK_MODE 0x0002
#define ASRIEL_END_MODE 0x0004

class Asriel : public Boss {
public:
	int count = 0;//��¼��ǰ����
	Asriel(std::string data) {
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		CImage img;
		img.Load("img\\asriel\\asriel.png");
		pic.push_back(img.Detach());
		img.Destroy();
		mode = ASRIEL_START_MODE;
	}
	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		int index;
		switch (mode) {
		case ASRIEL_START_MODE:
			index = 0;
			break;
		default:
			index = 0;
			break;
		}
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[index]);//��ͼƬ�ŵ�HDC��  
		TransparentBlt(g_hdc, x, y, 70, 115, mmhdc, 0, 0, 70, 115, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  	
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	void run(Player &player, GameMessageBox &box) {
		switch (count) {
		case 30:
			box.add("���ร������������������Ϣ!", 150);
			break;
		case 200:
			box.add("��ֱ̫���˸������������Ϸ�����������������ѽ!", 150);
			break;
		case 360:
			box.add("Ϊ����ףһ�£���΢������˱���~", 150);
			break;
		case 520:
			box.add("[����ո�ʹ�ú˱�]", 50);
			break;
		case 680:
			box.add("Ŷ����Ǹ����β���Ҫ������������!", 150);
			break;
		case 840:
			box.add("������ϲ��!����Ի�ó����EXP����Ϊ����Ĺ��ﶼ��������~", 150);
			break;
		case 1000:
			box.add("������������������", 150);
			break;
		case 1240:
			box.add("Asriel:�����Sans˵�Ļ�����Ǵ������ѵ�����", 150);
			break;
		case 1400:
			box.add("Asriel:���������Ѿ������˺ܾ��ˣ��Ѿ��������з�����......", 150);
			break;
		case 1560:
			box.add("Asriel:Sans˵��������Ѿ������ˣ�������Ѿ����˺����صĵز��ˡ�", 150);
			break;
		case 1720:
			box.add("Asriel:���������޷���صľ��档", 150);
			break;
		case 1880:
			box.add("Asriel:SansҪ�Ұ�SAVE���㡣", 150);
			break;
		case 2040:
			box.add("Asriel:��˵��\"�浵���Ѿ�������ˣ�SAVE�Ѿ��޷������浵�ˣ�����������SAVE\"��", 150);
			break;
		case 2200:
			box.add("Asriel:���Sʹ��SAVE��", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2360:
			box.add("Asriel:�Ҳ���Sans����˼��������˵��һ�������ס�", 150);
			mode = ASRIEL_END_MODE;
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2520:
			box.add("�������ģ����SAVE������޷�ӵ�о���ֵ�ˣ�", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2680:
			box.add("�ҰѺ˱��İ�ť���㣡������Լ����鵽һ˲��ɱ�����й���Ŀ�У�", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2800:
			box.add("[����ո�ʹ�ú˱�][����ո�ʹ�ú˱�][����ո�ʹ�ú˱�]", 100);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2900:
			box.add("Asriel:ϣ��������������ǵļ�԰��", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 3000:
			box.add("[����ո�ʹ�ú˱�][����ո�ʹ�ú˱�][����ո�ʹ�ú˱�]", 1000);
			box.element_message = END | CHECK_EMPTY;
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
	~Asriel() {
		for (HBITMAP hp : pic)
			DeleteObject(hp);
	}
};