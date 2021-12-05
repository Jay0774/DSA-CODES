#include "BTreeNode.cpp"

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