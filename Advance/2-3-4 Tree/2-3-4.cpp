#include<iostream>
#include<string.h>
using namespace std;

struct BTreeNode
{
	/**
	 * @brief Stores values on this array of data(integers)
	 * 
	 */
	int *Data;
	/**
	 * @brief Array of pointers, denoting child nodes
	 * 
	 */
	BTreeNode **Children;
	/**
	 * @brief The number of data nodes currently occupied in this node 
	 * 
	 */
	int CurrentNodes;
	/**
	 * @brief Denotes whether this node is leaf or not
	 * 
	 */
	bool IsLeafNode;
	/**
	 * @brief The Parent of this node
	 * 
	 */
	BTreeNode *Parent;
	/**
	 * @brief The index of this node inside its parent
	 * 
	 */
	int ParentIndex;
};
BTreeNode *CreateNode()
{
	BTreeNode *node = new BTreeNode;
	node->Data = new int[4]();			   //A node can have at most of 3 data items. If 4th item is added, it is split
	node->Children = new BTreeNode *[5](); //A node can have at most 4 children, extra space for overflow
	node->CurrentNodes = 0;				   //No elements inside this node yet
	node->IsLeafNode = true;			   //By default
	node->Parent = nullptr;				   //Only true for root
	return node;
}

/**
 * @brief Searches within this node
 * 
 * @param node: The root of the subtree being searched
 * @param value The item to search
 * @param FoundPosition: If found, denotes the index of the iten in returned node, otherwise -1
 * @return BTreeNode* If found, returns the node in which it is found. Otherwise the node where the insertion should be done
 */
BTreeNode *SearchNode(BTreeNode *node, int value, int &FoundPosition)
{
	FoundPosition = -1;
	if (node == nullptr)
		return nullptr;
	while (true)
	{
		int i = 0;
		while (i < node->CurrentNodes && node->Data[i] < value)
		{
			i++;
		}
		if (i < node->CurrentNodes && node->Data[i] == value)
		{
			FoundPosition = i;
			break;
		}
		else if (node->IsLeafNode)
		{
			break;
		}
		else
		{
			node = node->Children[i];
		}
	}
	return node;
}
/**
 * @brief Shifts all elements of an array by one element, from left to right
 *  starting from the given index
 * 
 * @tparam T The type of array
 * @param Array The array in which the shifting process is done
 * @param index The index from which the shifting is done
 * @param limit The index until which the shifting must be done. In most cases, it is size-1
 */
template <class T>
void RightShiftArray(T *Array, int index, int limit)
{
	if (index >= limit)
		return;
	for (int i = limit - 1; i >= index; i--)
	{
		Array[i + 1] = Array[i];
	}
}

/**
 * @brief Shifts all elements of an array by one element, from Right to left
 *  starting from the given index
 * 
 * @tparam T The type of array
 * @param Array The array in which the shifting process is done
 * @param index The index from which the shifting is done
 */
template <class T>
void LeftShiftArray(T *Array, int index, int size)
{
	size--;
	for (int i = index; i < size; i++)
	{
		Array[i] = Array[i + 1];
	}
}

/**
 * @brief Adds an element in its sorted location
 * 
 * @param Array The array in which the insertion is to be done
 * @param value The item to insert
 * @param size The size of the sorted array to consider
 * @return int The index at which the insertion was made
 */
int SortInsert(int *Array, int value, int size)
{
	int shiftIndex = 0;
	while (shiftIndex < size && value > Array[shiftIndex])
		shiftIndex++;
	RightShiftArray<int>(Array, shiftIndex, size);
	Array[shiftIndex] = value;
	return shiftIndex;
}
/**
 * @brief Splits the given node's child and pushes its median into its parent. 
 * 
 * @param ParentNode The node whose child needs to be split into sibilings
 * @param ChildIndex The index of this child
 */
