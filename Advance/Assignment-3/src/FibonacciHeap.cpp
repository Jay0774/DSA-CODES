#include "FibonacciNode.cpp"

class FibonacciHeap
{
private:
	FibonacciNode *Root;
	int Count;
	void Consolidate()
	{
		FibonacciNode *node = Root;
		Root = nullptr;
		int i, d, max_degree = Log2(Count) + 1;
		FibonacciNode **array = new FibonacciNode *[max_degree];
		FibonacciNode *next, *w;
		for (i = 0; i < max_degree; i++)
			array[i] = nullptr;
		node->PrevSibiling->NextSibiling = nullptr;
		node->PrevSibiling = nullptr;
		while (node != nullptr)
		{
			next = node->NextSibiling;
			if (next != nullptr)
				node->NextSibiling = node->NextSibiling->PrevSibiling = nullptr;
			d = node->Degree;
			while (array[d] != nullptr)
			{
				w = array[d];
				if (w->Data < node->Data)
				{
					Add_Child(w, node);
					node->Marked = false;
					node = w;
				}
				else
				{
					Add_Child(node, w);
					w->Marked = false;
				}
				array[d] = nullptr;
				d = node->Degree;
			}
			array[d] = node;
			node = next;
		}
		for (i = 0; i < max_degree; i++)
		{
			if (array[i] != nullptr)
				Insert(array[i]);
		}
	}
	void Cut(FibonacciNode *x, FibonacciNode *y)
	{
		if (x->NextSibiling == x)
			y->LeftMostChild = nullptr;
		else
		{
			y->LeftMostChild = x->NextSibiling;
			Unattach_Node(x);
		}
		y->Degree--;
		x->Parent = nullptr;
		x->Marked = false;
		Insert(x); //Also ensures x becomes root if it is the minimum
	}
	void CascadingCut(FibonacciNode *x)
	{
		FibonacciNode *y = x->Parent;
		if (y != nullptr)
		{
			if (!(y->Marked))
				y->Marked = true;
			else
			{
				Cut(x, y);
				CascadingCut(y);
			}
		}
	}
	void Insert(FibonacciNode *node)
	{
		if (Root == nullptr)
		{
			Root = node;
			Root->NextSibiling = Root;
			Root->PrevSibiling = Root;
		}
		else
		{
			node->NextSibiling = Root;
			node->PrevSibiling = Root->PrevSibiling;
			Root->PrevSibiling->NextSibiling = node;
			Root->PrevSibiling = node;
			if (Root->Data > node->Data)
			{
				Root = node;
			}
		}
	}

public:
	/**
	 * @brief Construct a new Fibonacci Heap object
	 * 
	 */
	FibonacciHeap()
	{
		Count = 0;
		Root = nullptr;
	}
	/**
	 * @brief Destroy the Fibonacci Heap object
	 * 
	 */
	~FibonacciHeap()
	{
		while (Count > 0)
			DeleteMin();
	}
	/**
	 * @brief Get the minimum value of the heap
	 * 
	 * @return int 
	 */
	int GetTop()
	{
		return Root->Data;
	}
	/**
	 * @brief Get the Top Dictionary Object object
	 * 
	 * @return int 
	 */
	int GetTopDictionaryObject()
	{
		return Root->Object;
	}
	/**
	 * @brief Inserts a value to the heap
	 * 
	 * @param value 
	 */
	FibonacciNode *Insert(int value, int object = 0)
	{
		FibonacciNode *node = CreateNode(value);
		node->Object = object;
		Insert(node);
		Count++;
		return node;
	}
	/**
	 * @brief Joins another Heap with this heap
	 * 
	 * @param otherTree The heap to join
	 */
	void Union(FibonacciHeap &otherTree)
	{
		if (otherTree.Count == 0)
			return;
		if (Count == 0)
			Root = otherTree.Root;
		else
			Merge_Fibonacci_Nodes(Root, otherTree.Root);
		Count += otherTree.Count;
		otherTree.Root = nullptr;
		otherTree.Count = 0;
	}
	/**
	 * @brief Removes the least value of the heap
	 * 
	 * @return true Deletion successful
	 * @return false Deletion failed as there was no node to delete
	 */
	bool DeleteMin()
	{
		if (Count == 0)
			return false;
		else if (Count == 1)
		{
			delete Root;
			Root = nullptr;
		}
		else
		{
			FibonacciNode *c = Root->LeftMostChild;
			if (c != nullptr)
				Merge_Fibonacci_Nodes(Root, c);
			c = Root;
			Root = c->NextSibiling;
			Unattach_Node(c);
			Consolidate();
			delete c;
		}
		Count--;
		return true;
	}
	/**
	 * @brief Decreses the value of a node existing in the heap
	 * 
	 * @param node The node whose value is to be reduced
	 * @param newvalue The new value replaced in the node
	 * @return true Process completed successfully
	 * @return false newvalue is greater than the value of the node
	 */
	bool DecreaseKey(FibonacciNode *node, int newvalue)
	{
		if (node->Data < newvalue)
			return false;
		node->Data = newvalue;
		FibonacciNode *p = node->Parent;
		if (p != nullptr && node->Data < p->Data)
		{
			Cut(node, p);
			CascadingCut(p);
		} //Cut() also ensures node becomes the root if it is minimum
		return true;
	}
	/**
	 * @brief Get the number of elements in the heap
	 * 
	 * @return int 
	 */
	int GetSize()
	{
		return Count;
	}
	void Clear()
	{
		while (Count > 0)
			DeleteMin();
	}
};