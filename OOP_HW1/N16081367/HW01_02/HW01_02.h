// Object Oriented Programming 
// Homework#01_02 
// N16081367 ³¯«T§Ê

#ifndef HW01_02_H_
#define HW01_02_H_

#include <iostream>
#include <string>

using std::string;
using std::endl;

namespace MyGeometry
{
	struct Point
	{
		float x;
		float y;
		double Length();
		string CoutPoint();
	};
	Point* LoadPoint(const char* filename, unsigned int& nPoint);
	Point MinDistance(Point* arr, const unsigned int nPoint);
	void SortbyLength(Point* arr, const unsigned int nPoint);
	void Report(const char* filename, Point* arr, const unsigned int nPoint, Point min);
}

#endif