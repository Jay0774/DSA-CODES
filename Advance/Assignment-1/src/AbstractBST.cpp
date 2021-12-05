/**
 * @brief The Node structure to use within the Tree
 * 
 */
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