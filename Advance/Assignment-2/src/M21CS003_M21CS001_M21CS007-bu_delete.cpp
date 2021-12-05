#include "BTreeNode.cpp"

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
			max = max->Children[max->CurrentNodes]; //Get the right-most (max) child
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
			node->Parent->Data[xi] = SibilingData;
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