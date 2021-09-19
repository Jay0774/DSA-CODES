#include<bits/stdc++.h>
#define black true
#define red false
using namespace std;
struct Node
{
	/**
	 * @brief The data contained by the tree
	 * 
	 */
	int Data;
	/**
	 * @brief The Child nodes of this node
	 * 
	 */
	Node *LChild, *RChild, *Parent;
	/**
	 * @brief returns true if this node is black, otherwise false
	 * 
	 */
	bool Color;
};


/**
 * @brief This is an abstract BST that stores int values
 * 
 */
class AbstractBST
{
public:
	/**
	 * @brief This function adds the given element to the tree 
	 * (only if it does not exist already in the tree) and returns true. 
	 * Otherwise, it returns false.
	 * 
	 * @param element: The element to add
	 * @return bool: True on sucessfull addition, otherwise false
	 */
	virtual bool AddElement(int element)=0;
	/**
	 * @brief This function removes the element from the tree (if it exists
	 * inside the tree) and returns true, otherwise it returns false
	 * 
	 * @param element: Element to remove
	 * @return bool: True on sucessful removal, otherwise false
	 */
	virtual bool RemoveElement(int element)=0;
	/**
	 * @brief This function checks if a given element is present 
	 * 
	 * @param element: The element to check if it exists in the tree
	 * @return bool: True if element is found, otherwise false
	 */
	virtual bool Contains(int element)=0;
};
class RedBlackTree : public AbstractBST
{
private:
	Node *Root;
	Node *Sential;
	Node *CreateNode(int value)
	{
		Node *x = new Node;
		x->RChild = x->LChild = x->Parent = Sential;
		x->Color = red;
		x->Data = value;
		return x;
	}
	Node *leftrotate(Node *x)
	{
		Node *y = x->RChild;
		x->RChild = y->LChild;
		y->LChild = x;
		y->Parent = x->Parent;
		x->Parent = y;
		return y;
	}
	Node *rightrotate(Node *y)
	{
		Node *x = y->LChild;
		y->LChild = x->RChild;
		x->RChild = y;
		x->Parent = y->Parent;
		y->Parent = x;
		return x;
	}
	void fixinsert(Node *x)
	{
		Node *father = x->Parent, *grandfather = father->Parent, *uncle;
		while (grandfather != Sential && father->Color == red)
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
						grandfather->LChild = leftrotate(father);
						x->Parent = grandfather;
						x = father;
						father = grandfather->LChild;
					}
					father->Color = black;
					grandfather->Color = red;
					if (Root == grandfather)
						Root = rightrotate(grandfather);
					else
					{
						father = grandfather->Parent;
						if (grandfather == father->LChild)
							father->LChild = rightrotate(grandfather);
						else
							father->RChild = rightrotate(grandfather);
					}
				}
			}
			else
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
					if (x == father->LChild)
					{
						grandfather->RChild = leftrotate(father);
						x->Parent = grandfather;
						x = father;
						father = grandfather->RChild;
					}
					father->Color = black;
					grandfather->Color = red;
					if (Root == grandfather)
						Root = rightrotate(grandfather);
					else
					{
						father = grandfather->Parent;
						if (grandfather == father->LChild)
							father->LChild = rightrotate(grandfather);
						else
							father->RChild = rightrotate(grandfather);
					}
				}
			}
			father = x->Parent;
			grandfather = father->Parent;
		}
		Root->Color = black;
	}
	Node* Sucessor(Node *x)
	{
	    Node *traverse;
	    if(x->LChild!=Sential)
	    {
	        traverse=x->LChild;
	        while(traverse->RChild!=Sential)
	            traverse=traverse->RChild;
	    }
	    else
	    {
	        traverse=traverse->RChild;
	        while(traverse->LChild!=Sential)
	            traverse=traverse->LChild;
	    }
	    return traverse;
	}
	void fixdelete(Node *x)
    {
        Node *delNode;
        while(x!=Root && x->Color==black)
        {
            if(x->Parent->LChild==x)
            {
                    delNode=x->Parent->RChild;
                    if(delNode->Color==red)
                    {
                        delNode->Color=black;
                        x->Parent->Color=red;
                        leftrotate(x->Parent);
                        delNode=x->Parent->RChild;
                    }
                    if(delNode->RChild->Color==black && delNode->LChild->Color==black)
                    {
                        delNode->Color=red;
                        x=x->Parent;
                    }
                    else
                    {
                        if(delNode->RChild->Color==black)
                        {
                            delNode->LChild->Color==black;
                            delNode->Color=red;
                            rightrotate(delNode);
                            delNode=x->Parent->RChild;
                        }
                        delNode->Color=x->Parent->Color;
                        x->Parent->Color=black;
                        delNode->RChild->Color=black;
                        leftrotate(x->Parent);
                        x=Root;
                    }
            }
            else
            {
                delNode=x->Parent->LChild;
                if(delNode->Color==red)
                    {
                        delNode->Color=black;
                        x->Parent->Color=red;
                        rightrotate(x->Parent);
                        delNode=x->Parent->LChild;
                    }
                    if(delNode->LChild->Color==black && delNode->RChild->Color==black)
                    {
                        delNode->Color=red;
                        x=x->Parent;
                    }
                    else
                    {
                        if(delNode->LChild->Color==black)
                        {
                            delNode->RChild->Color=black;
                            delNode->Color=red;
                            leftrotate(delNode);
                            delNode=x->Parent->LChild;
                        }
                        delNode->Color=x->Parent->Color;
                        x->Parent->Color=black;
                        delNode->LChild->Color=black;
                        rightrotate(x->Parent);
                        x=Root;
                    }
            }
            x->Color=black;
            Root->Color=black;
        }
    }
