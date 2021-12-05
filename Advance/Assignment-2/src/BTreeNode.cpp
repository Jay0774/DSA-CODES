#ifndef BTreeNode_CPP
#define BTreeNode_CPP

/**
 * @brief Denotes a single node of the Tree
 * 
 */
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

/**
 * @brief Create a Node object
 * 
 * @return BTreeNode* 
 */
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
	node->CurrentNodes -= 2;
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
			node->Children[i]->Parent = node;
		}
		for (i = 0; i <= y->CurrentNodes; i++)
		{
			y->Children[i]->ParentIndex = i;
			y->Children[i]->Parent = y;
		}
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
/**
 * @brief Merges a node having a single key and 2 children, each having a single key
 * 
 */
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
#endif