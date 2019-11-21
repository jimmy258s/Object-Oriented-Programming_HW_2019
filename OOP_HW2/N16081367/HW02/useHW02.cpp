// Object Oriented Programming 
// Homework#02 
// N16081367 陳俊廷

#include "pch.h"
#include "HW02.h"

int main()
{
	const char* filename = "Point_HW2.txt";
	unsigned int point_count; // 檔案中的點座標數量

	Point* point_arr = load_file(filename, point_count); // 將檔案中的點座標讀取到point_arr陣列中

	const Point* first_point = &point_arr[0]; // 設四元樹第一個引入的點座標為point_arr[0]
	const Point first_separate_point; // 設第一個分割中心為(0, 0)
	const float original_size = 200; // 設初始分割邊界長度為200

	QuadtreeNode tree(*first_point, first_separate_point, original_size); // 宣告四元樹tree

	for (int i = 1; i < point_count; i++) // 將point_arr陣列依序插入到tree中
		tree.InsertPoint(point_arr[i]); 
 
	QuadtreeNode copy_tree(tree); // 以複製建構子複製四元樹tree產生copy_tree

	Point input_point; 
	const Point* closest_point;
	const Point* copy_closest_point;

	cout << "請輸入一點座標，例如:10 10，x與y最大與最小值為+/-100: " << endl;
	while (cin >> input_point)
	{
		if (input_point[0] > 100 || input_point[0] < -100 || input_point[1] > 100 || input_point[1] < -100) // 如果輸入點座標超過邊界範圍則退出輸入
			break;

		closest_point = tree.FindClosestPoint(input_point);
		if (closest_point != nullptr)
			cout << "輸入點所屬子節點內的點座標為: " << std::fixed << std::setprecision(3) << *closest_point << endl;
		else
			cout << "輸入點所屬子節點內找不到點座標" << endl;

		copy_closest_point = copy_tree.FindClosestPoint(input_point);
		if (copy_closest_point != nullptr)
			cout << "輸入點在複製四元樹所屬子節點內的點座標為: " << std::fixed << std::setprecision(3) << *copy_closest_point << endl;
		else
			cout << "輸入點在複製四元樹所屬子節點內找不到點座標" << endl;

		cout << "請再次輸入一點座標: " << endl;
	}
	cout << "輸入點座標超過範圍，或為無效輸入，結束程序..." << endl;
	cout << "-------------------- Question --------------------" << endl;
	cout << "(1) 類別Point: " << endl;
	cout << "\t\"基底建構子\"和\"解構子\"可以直接使用編譯器預設的版本，" << endl;
	cout << "\t因為Point物件在產生時不需要產生動態空間，在解構時不用釋放動態空間所以可以直接使用編譯器預設的版本。" << endl;
	cout << "(2) 類別QoadtreeNode: " << endl;
	cout << "\t沒有成員函式可以直接使用編譯器預設的版本，" << endl;
	cout << "\tQuadtreeNode的基底建構子要調整為無法被呼叫，並且此物件在解構時需要釋放動態空間。" << endl;

	delete[] point_arr;

	cin.get();
	return 0;
}