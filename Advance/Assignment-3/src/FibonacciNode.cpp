/**
 * @brief Represents a node in the Fibonacci Heap
 * 
 */
struct FibonacciNode
{
	/**
	 * @brief Pointers
	 * 
	 */
	FibonacciNode *Parent, *LeftMostChild, *NextSibiling, *PrevSibiling;
	/**
	 * @brief Data fields
	 * 
	 */
	int Data, Degree;
	/**
	 * @brief Data fields
	 * 
	 */
	bool Marked;
	int Object;
};
/**
 * @brief Create a Node object
 * 
 * @param data: The data contained by this node
 * @return FibonacciNode* Created node
 */
FibonacciNode *CreateNode(int data)
{
	FibonacciNode *node = new FibonacciNode;
	node->Data = data;
	node->Parent = node->LeftMostChild = node->NextSibiling = node->PrevSibiling = nullptr;
	node->Degree = 0;
	node->Marked = false;
	return node;
}

/**
 * @brief Joins/connects the two circular list of nodes together
 * 
 * @param n1 Circular list of sibiling nodes
 * @param n2 Circular list of sibiling nodes
 */
void Merge_Fibonacci_Nodes(FibonacciNode *n1h, FibonacciNode *n2h)
{
	FibonacciNode *n1p = n1h->PrevSibiling, *n2p = n2h->PrevSibiling;
	n1p->NextSibiling = n2h;
	n2h->PrevSibiling = n1p;
	n2p->NextSibiling = n1h;
	n1h->PrevSibiling = n2p;
}

/**
 * @brief De-links this node with its sibilings
 * 
 * @param node The node to de-link
 */
void Unattach_Node(FibonacciNode* node)
{
	if(node->NextSibiling!=nullptr && node->PrevSibiling!=nullptr)
	{
		node->PrevSibiling->NextSibiling=node->NextSibiling;
		node->NextSibiling->PrevSibiling=node->PrevSibiling;
	}
}

/**
 * @brief Attaches one node as the child of the other
 * 
 * @param parent The node which is to be the parent
 * @param child The node which is to be the child
 */
void Add_Child(FibonacciNode* parent, FibonacciNode* child)
{
	if(parent->Degree==0||parent->LeftMostChild==nullptr)
	{
		parent->Degree=0;
		parent->LeftMostChild=child;
		child->PrevSibiling=child->NextSibiling=child;
	}
	else
	{
		child->NextSibiling=parent->LeftMostChild;
		child->PrevSibiling=parent->LeftMostChild->PrevSibiling;
		child->NextSibiling->PrevSibiling=child;
		child->PrevSibiling->NextSibiling=child;
	}
	parent->Degree++;
	child->Parent=parent;
}

int Log2(unsigned int x)
{
	int bits=0;
	while(x>0)
	{
		bits++;
		x>>=1;
	}
	return bits;
}