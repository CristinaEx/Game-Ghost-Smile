#pragma once
#include <vector>
#include <string>
#include <io.h>
#include <iostream>
#include <fstream>
#define DATA_PATH "data\\"


class DataDealer {
	//�����ļ������Ĺ�����

public:
	//��ո�·���µ������ļ�
	static void clearPath(std::string path) {
		std::vector<std::string> files; 
		getFiles(path, files);
		for (std::string file_name : files)
			remove(file_name.c_str());
	}
	static void getFiles(std::string path, std::vector<std::string>& files)
		 {
		    //�ļ����  
		    long   hFile = 0;
		    //�ļ���Ϣ  
		    struct _finddata_t fileinfo;
		    std::string p;
		    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
			    {
		         do
			        {
			            //�����Ŀ¼,����֮  
			            //�������,�����б�  
			        if ((fileinfo.attrib &  _A_SUBDIR))
			           {
			               if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
			                     getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			            }
			        else
			           {
			                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			            }
			     }while (_findnext(hFile, &fileinfo) == 0);
					_findclose(hFile);
			}
		 }
	//�����ļ��Ƿ����
	static bool checkFileExist(std::string file_path_name) {
		std::fstream _file;
		_file.open(file_path_name, std::ios::in);
		if (!_file)
			return false;
		else
			return true;
	}
	static void writeFile(std::string file_path_name , std::string data) {
		std::ofstream out;
		out.open(file_path_name, std::ios::out);  //��д��ķ�ʽ���ļ���û�еĻ��ʹ������ļ���
		if (!out.is_open())
			return;
		out << data;
		out.close();
	}
	//��ȡ�ļ���һ��
	//����һ��Ϊ���򷵻ؿ��ַ���
	static std::string readFileFirstLine(std::string file_path_name) {
		std::ifstream in(file_path_name, std::ios::in);
		std::string data;
		if (!in.eof())
			getline(in, data);
		else
			data = "";
		in.close();
		return data;
	}
};