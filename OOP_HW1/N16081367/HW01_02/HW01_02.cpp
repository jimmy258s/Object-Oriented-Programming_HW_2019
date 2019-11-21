// Object Oriented Programming 
// Homework#01_02 
// N16081367 陳俊廷

#include "pch.h"
#include "HW01_02.h"
#include <cmath>
#include <sstream>
#include <fstream>

namespace MyGeometry
{
	// 回傳座標到原點距離
	double Point::Length()
	{
		return sqrt(pow(x, 2) + pow(y, 2));  
	}

	// 回傳string格式的字串(x, y)
	string Point::CoutPoint()
	{
		string str_tmps = "(, )";
		std::stringstream ss;
		ss << x;
		string str_xy;
		ss >> str_xy;
		str_tmps.insert(1, str_xy);
		ss.str("");
		ss.clear();
		ss << y;
		ss >> str_xy;
		str_tmps.insert(str_tmps.find(',', 0) + 2, str_xy);
		return str_tmps;
	}

	// 以動態陣列儲存文字檔內的座標後回傳陣列地址
	Point* LoadPoint(const char* filename, unsigned int& nPoint)
	{
		// 計算出共幾個點給reference
		std::ifstream infile;
		infile.open(filename);  
		string tmps;
		while (getline(infile, tmps)) 
		{
			nPoint++;
		}
		infile.close();

		infile.open(filename);
		Point* arr = new Point[nPoint];
		string str_x, str_y;
		std::stringstream ss;
		for (int i = 0; i < nPoint; i++)
		{
			getline(infile, tmps);
			str_x = tmps.substr(0, tmps.find(' ', 0));
			str_y = tmps.substr(tmps.find(' ', 0) + 1, tmps.length());
			ss.str("");
			ss.clear();
			ss << str_x;
			ss >> arr[i].x;
			ss.str("");
			ss.clear();
			ss << str_y;
			ss >> arr[i].y;
		}
		infile.close();
		return arr;
	}

	// 回傳最接近 x+y=1 的點
	Point MinDistance(Point* arr, const unsigned int nPoint)
	{
		Point pmin = arr[0];
		float min = abs(arr[0].x + arr[0].y - 1);
		for (int i = 1; i < nPoint; i++)
		{
			if (abs(arr[i].x + arr[i].y - 1) < min)
			{
				pmin = arr[i];
				min = abs(arr[i].x + arr[i].y - 1);
			}
		}
		return pmin;
	}

	// 以selection sort將動態陣列依各點與原點距離由大到小排序
	void SortbyLength(Point* arr, const unsigned int nPoint)
	{
		for (int i = 0; i < nPoint - 1; i++)
		{
			unsigned int max = i;
			for (int j = i + 1; j < nPoint; j++)
			{
				if (arr[j].Length() > arr[max].Length())
					max = j;
			}
			std::swap(arr[i], arr[max]);
		}
	}

	// 將結果寫入文字檔"Output_HW1.txt"中
	void Report(const char* filename, Point* arr, const unsigned int nPoint, Point min)
	{
		std::ofstream outfile;
		outfile.open(filename);
		outfile << "物件導向程式設計第一次作業" << endl;
		outfile << "N16081367 陳俊廷" << endl;
		outfile << "點數目 : " << nPoint << endl;
		outfile << "最接近 x+y=1 的點 : " << min.CoutPoint() << endl;
		outfile << "與原點距離最近的點 : " << arr[nPoint - 1].CoutPoint() << "、距離為 : " << arr[nPoint - 1].Length() << endl;
		outfile.close();
	}
}

