// Object Oriented Programming 
// Homework#02 
// N16081367 ���T��

#include "pch.h"
#include "HW02.h"

int main()
{
	const char* filename = "Point_HW2.txt";
	unsigned int point_count; // �ɮפ����I�y�мƶq

	Point* point_arr = load_file(filename, point_count); // �N�ɮפ����I�y��Ū����point_arr�}�C��

	const Point* first_point = &point_arr[0]; // �]�|����Ĥ@�ӤޤJ���I�y�Ь�point_arr[0]
	const Point first_separate_point; // �]�Ĥ@�Ӥ��Τ��߬�(0, 0)
	const float original_size = 200; // �]��l������ɪ��׬�200

	QuadtreeNode tree(*first_point, first_separate_point, original_size); // �ŧi�|����tree

	for (int i = 1; i < point_count; i++) // �Npoint_arr�}�C�̧Ǵ��J��tree��
		tree.InsertPoint(point_arr[i]); 
 
	QuadtreeNode copy_tree(tree); // �H�ƻs�غc�l�ƻs�|����tree����copy_tree

	Point input_point; 
	const Point* closest_point;
	const Point* copy_closest_point;

	cout << "�п�J�@�I�y�СA�Ҧp:10 10�Ax�Py�̤j�P�̤p�Ȭ�+/-100: " << endl;
	while (cin >> input_point)
	{
		if (input_point[0] > 100 || input_point[0] < -100 || input_point[1] > 100 || input_point[1] < -100) // �p�G��J�I�y�жW�L��ɽd��h�h�X��J
			break;

		closest_point = tree.FindClosestPoint(input_point);
		if (closest_point != nullptr)
			cout << "��J�I���ݤl�`�I�����I�y�Ь�: " << std::fixed << std::setprecision(3) << *closest_point << endl;
		else
			cout << "��J�I���ݤl�`�I���䤣���I�y��" << endl;

		copy_closest_point = copy_tree.FindClosestPoint(input_point);
		if (copy_closest_point != nullptr)
			cout << "��J�I�b�ƻs�|������ݤl�`�I�����I�y�Ь�: " << std::fixed << std::setprecision(3) << *copy_closest_point << endl;
		else
			cout << "��J�I�b�ƻs�|������ݤl�`�I���䤣���I�y��" << endl;

		cout << "�ЦA����J�@�I�y��: " << endl;
	}
	cout << "��J�I�y�жW�L�d��A�ά��L�Ŀ�J�A�����{��..." << endl;
	cout << "-------------------- Question --------------------" << endl;
	cout << "(1) ���OPoint: " << endl;
	cout << "\t\"�򩳫غc�l\"�M\"�Ѻc�l\"�i�H�����ϥνsĶ���w�]�������A" << endl;
	cout << "\t�]��Point����b���ͮɤ��ݭn���ͰʺA�Ŷ��A�b�Ѻc�ɤ�������ʺA�Ŷ��ҥH�i�H�����ϥνsĶ���w�]�������C" << endl;
	cout << "(2) ���OQoadtreeNode: " << endl;
	cout << "\t�S�������禡�i�H�����ϥνsĶ���w�]�������A" << endl;
	cout << "\tQuadtreeNode���򩳫غc�l�n�վ㬰�L�k�Q�I�s�A�åB������b�Ѻc�ɻݭn����ʺA�Ŷ��C" << endl;

	delete[] point_arr;

	cin.get();
	return 0;
}