#pragma once
#include<windows.h>
#include <mmsystem.h>
#include<dsound.h>
#include<string>
#include <sstream>
#pragma comment(lib, "WINMM.LIB")
class MusicPlayer {
public:
	//��ǰ���ŵ����ֵ�����
	std::string music_name = "";

	//��������
	//file_path_name Ϊ���ֵ�·��+�ļ���
	//command������ո�
    void play(std::string file_path_name,std::string command = "")
	{
		this->music_name = file_path_name;
		mciSendString(TEXT(("open " + this->music_name).c_str()), NULL, 0, NULL);
		mciSendString(TEXT(("play " + this->music_name + command).c_str()), NULL, 0, NULL);
	}
	//�ر�����
	void close() {
		if (!music_name.empty()) {
			mciSendString(TEXT(("stop " + this->music_name).c_str()), NULL, 0, NULL);
			mciSendString(TEXT(("close " + this->music_name).c_str()), NULL, 0, NULL);
		}
		this->music_name.clear();
	}
	//��������
	void setVolume(int volume) {
		mciSendString(TEXT(("setaudio movie volume to " + this->int2str(volume)).c_str()), NULL, 0, NULL);
	}
	//��ȡ������С
	int getVolume() {
		char V[5];
		mciSendString(TEXT(std::string("status movie volume").c_str()), V, 5, NULL);
		int result = 0;
		int mod = 0;
		for (int index = 4; index >= 0; index--) {
			if (V[index] == '\0')mod = 1;
			result += (V[index] - 48) * mod;
			mod *= 10;
		}
		return result;
	}
private:
	//���ַ���תΪwchar_t
	wchar_t *multiByteToWideChar(std::string& str)
	{
	    char * pCStrKey = const_cast<char*>(str.c_str());
		//��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
		int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
		wchar_t *pWCStrKey = new wchar_t[pSize];
		//�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
		MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
		return pWCStrKey;
	}

	//�����ζ�Ӧ����תΪ�ַ���
	std::string int2str(const int &int_temp)
	{
		std::stringstream stream;
		stream << int_temp;
		return stream.str();   //�˴�Ҳ������ stream>>string_temp  
	}
};
