// Object Oriented Programming 
// Homework#02 
// N16081367 ���T��

#ifndef HW02_H_
#define HW02_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Point
{
private:
	float x;
	float y;
public:
	Point();
	Point(float, float);
	~Point();
	void Set_data(float, float);
	float operator[](int i)const;
	friend std::istream& operator>>(std::istream&, Point&);
	friend std::ostream& operator<<(std::ostream&, const Point&);
};

Point* load_file(const char* filename, unsigned int& n);

class QuadtreeNode
{
private:
	const Point* data; 
	QuadtreeNode* nextNode[4]; 
	const Point separate_point; 
	const float size; 
public:
	QuadtreeNode() = delete; // �򩳫غc�l�A�����O���ϥΡA�ҥH�L�k�Q�I�s
	QuadtreeNode(const Point&, const Point&, const float); 
	QuadtreeNode(const QuadtreeNode&); 
	~QuadtreeNode(); 
	QuadtreeNode& operator=(const QuadtreeNode&) = delete; // ���w�B��l�A�����O���ϥΡA�ҥH�L�k�Q�I�s
	bool InsertPoint(const Point&); 
	const Point* FindClosestPoint(const Point&)const; 
};

#endif