void SplitNode(BTreeNode *ParentNode, int ChildIndex)
{
	BTreeNode *node = ParentNode->Children[ChildIndex], *y = CreateNode();
	y->Parent = ParentNode;
	y->Data[0] = node->Data[0];
	y->Children[0] = node->Children[0];
	y->Children[1] = node->Children[1];
	y->CurrentNodes = 1;
	y->IsLeafNode = node->IsLeafNode;
	int value = node->Data[1];
	node->Data[0] = node->Data[2];
	node->Data[1] = node->Data[3];
	node->Data[2] = node->Data[3] = 0;
	node->Children[0] = node->Children[2];
	node->Children[1] = node->Children[3];
	node->Children[2] = node->Children[4];
	node->Children[4] = nullptr;
	node->CurrentNodes-=2;
	int insertedIndex = SortInsert(ParentNode->Data, value, ParentNode->CurrentNodes);
	ParentNode->CurrentNodes++;
	RightShiftArray<BTreeNode *>(ParentNode->Children, insertedIndex, ParentNode->CurrentNodes);
	ParentNode->Children[insertedIndex] = y;
	int i;
	for (i = 0; i <= ParentNode->CurrentNodes; i++)
	{
		ParentNode->Children[i]->ParentIndex = i;
	}
	if (!y->IsLeafNode)
	{
		for (i = 0; i <= node->CurrentNodes; i++)
		{
			node->Children[i]->ParentIndex = i;
			node->Children[i]->Parent=node;
		}
		for (i = 0; i <= y->CurrentNodes; i++)
		{
			y->Children[i]->ParentIndex = i;
			y->Children[i]->Parent=y;
		}
	}
}
void MergeNode(BTreeNode *node, int index)
{//It is given that this node has exactly 1 child, and so does its two children
	BTreeNode *l = node->Children[index], *r = node->Children[index + 1]; //Both have one keys
	int i;
	l->Data[1] = node->Data[index];
	l->Data[2] = r->Data[0];
	l->Children[2] = r->Children[0];
	l->Children[3] = r->Children[1];
	l->CurrentNodes = 3;
	if (!l->IsLeafNode)
	{
		for (i = 0; i < 4; i++)
		{
			l->Children[i]->ParentIndex = i;
			l->Children[i]->Parent = l;
		}
	}
	LeftShiftArray<int>(node->Data, index, node->CurrentNodes);
	LeftShiftArray<BTreeNode *>(node->Children, index + 1, node->CurrentNodes + 1);
	node->CurrentNodes--;
	for (i = 0; i <= node->CurrentNodes; i++)
	{
		node->Children[i]->Parent = node;
		node->Children[i]->ParentIndex = i;
	}
}
/**
 * @brief Splits the root node. 
 * 
 * @param Root: The root of the subtree. Notice that this is called by reference!
 */
