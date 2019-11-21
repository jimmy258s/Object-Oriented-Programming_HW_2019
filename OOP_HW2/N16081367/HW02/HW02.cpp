// Object Oriented Programming 
// Homework#02 
// N16081367 陳俊廷

#include "pch.h"
#include "HW02.h"

// 基底建構子，將點預設為(0, 0)
Point::Point()
{
	x = 0;
	y = 0;
}

// 兩個參數建構子
Point::Point(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

// 類別Point沒有建動態空間因此可使用預設解構子
Point::~Point()
{

}

// 設定資料值
void Point::Set_data(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

// Subscript operator，[0]為 x、[1]為 y
float Point::operator[](int i)const
{
	if (i == 0)
		return x;
	else if (i == 1)
		return y;
}

// 重載輸入導向運算子
std::istream& operator>>(std::istream& is, Point& p)
{
	is >> p.x >> p.y;
	return is;
}

// 重載輸出導向運算子
std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

// 用於讀檔的函式，引入檔案名稱及點座標數量的reference，回傳點座標陣列的地址
Point* load_file(const char* f, unsigned int& n)
{
	std::ifstream infile;
	infile.open(f); 

	string tmps_line, tmps_count;
	getline(infile, tmps_line);
	std::stringstream ss;
	tmps_count = tmps_line.substr(12, 13);
	ss.str("");
	ss.clear();
	ss << tmps_count;
	ss >> n;

	Point* arr = new Point[n];
	for (int i = 0; i < n; i++)
		infile >> arr[i];
	infile.close();

	return arr;
}

// 三個參數建構子
QuadtreeNode::QuadtreeNode(const Point& d, const Point& s_p, const float s) :data(&d), separate_point(s_p), size(s)
{
	for (int i = 0; i < 4; i++)
		nextNode[i] = nullptr;
}

// 複製建構子
QuadtreeNode::QuadtreeNode(const QuadtreeNode& qn) :data(qn.data), separate_point(qn.separate_point), size(qn.size)
{
	for (int i = 0; i < 4; i++)
	{
		if (qn.nextNode[i] != nullptr)
			nextNode[i] = new QuadtreeNode(*qn.nextNode[i]);
		else
			nextNode[i] = nullptr;
	}
}

// 解構子，若nextNode[i]有資料則釋放其動態空間
QuadtreeNode::~QuadtreeNode()
{
	for (int i = 0; i < 4; i++)
	{
		if (nextNode[i] != nullptr)
		{
			delete nextNode[i];
			nextNode[i] = nullptr;
		}
	}
}

// 將點座標傳入並插入四元樹中
bool QuadtreeNode::InsertPoint(const Point& p)
{
	if (&p == nullptr) // 若輸入點座標無資料則回傳false
		return false;

	int times;
	if (data == nullptr) // 若此節點無資料只需要執行一次，節點有資料的話要將輸入點座標跟原節點的資料點座標都往下插入
		times = 1;
	else
		times = 2;

	for (int i = 0; i < times; i++)
	{
		const Point* tmps;

		if (i == 0)
			tmps = &p; // 第一次將輸入點座標往下插入
		else
		{
			tmps = data; // 第二次將原節點的資料點座標往下插入
			data = nullptr; 
		}

		bool dx = ((*tmps)[0] > separate_point[0]);
		bool dy = ((*tmps)[1] > separate_point[1]);

		// 第一象限
		if (dx == true && dy == true)
		{
			if (nextNode[0] == nullptr) // 若下個第一象限節點無資料則插入新的四元樹節點
			{
				Point new_separate_point(separate_point[0] + size / 4, separate_point[1] + size / 4);
				nextNode[0] = new QuadtreeNode(*tmps, new_separate_point, size / 2);
			}
			else // 若下個第一象限節點有資料則遞迴
				nextNode[0]->InsertPoint(*tmps);
		}
		// 第二象限
		else if (dx == false && dy == true)
		{
			if (nextNode[1] == nullptr)
			{
				Point new_separate_point(separate_point[0] - size / 4, separate_point[1] + size / 4);
				nextNode[1] = new QuadtreeNode(*tmps, new_separate_point, size / 2);
			}
			else
				nextNode[1]->InsertPoint(*tmps);
		}
		// 第三象限
		else if (dx == false && dy == false)
		{
			if (nextNode[2] == nullptr)
			{
				Point new_separate_point(separate_point[0] - size / 4, separate_point[1] - size / 4);
				nextNode[2] = new QuadtreeNode(*tmps, new_separate_point, size / 2);
			}
			else
				nextNode[2]->InsertPoint(*tmps);
		}
		// 第四象限
		else if (dx == true && dy == false)
		{
			if (nextNode[3] == nullptr)
			{
				Point new_separate_point(separate_point[0] + size / 4, separate_point[1] - size / 4);
				nextNode[3] = new QuadtreeNode(*tmps, new_separate_point, size / 2);
			}
			else
				nextNode[3]->InsertPoint(*tmps);
		}
		else 
			return false;
	}
	return true;
}

// 將點傳入，尋找傳入點所屬的子節點，並將已屬於該子節點的點回傳
const Point* QuadtreeNode::FindClosestPoint(const Point& p)const
{
	if (data == nullptr) // 如果該節點無資料表示要繼續往下找或點座標所屬子節點無資料
	{
		bool dx = (p[0] > separate_point[0]);
		bool dy = (p[1] > separate_point[1]);

		// 第一象限
		if (dx == true && dy == true)
		{
			if (nextNode[0] == nullptr) // 若此節點下無第一象限節點，表示此節點已為leaf，點座標所屬子節點無資料
				return nullptr;
			else
				return nextNode[0]->FindClosestPoint(p); // 若此節點下還有分支則遞迴
		}
		// 第二象限
		else if (dx == false && dy == true)
		{
			if (nextNode[1] == nullptr)
				return nullptr;
			else
				return nextNode[1]->FindClosestPoint(p);
		}
		// 第三象限
		else if (dx == false && dy == false)
		{
			if (nextNode[2] == nullptr)
				return nullptr;
			else
				return nextNode[2]->FindClosestPoint(p);
		}
		// 第四象限
		else if (dx == true && dy == false)
		{
			if (nextNode[3] == nullptr)
				return nullptr;
			else
				return nextNode[3]->FindClosestPoint(p);
		}
		else
			return nullptr;
	}
	else // 若此節點有資料則回傳
		return data;
}