public:
	RedBlackTree()
	{
		Sential = CreateNode(0);
		Sential->Color = black;
		Root = Sential;
	}
	bool AddElement(int element)
	{
		if (Root == Sential)
		{
			Root = CreateNode(element);
			Root->Color = black;
			return true;
		}
		Node *a, *b;
		a = Root;
		while (a != Sential)
		{
			b = a;
			if (a->Data == element)
				return false;
			if (a->Data < element)
				a = a->RChild;
			else
				a = a->LChild;
		}
		Node *temp = CreateNode(element);
		temp->Parent = b;
		if (b->Data < temp->Data)
			b->RChild = temp;
		else
			b->LChild = temp;
		fixinsert(temp);
		return true;
	}
	bool RemoveElement(int element)
	{
		if(Root==Sential)
            return false;
        if(Contains(element)==false)
            return false;
        else
        {
            Node *temp,*sucessor,*delNode;
            temp=Root;
            while(temp!=Sential)
            {
                if(temp->Data==element)
                    break;
                else if(temp->Data<element)
                    temp=temp->RChild;
                else
                    temp=temp->LChild;
            }    
            if(temp->LChild==Sential || temp->RChild==Sential)
                sucessor=temp;
            else
                sucessor=Sucessor(temp);
            if(sucessor->LChild!=Sential)
                delNode=sucessor->LChild;
            else
            {
                if(sucessor->RChild!=Sential)
                    delNode=sucessor->RChild;
                else
                    delNode=Sential;
            }
            if(delNode!=Sential)
                delNode->Parent=sucessor->Parent;
            if(sucessor->Parent==Sential)
                Root=delNode;
            else
            {
                if(sucessor==sucessor->Parent->LChild)
                    sucessor->Parent->LChild=delNode;
                else
                    sucessor->Parent->RChild=delNode;
            }
            if(sucessor!=temp)
            {
                temp->Color=sucessor->Color;
                temp->Data=sucessor->Data;
            }
            if(sucessor->Color==black)
                fixdelete(delNode);
            return true;    
        }
	}
	bool Contains(int element)
	{
		if (Root == Sential)
			return false;
		Node *traverse = Root;
		while (traverse != Sential)
		{
			if (traverse->Data == element)
				return true;
			else if (traverse->Data < element)
				traverse = traverse->RChild;
			else
				traverse = traverse->LChild;
		}
		return false;
	}
};
void testCase_1()
{
	AbstractBST *tree = new RedBlackTree;

	int inputArray[] = {10, 6, 20, 3, 7, 19, 28, 4, 18, 24};

	for(int i = 0; i < 10; i++)
	{
		int returnType = tree -> AddElement(inputArray[i]);

		if(returnType != true)
		{
			std::cout<<"\nTestcase 1 - Failed";
			return;
		}
	}

	std::cout<<"\nTestcase 1 - Passed";
}