void SplitRoot(BTreeNode *&Root)
{
	BTreeNode *x = Root;
	Root = CreateNode(); //Root is called by reference, so this will work
	x->Parent = Root;
	x->ParentIndex = 0;
	Root->Children[0] = x;
	SplitNode(Root, 0);
	Root->IsLeafNode = false;
}
bool bu_delete(BTreeNode *&Root, int value)
{
	int pos = -1;
	BTreeNode *node = SearchNode(Root, value, pos);
	if (pos == -1)
		return false;
	if (node->IsLeafNode)
	{
		LeftShiftArray<int>(node->Data, pos, node->CurrentNodes);
		node->CurrentNodes--;
	}
	else
	{
		BTreeNode *max = node->Children[pos]; //Left child of node
		while (!max->IsLeafNode)
		{
			max = max->Children[max->CurrentNodes - 1]; //Get the right-most (max) child
		}
		max->CurrentNodes--;
		node->Data[pos] = max->Data[max->CurrentNodes];
		node = max;
	}
	while (node->CurrentNodes == 0)
	{
		BTreeNode *sibiling;
		int pi, xi;
		bool Case1L = (node->ParentIndex > 0 && node->Parent->Children[node->ParentIndex - 1]->CurrentNodes > 1);
		bool Case1R = (node->ParentIndex + 1 <= node->Parent->CurrentNodes && node->Parent->Children[node->ParentIndex + 1]->CurrentNodes > 1);
		if (node == Root)
		{
			if (Root->Children[0] != nullptr)
			{
				Root = Root->Children[0];
				delete node;
				Root->Parent = nullptr;
				Root->ParentIndex = -1;
				node = Root;
			}
			else
				break; //The tree is supposed to be completly empty
		}
		else if (Case1L || Case1R)
		{
			int SibilingData, ParentData;
			if (Case1L)
			{ //Borrow from left sibiling if available
				pi = node->ParentIndex - 1;
				xi = pi;
				sibiling = node->Parent->Children[pi];
				SibilingData = sibiling->Data[sibiling->CurrentNodes - 1];
				if (!sibiling->IsLeafNode)
				{
					node->Children[1] = node->Children[0];
					node->Children[1]->ParentIndex = 1;
					node->Children[0] = sibiling->Children[sibiling->CurrentNodes];
					node->Children[0]->Parent = node->Children[1]->Parent = node;
					node->Children[0]->ParentIndex = 0;
				}
				sibiling->Children[sibiling->CurrentNodes] = nullptr;
			}
			else
			{ //Borrow from right sibiling if available
				pi = node->ParentIndex + 1;
				xi = node->ParentIndex;
				sibiling = node->Parent->Children[pi];
				SibilingData = sibiling->Data[0];
				LeftShiftArray<int>(sibiling->Data, 0, sibiling->CurrentNodes);
				if (!sibiling->IsLeafNode)
				{
					node->Children[1] = sibiling->Children[0];
					node->Children[1]->Parent = node;
					node->Children[1]->ParentIndex = 1;
					sibiling->Children[sibiling->CurrentNodes] = nullptr;
					LeftShiftArray<BTreeNode *>(sibiling->Children, 0, sibiling->CurrentNodes + 1);
				}
				sibiling->Children[sibiling->CurrentNodes] = nullptr;
			}
			ParentData = node->Parent->Data[xi];
			sibiling->CurrentNodes--;
			node->Parent->Data[pi] = SibilingData;
			node->Data[0] = ParentData;
			node->CurrentNodes = 1;
		}
		else
		{							   //Merge childs
			if (node->ParentIndex > 0) //There exists a left child
			{
				pi = node->ParentIndex - 1;
				xi = pi;
				sibiling = node->Parent->Children[pi];
				sibiling->Data[sibiling->CurrentNodes] = node->Parent->Data[xi];
				sibiling->CurrentNodes++;
				sibiling->Children[sibiling->CurrentNodes] = node->Children[0];
				if (node->Children[0] != nullptr)
				{
					node->Children[0]->Parent = sibiling;
					node->Children[0]->ParentIndex = sibiling->CurrentNodes;
					node->Children[0] = nullptr;
				}
				node->Parent->Children[node->ParentIndex] = nullptr;
				delete node;
				node = sibiling->Parent;
			}
			else //There exists a right child
			{
				pi = node->ParentIndex + 1;
				xi = pi - 1;
				sibiling = node->Parent->Children[pi];
				node->Data[0] = node->Parent->Data[xi];
				node->Data[1] = sibiling->Data[0];
				if (!sibiling->IsLeafNode)
				{
					node->Children[1] = sibiling->Children[0];
					node->Children[1]->Parent = node;
					node->Children[1]->ParentIndex = 1;
					node->Children[2] = sibiling->Children[1];
					node->Children[2]->Parent = node;
					node->Children[2]->ParentIndex = 2;
				}
				node->CurrentNodes = 2;
				delete sibiling;
				node = node->Parent;
			}
			LeftShiftArray<int>(node->Data, xi, node->CurrentNodes);
			LeftShiftArray<BTreeNode *>(node->Children, pi + 1, node->CurrentNodes+1);
			node->Children[node->CurrentNodes] = nullptr;
			node->CurrentNodes--;
			for (int i = 0; i <= node->CurrentNodes; i++)
			{
				node->Children[i]->Parent = node;
				node->Children[i]->ParentIndex = i;
			}
		}
		node->IsLeafNode = node->Children[0] == nullptr;
	}
	return true;
}
bool bu_insert(BTreeNode *&Root, int value)
{
	int found = -1;
	BTreeNode *node = SearchNode(Root, value, found);
	if (found != -1)
		return false;
	if (node->CurrentNodes == 0) //Possible only for Root
	{
		node->CurrentNodes++;
		node->Data[0] = value;
		return true;
	}
	int insertedIndex = SortInsert(node->Data, value, node->CurrentNodes);
	node->CurrentNodes++;
	while (node->CurrentNodes == 4)
	{
		if (node == Root)
		{
			SplitRoot(Root);
			return true;
		}
		else
			SplitNode(node->Parent, node->ParentIndex);
		node = node->Parent;
	}
	return true;
}
bool td_delete(BTreeNode *&Root, int value)
{
	int pos = -1;
	BTreeNode *node = SearchNode(Root, value, pos);
	if (pos == -1)
		return false;
	if (Root->CurrentNodes == 1 && Root->IsLeafNode == false && Root->Children[0]->CurrentNodes == 1 && Root->Children[1]->CurrentNodes == 1)
	{
		BTreeNode *l = Root->Children[0], *r = Root->Children[1];
		Root->Data[1] = Root->Data[0];
		Root->Data[0] = l->Data[0];
		Root->Data[2] = r->Data[1];
		Root->Children[0] = l->Children[0];
		Root->Children[1] = l->Children[1];
		Root->Children[2] = r->Children[0];
		Root->Children[3] = r->Children[1];
		delete l;
		delete r;
		Root->CurrentNodes = 3;
		Root->IsLeafNode = Root->Children[0] == nullptr;
		if (!Root->IsLeafNode)
		{
			for (int i = 0; i < 4; i++)
			{
				Root->Children[i]->Parent = Root;
				Root->Children[i]->ParentIndex = i;
			}
		}
	}
	node = Root;
	while (!node->IsLeafNode)
	{
		int FoundPosition = -1;
		int i = 0;
		while (i < node->CurrentNodes && node->Data[i] < value)
		{
			i++;
		}
		if (i < node->CurrentNodes && node->Data[i] == value)
		{
			if (node->Children[i]->CurrentNodes > 1)
			{
				BTreeNode *max = node->Children[i];
				while (!max->IsLeafNode)
					max = max->Children[max->CurrentNodes];
				value = max->Data[max->CurrentNodes - 1];
				node->Data[i] = value;
				node = node->Children[i];
			}
			else if (node->Children[i + 1]->CurrentNodes > 1)
			{
				BTreeNode *min = node->Children[i + 1];
				while (!min->IsLeafNode)
					min = min->Children[0];
				value = min->Data[0];
				node->Data[i] = value;
				node = node->Children[i+1];
			}
			else
			{
				MergeNode(node, i);
				node = node->Children[i];
			}
		}
		else
		{
			if (node->Children[i]->CurrentNodes == 1)
			{
				BTreeNode *l, *r;
				if (i > 0 && node->Children[i - 1]->CurrentNodes > 1)
				{
					l = node->Children[i - 1];
					r = node->Children[i];
					RightShiftArray<int>(r->Data, 0, r->CurrentNodes);
					RightShiftArray<BTreeNode *>(r->Children, 0, r->CurrentNodes + 1);
					r->Data[0] = node->Data[i-1];
					node->Data[i-1]=l->Data[l->CurrentNodes-1];
					r->Children[0] = l->Children[l->CurrentNodes];
					l->Children[l->CurrentNodes]=nullptr;
					l->CurrentNodes--;
					r->CurrentNodes++;
					if(r->Children[0]!=nullptr)
					{
						for(i=0;i<=r->CurrentNodes;i++)
						{
							r->Children[i]->Parent=r;
							r->Children[i]->ParentIndex=i;
						}
					}
					node=r;
				}
				else if (i + 1 <= node->CurrentNodes && node->Children[i + 1]->CurrentNodes > 1)
				{
					l = node->Children[i];
					r = node->Children[i+1];
					l->Data[l->CurrentNodes]=node->Data[i];
					node->Data[i]=r->Data[0];
					LeftShiftArray<int>(r->Data, 0, r->CurrentNodes);
					l->CurrentNodes++;
					l->Children[l->CurrentNodes]=r->Children[0];
					LeftShiftArray<BTreeNode*>(r->Children,0,r->CurrentNodes+1);
					r->Children[r->CurrentNodes]=nullptr;
					r->CurrentNodes--;
					if(l->Children[0]!=nullptr)
					{
						for(i=0;i<=l->CurrentNodes;i++)
						{
							l->Children[i]->Parent=l;
							l->Children[i]->ParentIndex=i;
						}
						for(i=0;i<=r->CurrentNodes;i++)
						{
							r->Children[i]->Parent=r;
							r->Children[i]->ParentIndex=i;
						}
					}
					node=l;
				}
				else
				{
					if (i > 0) //left child exists
						MergeNode(node, i - 1);
					else
						MergeNode(node, i);
				}
			}
			else
			{
				node=node->Children[i];
			}
		}
	}
	int i = 0;
	while (i < node->CurrentNodes && node->Data[i] < value)
	{
		i++;
	}
	LeftShiftArray<int>(node->Data, i, node->CurrentNodes);
	node->CurrentNodes--;
	return true;
}
bool td_insert(BTreeNode *&Root, int value)
{
    int pos = -1;
    SearchNode(Root, value, pos);
    if (pos != -1)
        return false;
    if(Root->CurrentNodes==3)
		SplitRoot(Root);
	BTreeNode*node = Root;
	while(!node->IsLeafNode)
	{
		int i=0;
		while(i<node->CurrentNodes && node->Data[i] < value)
		{
			i++;
		}
		if(node->Children[i]->CurrentNodes==3)
		{
			SplitNode(node, i);
			if(node->Data[i] < value)
				i++;
		}
		node=node->Children[i];
	}
	SortInsert(node->Data, value, node->CurrentNodes);
	node->CurrentNodes++;
	return false;
}
class BTree
{
	BTreeNode *Root;
	int Count;
public:
	/**
	 * @brief Construct a new BTree object
	 * 
	 */
	BTree()
	{
		Root = CreateNode();
		Count = 0;
	}
	/**
	 * @brief Get the number of items inserted in this BTree
	 * 
	 * @return int 
	 */
	int GetCount()
	{
		return Count;
	}
	/**
	 * @brief Inserts an item using the Top-Down Approach
	 * 
	 * @param item The item to insert
	 * @return bool: Denotes if the insertion was successful
	 */
	bool Insert_TopDown(int item)
	{
		bool res = td_insert(Root, item);
		if(res)Count++;
		return res;
	}
	/**
	 * @brief Inserts an item using the Bottom-Up Approach
	 * 
	 * @param item The item to insert
	 * @return bool: Denotes if the insertion was successful
	 */
	bool Insert_BottomUp(int item)
	{
		bool res = bu_insert(Root, item);
		if(res)Count++;
		return res;
	}
	/**
	 * @brief Deletes an item using the Top-Down approach
	 * 
	 * @param item The item to delete from the Tree
	 * @return bool Denotes if the deletion is successful
	 */
	bool Delete_TopDown(int item)
	{
		bool res = td_delete(Root, item);
		if(res)Count--;
		return res;
	}
	/**
	 * @brief Deletes an item using the Bottom-Up approach
	 * 
	 * @param item The item to delete from the Tree
	 * @return bool Denotes if the deletion is successful
	 */
	bool Delete_BottomUp(int item)
	{
		bool res =  bu_delete(Root, item);
		if(res)Count--;
		return res;
	}
	/**
	 * @brief Searches for a given item within the BTree
	 * 
	 * @param item The item to search
	 * @return bool: True if item is found, False otherwise
	 */
	bool Contains(int item)
	{
		BTreeNode *z = Root;
		int result;
		BTreeNode *x = SearchNode(z, item, result);
		return result!=-1;
	}
	BTreeNode* getRoot()
	{
		return Root;//delete this
	}
};





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

	string expected_output = "+- [ 5 ]\n   +- [ 3 ]\n   |  +- [ 1, 2 ]\n   |  +- [ 4 ]\n   +- [ 9 ]\n      +- [ 6, 7, 8 ]\n      +- [ 10 ]\n";

	for (int i = 0; i < 10; i++)
	{
		tree.Insert_TopDown(input[i]);

	}
    actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 1 Passed" << endl;
	else
		cout << "\n\n Testcase 1 Failed" << endl;
}

