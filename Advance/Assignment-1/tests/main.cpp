#include "PrintConsoleTree.cpp"

/* Basic insertion test - tests if all distrinct elements are 
successfully being inserted into the Red Black Tree */
void testCase_1(AbstractBST *tree)
{ //10,18,19,20,24,6,7,3,4,
	int inputArray[] = {10, 6, 20, 3, 7, 19, 28, 4, 18, 24};
	for (int i = 0; i < 10; i++)
	{
		int returnType = tree->AddElement(inputArray[i]);
		if (returnType != true)
		{
			std::cout << "\nTestcase 1 - Failed";
			return;
		}
	}
	std::cout << "\nTestcase 1 - Passed";
}

/* Insertion of duplicate element into the Red Black Tree. If the 
insertion fails, the test passes. */
void testCase_2(AbstractBST *tree)
{
	int inputArray[] = {10, 9, 8, 7, 6, 5, 5, 4, 3, 2, 1};
	for (int i = 0; i < 11; i++)
	{
		int returnType = tree->AddElement(inputArray[i]);
		if (i == 6 && returnType != false)
		{
			std::cout << "\nTestcase 2 - Failed";
			return;
		}
	}
	std::cout << "\nTestcase 2 - Passed";
}

/* Searching for an element that is present in the Red Black Tree. 
Test case passes if element is found.*/
void testCase_3(AbstractBST *tree)
{
	int inputArray[] = {13, 8, 17, 1, 11, 15, 25, 6, 22, 27};
	for (int i = 0; i < 10; i++)
		tree->AddElement(inputArray[i]);
	for (int i = 0; i < 10; i++)
	{
		int returnType = tree->Contains(inputArray[i]);
		if (returnType != true)
		{
			std::cout << "\nTestcase 3 - Failed";
			return;
		}
	}
	std::cout << "\nTestcase 3 - Passed";
}

/* Searching for an element that isn't present in the Red Black Tree.
Test case passes if element isn't found. */
void testCase_4(AbstractBST *tree)
{
	int inputArray[] = {10, 9, 15, 12, 11, 13};
	for (int i = 0; i < 6; i++)
		tree->AddElement(inputArray[i]);
	int returnType = tree->Contains(24);
	if (returnType == true)
		std::cout << "\nTestcase 4 - Failed";
	else
		std::cout << "\nTestcase 4 - Passed";
}

/* Deleting an element from the Red Black Tree. If element to be deleted is found,
and is successfully removed, the testcase passes. */
void testCase_5(AbstractBST *tree)
{
	int inputArray[] = {8, 10, 9, 20, 19, 24, 19, 17};
	for (int i = 0; i < 6; i++)
		tree->AddElement(inputArray[i]);
	for (int i = 0; i < 6; i++)
	{
		int returnType = tree->RemoveElement(inputArray[i]);
		if (returnType != true)
		{
			std::cout << "\nTestcase 5 - Failed";
			return;
		}
	}
	std::cout << "\nTestcase 5 - Passed";
}

/* Deleting an element from the Red Black Tree. If element to be deleted
 is not found, the testcase passes. */
void testCase_6(AbstractBST *tree)
{
	int inputArray[] = {8, 17, 9, 24, 19, 18};
	for (int i = 0; i < 6; i++)
		tree->AddElement(inputArray[i]);
	int returnType = tree->RemoveElement(1);
	if (returnType == true)
		std::cout << "\nTestcase 6 - Failed";
	else
		std::cout << "\nTestcase 6 - Passed";
}

int main()
{
	RedBlackTree tree;
	testCase_1(&tree);
	tree.Clear();
	testCase_2(&tree);
	tree.Clear();
	testCase_3(&tree);
	tree.Clear();
	testCase_4(&tree);
	tree.Clear();
	testCase_5(&tree);
	tree.Clear();
	testCase_6(&tree);
}