#include "BTreeNode.cpp"

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