void testcase_2()
{
	BTree tree;

	int input[] = {10, 30, 60, 20, 50, 44, 76, 80, 15, 99, 100, 25};

	string actual_output = "";

	string expected_output = "+- [ 50 ]\n   +- [ 15, 30 ]\n   |  +- [ 10 ]\n   |  +- [ 20, 25 ]\n   |  +- [ 44 ]\n   +- [ 76 ]\n      +- [ 60 ]\n      +- [ 80, 99, 100 ]\n";

	for (int i = 0; i < 12; i++)
	{
		tree.Insert_TopDown(input[i]);

	}
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 2 Passed" << endl;
	else
		cout << "\n\n Testcase 2 Failed" << endl;
}

void testcase_3()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output = "+- [ 10, 50 ]\n   +- [ 1, 2, 8 ]\n   +- [ 42 ]\n   +- [ 77, 90, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);

	}
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 3 Passed" << endl;
	else
		cout << "\n\n Testcase 3 Failed" << endl;
}

void testcase_4()
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
		PrintTree(tree.getRoot(), "", true);
	}
	if (flag == 1)
		cout << "\n\n Testcase 4 Passed." << endl;
	else
		cout << "\n\n Testcase 4 Failed" << endl;
}
void testcase_5()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output = "+- [ 10, 50 ]\n   +- [ 1, 8 ]\n   +- [ 42 ]\n   +- [ 77, 90, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);
	}
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	bool res = tree.Delete_TopDown(2);
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	if (res && actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 5 Passed" << endl;
	else
		cout << "\n\n Testcase 5 Failed" << endl;
}

