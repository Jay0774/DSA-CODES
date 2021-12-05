#include "BTreeNode.cpp"
#include "M21CS003_M21CS001_M21CS007-td_insert.cpp"
#include "M21CS003_M21CS001_M21CS007-bu_insert.cpp"
#include "M21CS003_M21CS001_M21CS007-td_delete.cpp"
#include "M21CS003_M21CS001_M21CS007-bu_delete.cpp"
/**
 * @brief B-Tree implementation: 2-3-4 Tree storing integers
 * 
 */
class BTree
{
	BTreeNode *Root;
	int Count;
public:
	/**
	 * @brief Construct a new BTree object
	 * 
	 */
	BTree()
	{
		Root = CreateNode();
		Count = 0;
	}
	/**
	 * @brief Get the number of items inserted in this BTree
	 * 
	 * @return int 
	 */
	int GetCount()
	{
		return Count;
	}
	/**
	 * @brief Inserts an item using the Top-Down Approach
	 * 
	 * @param item The item to insert
	 * @return bool: Denotes if the insertion was successful
	 */
	bool Insert_TopDown(int item)
	{
		bool res = td_insert(Root, item);
		if(res)Count++;
		return res;
	}
	/**
	 * @brief Inserts an item using the Bottom-Up Approach
	 * 
	 * @param item The item to insert
	 * @return bool: Denotes if the insertion was successful
	 */
	bool Insert_BottomUp(int item)
	{
		bool res = bu_insert(Root, item);
		if(res)Count++;
		return res;
	}
	/**
	 * @brief Deletes an item using the Top-Down approach
	 * 
	 * @param item The item to delete from the Tree
	 * @return bool Denotes if the deletion is successful
	 */
	bool Delete_TopDown(int item)
	{
		bool res = td_delete(Root, item);
		if(res)Count--;
		return res;
	}
	/**
	 * @brief Deletes an item using the Bottom-Up approach
	 * 
	 * @param item The item to delete from the Tree
	 * @return bool Denotes if the deletion is successful
	 */
	bool Delete_BottomUp(int item)
	{
		bool res =  bu_delete(Root, item);
		if(res)Count--;
		return res;
	}
	/**
	 * @brief Searches for a given item within the BTree
	 * 
	 * @param item The item to search
	 * @return bool: True if item is found, False otherwise
	 */
	bool Contains(int item)
	{
		BTreeNode *z = Root;
		int result;
		BTreeNode *x = SearchNode(z, item, result);
		return result!=-1;
	}
	BTreeNode* getRoot()
	{
		return Root;//delete this
	}
};