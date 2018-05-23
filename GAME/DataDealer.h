#pragma once
#include <vector>
#include <string>
#include <io.h>
#include <iostream>
#include <fstream>
#define DATA_PATH "data\\"


class DataDealer {
	//关于文件操作的工具类

public:
	//清空该路径下的所有文件
	static void clearPath(std::string path) {
		std::vector<std::string> files; 
		getFiles(path, files);
		for (std::string file_name : files)
			remove(file_name.c_str());
	}
	static void getFiles(std::string path, std::vector<std::string>& files)
		 {
		    //文件句柄  
		    long   hFile = 0;
		    //文件信息  
		    struct _finddata_t fileinfo;
		    std::string p;
		    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
			    {
		         do
			        {
			            //如果是目录,迭代之  
			            //如果不是,加入列表  
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
	//返回文件是否存在
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
		out.open(file_path_name, std::ios::out);  //以写入的方式打开文件，没有的话就创建该文件。
		if (!out.is_open())
			return;
		out << data;
		out.close();
	}
	//读取文件第一行
	//若第一行为空则返回空字符串
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