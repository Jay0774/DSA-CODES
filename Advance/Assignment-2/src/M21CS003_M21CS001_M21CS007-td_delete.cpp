#include "BTreeNode.cpp"

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