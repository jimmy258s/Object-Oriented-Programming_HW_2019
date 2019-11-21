// Object Oriented Programming 
// Homework#01_01 
// N16081367 陳俊廷

#include "pch.h"
#include <iostream>
#include <ctime>

using namespace std;

const double D_MAX = 100.0;
const double D_MIN = 0.0;
const short S_MAX = 100;
const short S_MIN =  0;

template <class T>
T max_value(T* a, int n);
const char* max_value(const char** a, int n);

int main()
{
	srand(time(NULL));

     // 產生一維動態陣列s_arr內值為short; 範圍0~100
	short* s_arr = new short[6];
	for (int i = 0; i < 6; i++)
		s_arr[i] = (S_MAX - S_MIN) * rand() / (RAND_MAX + 1) + S_MIN;

	// 產生一維動態陣列d_arr內值為double; 範圍0.0~100.0
	double* d_arr = new double[8];
	for (int i = 0; i < 8; i++)
		d_arr[i] = (D_MAX - D_MIN) * rand() / (RAND_MAX + 1.0) + D_MIN;

	// 尋找兩個陣列最大值分別為short_max, double_max
	short short_max = max_value(s_arr, 6);
	double double_max = max_value(d_arr, 8);

	cout << "short值陣列最大值為: " << short_max << "\ndouble值陣列最大值為: " << double_max << endl;

	// 產生6個char指標的陣列c_arr
	const char* c_arr[6] = {"National", "Cheng", "Kung", "University", "Mechanical", "Engineering"};
	// 尋找c_arr最長字串為char_max
	const char* char_max = max_value(c_arr, 6);

	cout << "char指標的陣列最長字串為: " << char_max << endl;

	delete[] s_arr;
	delete[] d_arr;

	cin.get();
	return 0;
}

// 取陣列中最大值
template <class T>
T max_value(T* a, int n)
{
	T max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

// pmax指向最長字串; max為最長字串長度 
// 字串長度大於目前最長長度才會被取其地址; 所以會回傳第一個最長字串的地址
const char* max_value(const char** a, int n)
{
	const char* pmax = NULL;
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		int length = (int)strlen(a[i]);
		if (length > max)
		{
			pmax = a[i];
			max = length;
		}
	}
	return pmax;
}