/* Insertion of duplicate element into the Red Black Tree. If the 
insertion fails, the test passes. */
void testCase_2()
{
	AbstractBST *tree = new RedBlackTree;

	int inputArray[] = {10, 9, 8, 7, 6, 5, 5, 4, 3, 2, 1};

	for(int i = 0; i < 11; i++)
	{
		int returnType = tree -> AddElement(inputArray[i]);

		if(i == 6 && returnType != false)
		{
			std::cout<<"\nTestcase 2 - Failed";
			return;
		}	
	}

	std::cout<<"\nTestcase 2 - Passed";
}

/* Searching for an element that is present in the Red Black Tree. 
Test case passes if element is found.*/
void testCase_3()
{
	AbstractBST *tree = new RedBlackTree;

	int inputArray[] = {13, 8, 17, 1, 11, 15, 25, 6, 22, 27};

	for(int i = 0; i < 10; i++)
		tree -> AddElement(inputArray[i]);

	for(int i = 0; i < 10; i++)
	{
		int returnType = tree -> Contains(inputArray[i]);

		if(returnType != true)
		{
			std::cout<<"\nTestcase 3 - Failed";
			return;
		}
	}

	std::cout<<"\nTestcase 3 - Passed";
}

/* Searching for an element that isn't present in the Red Black Tree.
Test case passes if element isn't found. */
void testCase_4()
{
	AbstractBST *tree = new RedBlackTree;

	int inputArray[] = {10, 9, 15, 12, 11, 13};

	for(int i = 0; i < 6; i++)
		tree -> AddElement(inputArray[i]);

	int returnType = tree -> Contains(24);

	if(returnType == true)
		std::cout<<"\nTestcase 4 - Failed";
	else
		std::cout<<"\nTestcase 4 - Passed";
}

/* Deleting an element from the Red Black Tree. If element to be deleted is found,
and is successfully removed, the testcase passes. */
void testCase_5()
{
	AbstractBST *tree = new RedBlackTree;

	int inputArray[] = {8, 10, 9, 20, 19, 24, 19, 17};

	for(int i = 0; i < 6; i++)
		tree -> AddElement(inputArray[i]);

	for(int i = 0; i < 6; i++)
	{
		int returnType = tree -> RemoveElement(inputArray[i]);

		if(returnType != true)
		{
			std::cout<<"\nTestcase 5 - Failed";
			return;
		}
	}

	std::cout<<"\nTestcase 5 - Passed";

}

/* Deleting an element from the Red Black Tree. If element to be deleted
 is not found, the testcase passes. */
void testCase_6()
{
	AbstractBST *tree = new RedBlackTree;

	int inputArray[] = {8, 17, 9, 24, 19, 18};

	for(int i = 0; i < 6; i++)
		tree -> AddElement(inputArray[i]);

	int returnType = tree -> RemoveElement(1);

	if(returnType == true)
		std::cout<<"\nTestcase 6 - Failed";
	else
		std::cout<<"\nTestcase 6 - Passed";
	
}

int main()
{
	
	AbstractBST *tree = new RedBlackTree;
	/*
	testCase_1(); // General Insertion Test
	testCase_2(); // Duplicate Insertion Test
	testCase_3(); // Search of element present in tree
	testCase_4(); // Search of element which isn't present in tree
	testCase_5(); // Deletion of existing element from tree
	testCase_6(); // Deletion of element that isn't there in the tree
	*/
	int d,n,ch=1;
	while(ch){
	cout<<"1. Insert"<<endl;
    cout<<"2. Search"<<endl;
    cout<<"3. Delete"<<endl;
    cout<<"4. Dispaly"<<endl;
    cout<<"Enter choice 1,2,3,4"<<endl;
    cin>>n;
    switch(n)
    {
        case 1: cout<<"Enter Data"<<endl;
                cin>>d;
                cout<<tree -> AddElement(d)<<endl;
                break;
        case 2: cout<<"Enter Data"<<endl;
                cin>>d;
                cout<<tree -> Contains(d)<<endl;
                break;
        case 3: cout<<"Enter Data to delete"<<endl;
                cin>>d;
                cout<<tree -> RemoveElement(d)<<endl;
                break;
        case 4: 
                break;
        default: cout<<"Enter valid Choice"<<endl;
        }
        cout<<"Do you want to continue '1' or '0'"<<endl;
        cin>>ch;
	}
}