#include "../src/BTree.cpp"
#include <iostream>
#include <string.h>
using namespace std;

//string actual_output = "";

string PrintArray(int *A, int size)
{
	string actual_output = "";

	size--;
	//cout << "[ ";
	actual_output.append("[ ");

	for (int i = 0; i < size; i++)
	{
		//cout << A[i] << ", ";
		actual_output.append(to_string(A[i]));
		actual_output.append(", ");
	}

	//cout << A[size];
	actual_output.append(to_string(A[size]));

	//cout << " ]";
	actual_output.append(" ]");

	return actual_output;
}

string PrintTree(BTreeNode *node, string indent, bool last)
{
	string actual_output = "";

	//cout << indent << "+- ";
	actual_output.append(indent);
	actual_output.append("+- ");

	actual_output.append(PrintArray(node->Data, node->CurrentNodes));
	//cout<<"IsLeafNode: "<<node->IsLeafNode<<"\n";
	//cout<<"\n";
	actual_output.append("\n");

	indent.append(last ? "   " : "|  ");

	for (int i = 0, c = node->IsLeafNode ? 0 : node->CurrentNodes + 1; i < c; i++)
	{
		string x = PrintTree(node->Children[i], indent, i == c - 1);

		actual_output.append(x);
	}

	return actual_output;
}

void testcase_1()
{
	BTree tree;

	int input[] = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6};

	string actual_output = "";

	string expected_output = "+- [ 3, 5, 8 ]\n   +- [ 1, 2 ]\n   +- [ 4 ]\n   +- [ 6, 7 ]\n   +- [ 9, 10 ]\n";

	for (int i = 0; i < 10; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 1 Passed";
	else
		cout << "\n\n Testcase 1 Failed";
}

