// Object Oriented Programming 
// Homework#01_02 
// N16081367 ���T��

#include "pch.h"
#include "HW01_02.h"

using namespace MyGeometry;

int main()
{
	unsigned int point_total = 0;
	Point* point_arr = LoadPoint("Point_HW1.txt", point_total);
	Point min_point = MinDistance(point_arr, point_total);
	SortbyLength(point_arr, point_total);
	Report("Output_HW1.txt", point_arr, point_total, min_point);
	std::cout << "���G�w��X���ɮ�Output_HW1.txt��" << endl;
	delete[] point_arr;
	return 0;
}