void testcase_6()
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
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	bool res = tree.Delete_TopDown(42);
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;

	if (res && (actual_output.compare(expected_output_l) == 0 || actual_output.compare(expected_output_r) == 0))
		cout << "\n\n Testcase 6 Passed" << endl;
	else
		cout << "\n\n Testcase 6 Failed" << endl;
}

void testcase_7()
{
	BTree tree;

	int input[] = {42, 50, 77, 90, 10, 8, 2, 1, 500};

	string actual_output = "";

	string expected_output = "+- [ 10 ]\n   +- [ 1, 2, 8 ]\n   +- [ 42, 500 ]\n";

	for (int i = 0; i < 9; i++)
	{
		tree.Insert_TopDown(input[i]);
	}
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	bool res = tree.Delete_TopDown(50);
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	res = tree.Delete_TopDown(77);
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	res = tree.Delete_TopDown(90);
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	actual_output = PrintTree(tree.getRoot(), "", true);

	if (res && actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 7 Passed" << endl;
	else
		cout << "\n\n Testcase 7 Failed" << endl;
}

void testcase_8()
{
	BTree tree;

	int input[] = {1, 30, 29, 2, 4, 6, 10, 12, 15, 18, 20, 3, 13, 16, 17, 19, 7, 8, 9, 11, 14, 22, 21, 24, 25, 26, 23, 27, 28, 5 };

	string actual_output = "";

	string expected_output = "+- [ 12 ]\n   +- [ 6 ]\n   |  +- [ 2 ]\n   |  |  +- [ 1 ]\n   |  |  +- [ 3, 4, 5 ]\n   |  +- [ 8 ]\n   |     +- [ 7 ]\n   |     +- [ 9, 10, 11 ]\n   +- [ 18, 22 ]\n      +- [ 15 ]\n      |  +- [ 13, 14 ]\n      |  +- [ 16, 17 ]\n      +- [ 20 ]\n      |  +- [ 19 ]\n      |  +- [ 21 ]\n      +- [ 25, 29 ]\n         +- [ 23, 24 ]\n         +- [ 26, 27, 28 ]\n         +- [ 30 ]\n";

	for (int i = 0; i < 30; i++)
	{
		tree.Insert_TopDown(input[i]);
	}
	actual_output = PrintTree(tree.getRoot(), "", true);
	cout<<actual_output<<endl;
	if (actual_output.compare(expected_output) == 0)
		cout << "\n\n Testcase 8 Passed" << endl;
	else
		cout << "\n\n Testcase 8 Failed" << endl;
}



int main()
{

	testcase_1(); //Basic Insertion Test

	testcase_2(); //Basic Insertion Test

	testcase_3(); //Basic Insertion Test

	testcase_4(); // Duplicate insertion test

	testcase_5(); // Delete from leaf

	testcase_6(); // Delete from with borrow from sibling

	testcase_7(); // Delete from internal with merge
	
	testcase_8(); // Large data Insertion

	return 0;
}