void testcase_2()
{
	BTree tree;

	int input[] = {6, 15, 4, 12, 17, 22, 2, 3, 5, 11, 14, 16, 20, 24};

	string actual_output = "";

	string expected_output = "+- [ 6 ]\n   +- [ 3 ]\n   |  +- [ 2 ]\n   |  +- [ 4, 5 ]\n   +- [ 15, 17 ]\n      +- [ 11, 12, 14 ]\n      +- [ 16 ]\n      +- [ 20, 22, 24 ]\n";

	for (int i = 0; i < 14; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 2 Passed";
	else
		cout << "\n\n Testcase 2 Failed";
}

void testcase_3()
{
	BTree tree;

	int input[] = {50, 35, 70, 27, 30, 40, 47, 55, 60, 85, 90};

	string actual_output = "";

	string expected_output = "+- [ 47 ]\n   +- [ 35 ]\n   |  +- [ 27, 30 ]\n   |  +- [ 40 ]\n   +- [ 55, 70 ]\n      +- [ 50 ]\n      +- [ 60 ]\n      +- [ 85, 90 ]\n";

	for (int i = 0; i < 11; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 3 Passed";
	else
		cout << "\n\n Testcase 3 Failed";
}

void testcase_4()
{
	BTree tree;

	int input[] = {12, 45, 76, 88, 4, 568, 11, 23, 46, 98, 9, 44, 32, 67, 24, 56, 22, 34, 78, 99, 234, 654, 456, 555, 457, 124, 986, 459, 239, 121, 100, 444, 458, 771, 40, 208, 183, 888, 199, 200};

	string actual_output = "";

	string expected_output = "+- [ 45 ]\n   +- [ 23 ]\n   |  +- [ 11 ]\n   |  |  +- [ 4, 9 ]\n   |  |  +- [ 12, 22 ]\n   |  +- [ 32 ]\n   |     +- [ 24 ]\n   |     +- [ 34, 40, 44 ]\n   +- [ 88, 124, 456 ]\n      +- [ 76 ]\n      |  +- [ 46, 56, 67 ]\n      |  +- [ 78 ]\n      +- [ 99 ]\n      |  +- [ 98 ]\n      |  +- [ 100, 121 ]\n      +- [ 199, 234 ]\n      |  +- [ 183 ]\n      |  +- [ 200, 208 ]\n      |  +- [ 239, 444 ]\n      +- [ 555, 654 ]\n         +- [ 457, 458, 459 ]\n         +- [ 568 ]\n         +- [ 771, 888, 986 ]\n";

	for (int i = 0; i < 40; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 4 Passed";
	else
		cout << "\n\n Testcase 4 Failed";
}

void testcase_5()
{
	BTree tree;

	int input[] = {42, 92, 84, 66, 42, 11};

	int flag = 0;

	for (int i = 0; i < 6; i++)
	{
		int return_value = tree.Insert_BottomUp(input[i]);

		if (return_value == false)
		{
			flag = 1;
			break;
		}

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";
		PrintTree(tree.getRoot(), "", true);
	}

	if (flag == 1)
		cout << "\n\n Testcase 5 Passed";
	else
		cout << "\n\n Testcase 5 Failed";
}

void testcase_6()
{
	BTree tree;

	int input[] = {50, 35, 70, 27, 30, 40, 47, 55, 60, 85, 90};

	string actual_output = "";

	string expected_output = "+- [ 47 ]\n   +- [ 35 ]\n   |  +- [ 27, 30 ]\n   |  +- [ 40 ]\n   +- [ 55, 85 ]\n      +- [ 50 ]\n      +- [ 70 ]\n      +- [ 90 ]\n";

	for (int i = 0; i < 11; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	//cout<<"\n\nDelete Element: 60\n Printing Tree\n";

	tree.Delete_BottomUp(60);

	actual_output = PrintTree(tree.getRoot(), "", true);

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 6 Passed";
	else
		cout << "\n\n Testcase 6 Failed";
}

void testcase_7()
{
	BTree tree;

	int input[] = {6, 15, 4, 12, 17, 22, 2, 3, 5, 11, 14, 16, 20, 24};

	string actual_output = "";

	string expected_output = "+- [ 6 ]\n   +- [ 3 ]\n   |  +- [ 2 ]\n   |  +- [ 4, 5 ]\n   +- [ 14, 17 ]\n      +- [ 11, 12 ]\n      +- [ 15 ]\n      +- [ 20, 22, 24 ]\n";

	for (int i = 0; i < 14; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	//cout<<"\n\nDelete Element: 16\n Printing Tree\n";

	tree.Delete_BottomUp(16);

	actual_output = PrintTree(tree.getRoot(), "", true);

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 7 Passed";
	else
		cout << "\n\n Testcase 7 Failed";
}

void testcase_8()
{
	BTree tree;

	int input[] = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6};

	string actual_output = "";

	string expected_output = "+- [ 3, 5, 8 ]\n   +- [ 1, 2 ]\n   +- [ 4 ]\n   +- [ 6, 7 ]\n   +- [ 9, 10 ]\n";

	for (int i = 0; i < 10; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	//cout<<"\n\nDelete Element: 24\n Printing Tree\n";

	bool returnvalue = tree.Delete_BottomUp(24);

	if (returnvalue == false)
		cout << "\n\n Testcase 8 Passed";
	else
		cout << "\n\n Testcase 8 Failed";
}

void testcase_9()
{
	BTree tree;

	int input[] = {6, 15, 4, 12, 17, 22, 2, 3, 5, 11, 14, 16, 20, 24};

	string actual_output = "";

	string expected_output = "+- [ 5 ]\n   +- [ 3 ]\n   |  +- [ 2 ]\n   |  +- [ 4 ]\n   +- [ 15, 17 ]\n      +- [ 11, 12, 14 ]\n      +- [ 16 ]\n      +- [ 20, 22, 24 ]\n";

	for (int i = 0; i < 14; i++)
	{
		tree.Insert_BottomUp(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	//cout<<"\n\nDelete Element: 6\n Printing Tree\n";

	tree.Delete_BottomUp(6);

	actual_output = PrintTree(tree.getRoot(), "", true);

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 9 Passed";
	else
		cout << "\n\n Testcase 9 Failed";
}

void testcase_11()
{
	BTree tree;

	int input[] = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6};

	string actual_output = "";

	string expected_output = "+- [ 5 ]\n   +- [ 3 ]\n   |  +- [ 1, 2 ]\n   |  +- [ 4 ]\n   +- [ 9 ]\n      +- [ 6, 7, 8 ]\n      +- [ 10 ]\n";

	for (int i = 0; i < 10; i++)
	{
		tree.Insert_TopDown(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 11 Passed" << endl;
	else
		cout << "\n\n Testcase 11 Failed" << endl;
}

void testcase_12()
{
	BTree tree;

	int input[] = {10, 30, 60, 20, 50, 44, 76, 80, 15, 99, 100, 25};

	string actual_output = "";

	string expected_output = "+- [ 50 ]\n   +- [ 15, 30 ]\n   |  +- [ 10 ]\n   |  +- [ 20, 25 ]\n   |  +- [ 44 ]\n   +- [ 76 ]\n      +- [ 60 ]\n      +- [ 80, 99, 100 ]\n";

	for (int i = 0; i < 12; i++)
	{
		tree.Insert_TopDown(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}
	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 12 Passed" << endl;
	else
		cout << "\n\n Testcase 12 Failed" << endl;
}

void testcase_13()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output = "+- [ 10, 50 ]\n   +- [ 1, 2, 8 ]\n   +- [ 42 ]\n   +- [ 77, 90, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}
	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 13 Passed" << endl;
	else
		cout << "\n\n Testcase 13 Failed" << endl;
}

void testcase_14()
{
	BTree tree;

	int input[] = {42, 92, 84, 66, 42, 11};

	int flag = 0;

	for (int i = 0; i < 6; i++)
	{
		int return_value = tree.Insert_BottomUp(input[i]);

		if (return_value == false)
		{
			flag = 1;
			break;
		}

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";
		PrintTree(tree.getRoot(), "", true);
	}
	if (flag == 1)
		cout << "\n\n Testcase 14 Passed." << endl;
	else
		cout << "\n\n Testcase 14 Failed" << endl;
}
void testcase_15()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output = "+- [ 10, 50 ]\n   +- [ 1, 8 ]\n   +- [ 42 ]\n   +- [ 77, 90, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);
	}
	bool res = tree.Delete_TopDown(2);
	actual_output = PrintTree(tree.getRoot(), "", true);

	if (res && actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 15 Passed" << endl;
	else
		cout << "\n\n Testcase 15 Failed" << endl;
}

void testcase_16()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output_l = "+- [ 8, 50 ]\n   +- [ 1, 2 ]\n   +- [ 10 ]\n   +- [ 77, 90, 500 ]\n";
	string expected_output_r = "+- [ 10, 77 ]\n   +- [ 1, 2, 8 ]\n   +- [ 50 ]\n   +- [ 90, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);
	}
	bool res = tree.Delete_TopDown(42);
	actual_output = PrintTree(tree.getRoot(), "", true);

	if (res && (actual_output.compare(expected_output_l) == 0 || actual_output.compare(expected_output_r) == 0))
		cout << "\n\n Testcase 16 Passed" << endl;
	else
		cout << "\n\n Testcase 16 Failed" << endl;
}

void testcase_17()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output = "+- [ 10 ]\n   +- [ 1, 2, 8 ]\n   +- [ 42, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);
	}
	bool res = tree.Delete_TopDown(50);
	res = tree.Delete_TopDown(77);
	res = tree.Delete_TopDown(90);
	actual_output = PrintTree(tree.getRoot(), "", true);

	if (res && actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 17 Passed" << endl;
	else
		cout << "\n\n Testcase 17 Failed" << endl;
}
void testcase_18()
{
	BTree tree;

	int input[] = {1, 30, 29, 2, 4, 6, 10, 12, 15, 18, 20, 3, 13, 16, 17, 19, 7, 8, 9, 11, 14, 22, 21, 24, 25, 26, 23, 27, 28, 5};

	string actual_output = "";

	string expected_output = "+- [ 12 ]\n   +- [ 6 ]\n   |  +- [ 2 ]\n   |  |  +- [ 1 ]\n   |  |  +- [ 3, 4, 5 ]\n   |  +- [ 8 ]\n   |     +- [ 7 ]\n   |     +- [ 9, 10, 11 ]\n   +- [ 18, 22 ]\n      +- [ 15 ]\n      |  +- [ 13, 14 ]\n      |  +- [ 16, 17 ]\n      +- [ 20 ]\n      |  +- [ 19 ]\n      |  +- [ 21 ]\n      +- [ 25, 29 ]\n         +- [ 23, 24 ]\n         +- [ 26, 27, 28 ]\n         +- [ 30 ]\n";

	for (int i = 0; i < 30; i++)
	{
		tree.Insert_TopDown(input[i]);

		//cout<<"Inserted element: "<<input[i]<<"\n Printing Tree\n";

		actual_output = PrintTree(tree.getRoot(), "", true);
	}

	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 18 Passed" << endl;
	else
		cout << "\n\n Testcase 18 Failed" << endl;
}

int main()
{

	testcase_1(); //Basic Insertion Test

	testcase_2(); //Basic Insertion Test

	testcase_3(); //Basic Insertion Test

	testcase_4(); //Basic Insertion Test

	testcase_5(); // Duplicate insertion test

	testcase_6(); // Deletion of an element from leaf node test (borrowing from right sibling)

	testcase_7(); // Deletion of an element from leaf node test (borrowing from left sibling)

	testcase_8(); // Deletion of an element that doesn't exist in the tree

	testcase_9(); // Deletion of root from tree

	testcase_11();

	testcase_12();

	testcase_13();

	testcase_14();

	testcase_15();

	testcase_16();

	testcase_17();

	testcase_18();

	return 0;
}
