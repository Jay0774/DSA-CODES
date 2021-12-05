#include "AbstractBST.cpp"
#define black true
#define red false
class RedBlackTree : public AbstractBST
{
private:
	Node *Root;
	int Count;
	Node *CreateNode(int value)
	{
		Node *x = new Node;
		x->LChild = NilNode();
		x->RChild = NilNode();
		x->LChild->Parent = x;
		x->RChild->Parent = x;
		x->Color = red;
		x->Data = value;
		return x;
	}
	Node *NilNode()
	{
		Node *x = new Node;
		x->RChild = x->LChild = x->Parent = nullptr;
		x->Color = black;
		return x;
	}
	bool isNil(Node *node)
	{
		return node->Color == black && (node->LChild == nullptr || node->RChild == nullptr);
	}
	void leftrotate(Node *x)
	{
		Node *y = x->RChild, *parent = x->Parent;
		x->RChild = y->LChild;
		x->RChild->Parent = x;
		y->LChild = x;
		y->Parent = parent;
		x->Parent = y;
		if (!isNil(parent))
		{
			if (parent->LChild == x)
				parent->LChild = y;
			else
				parent->RChild = y;
		}
		else
			Root = y;
	}
	void rightrotate(Node *y)
	{
		Node *x = y->LChild, *parent = y->Parent;
		y->LChild = x->RChild;
		y->LChild->Parent = y;
		x->RChild = y;
		x->Parent = parent;
		y->Parent = x;
		if (!isNil(parent))
		{
			if (parent->LChild == y)
				parent->LChild = x;
			else
				parent->RChild = x;
		}
		else
			Root = x;
	}
	Node *SearchNode(int data)
	{
		Node *x = Root;
		while (!isNil(x))
		{
			if (x->Data == data)
				return x;
			else if (x->Data < data)
				x = x->RChild;
			else
				x = x->LChild;
		}
		return nullptr;
	}
	void fixinsert(Node *x)
	{
		Node *father = x->Parent, *grandfather = father->Parent, *uncle;
		while (isNil(grandfather) == false && father->Color == red)
		{
			if (father == grandfather->LChild)
			{
				uncle = grandfather->RChild;
				if (uncle->Color == red)
				{
					uncle->Color = father->Color = black;
					grandfather->Color = red;
					x = grandfather;
				}
				else
				{
					if (x == father->RChild)
					{
						leftrotate(father);
						x = father;
						father = grandfather->LChild;
					}
					father->Color = black;
					grandfather->Color = red;
					rightrotate(grandfather);
				}
			}
			else
			{
				uncle = grandfather->LChild;
				if (uncle->Color == red)
				{
					uncle->Color = father->Color = black;
					grandfather->Color = red;
					x = grandfather;
				}
				else
				{
					if (x == father->LChild)
					{
						rightrotate(father);
						x->Parent = grandfather;
						x = father;
						father = grandfather->RChild;
					}
					father->Color = black;
					grandfather->Color = red;
					leftrotate(grandfather);
				}
			}
			father = x->Parent;
			grandfather = father->Parent;
		}
		Root->Color = black;
	}
	void fixdelete(Node *x)
	{
		while (x != Root && x->Color == black)
		{
			Node *w, *father = x->Parent;
			if (father->LChild == x)
			{
				w = father->RChild;
				if (w->Color == red) //Case 1L
				{
					w->Color = black;
					father->Color = red;
					leftrotate(father);
					w = father->RChild;
				}
				if (w->LChild->Color == black && w->RChild->Color == black) //Case 2L
				{
					w->Color = red;
					x = x->Parent;
					father = x->Parent;
				}
				else
				{
					if (w->RChild->Color == black) //Case 3L
					{
						w->LChild->Color = black;
						w->Color = red;
						rightrotate(w);
						w = father->RChild;
					}
					w->Color = father->Color; //Case 4L
					father->Color = black;
					w->RChild->Color = black;
					leftrotate(father);
					x = Root;
				}
			}
			else
			{
				w = father->LChild;
				if (w->Color == red) //Case 1R
				{
					w->Color = black;
					father->Color = red;
					rightrotate(father);
					w = father->LChild;
				}
				if (w->LChild->Color == black && w->RChild->Color == black) //Case 2R
				{
					w->Color = red;
					x = x->Parent;
					father = x->Parent;
				}
				else
				{
					if (w->LChild->Color == black) //Case 3R
					{
						w->RChild->Color = black;
						w->Color = red;
						leftrotate(w);
						w = father->LChild;
					}
					w->Color = father->Color; //Case 4R
					father->Color = black;
					w->LChild->Color = black;
					rightrotate(father);
					x = Root;
				}
			}
		}
		if (!isNil(x))
			x->Color = black; //Case 0
	}
	void Transplant(Node *before, Node *after)
	{
		Node *parent = before->Parent;
		if (isNil(parent))
			Root = after;
		else if (parent->LChild == before)
			parent->LChild = after;
		else
			parent->RChild = after;
		after->Parent = parent;
	}

public:
	RedBlackTree()
	{
		Root = NilNode();
		Root->Parent = Root;
		Count = 0;
	}
	int mid() { return Root->Data; }
	void Clear()
	{
		while (Count > 0)
		{
			int data = Root->Data;
			RemoveElement(data);
		}
	}
	bool AddElement(int element)
	{
		if (isNil(Root))
		{
			Node *nilnode = Root;
			Root = CreateNode(element);
			Root->Color = black;
			Root->Parent = nilnode;
			Count++;
			return true;
		}
		Node *a, *b;
		a = Root;
		while (!isNil(a))
		{
			b = a;
			if (a->Data == element)
				return false;
			if (a->Data < element)
				a = a->RChild;
			else
				a = a->LChild;
		}
		Node *temp = CreateNode(element), *delnode;
		temp->Parent = b;
		if (b->Data < temp->Data)
		{
			delnode = b->RChild;
			b->RChild = temp;
		}
		else
		{
			delnode = b->LChild;
			b->LChild = temp;
		}
		delete delnode;
		fixinsert(temp);
		Count++;
		return true;
	}
	bool RemoveElement(int element)
	{
		Node *delnode = SearchNode(element), *fixnode, *successor;
		if (delnode == nullptr)
			return false;
		bool OriginalColor = delnode->Color;
		if (isNil(delnode->LChild))
		{
			fixnode = delnode->RChild;
			Transplant(delnode, fixnode);
			delnode->RChild = nullptr;
			delete delnode->LChild; //Extra NIL node
		}
		else if (isNil(delnode->RChild))
		{
			fixnode = delnode->LChild;
			Transplant(delnode, fixnode);
			delnode->LChild = nullptr;
			delete delnode->RChild; //Extra NIL node
		}
		else
		{
			successor = delnode->RChild;
			while (!isNil(successor->LChild))
				successor = successor->LChild;
			delete successor->LChild; //Extra NIL node
			OriginalColor = successor->Color;
			fixnode = successor->RChild;
			if (successor->Parent == delnode)
				fixnode->Parent = successor;
			else
			{
				Transplant(successor, fixnode);
				successor->RChild = delnode->RChild;
				successor->RChild->Parent = successor;
				delnode->RChild = nullptr;
			}
			Transplant(delnode, successor);
			successor->LChild = delnode->LChild;
			delnode->LChild = nullptr;
			successor->LChild->Parent = successor;
			successor->Color = delnode->Color;
		}
		if (OriginalColor == black)
			fixdelete(fixnode);
		delete delnode;
		Count--;
		if (Count == 0)
		{
			delnode = Root;
			Root = Root->Parent;
			delete delnode; //In case of root node,
							//Another leaf node is deleted
		}
		return true;
	}
	bool Contains(int element)
	{
		return SearchNode(element) != nullptr;
	}
	void PrintTree(void (*Printer)(Node *n))
	{
		if (!isNil(Root))
			Printer(Root);
	}
};
