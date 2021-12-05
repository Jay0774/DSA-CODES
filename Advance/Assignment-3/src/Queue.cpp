/**
 * @brief Represents single node of a queue
 * 
 */
struct QueueNode
{
	/**
	 * @brief The data element of the node
	 * 
	 */
	int Data;
	/**
	 * @brief The next pointer of the node
	 * 
	 */
	QueueNode *Next;
};
/**
 * @brief Creates a new node
 * 
 * @param value The value to insert in the node
 * @return QueueNode* The reference of the created node
 */
QueueNode *Create(int value)
{
	QueueNode *node = new QueueNode;
	node->Next = nullptr;
	node->Data = value;
	return node;
}
/**
 * @brief Structure to manage a queue of nodes
 * 
 */
class Queue
{
	QueueNode *Front, *Tail;
	unsigned int Size;

public:
	/**
	 * @brief Construct a new Queue object
	 * 
	 */
	Queue()
	{
		Front = Tail = nullptr;
		Size = 0;
	}
	/**
	 * @brief Adds an element at the End of the queue
	 * 
	 * @param value The element to add
	 */
	void Push(int value)
	{
		QueueNode *node = Create(value);
		if (Front == nullptr)
			Front = Tail = node;
		else
		{
			Tail->Next = node;
			Tail = node;
		}
		Size++;
	}
	/**
	 * @brief Adds an element at the beginning of the queue
	 * 
	 * @param value 
	 */
	void Insert(int value)
	{
		QueueNode *node = Create(value);
		if (Front == nullptr)
			Front = Tail = node;
		else
		{
			node->Next=Front;
			Front=node;
		}
		Size++;
	}
	/**
	 * @brief Returns the value at the top of the queue
	 * 
	 * @return int 
	 */
	int Top()
	{
		if (Size == 0)
			return 0;
		else
			return Front->Data;
	}
	/**
	 * @brief Deletes an element from the Queue
	 * 
	 * @return bool Denotes wheter the deletion was successful or not
	 */
	bool Pop()
	{
		if (Tail == nullptr)
			return false;
		else if (Tail == Front)
		{
			delete Front;
			Tail = Front = nullptr;
		}
		else
		{
			QueueNode *node = Front;
			Front = Front->Next;
			delete node;
		}
		Size--;
		return true;
	}
	/**
	 * @brief Get the Size of the queue
	 * 
	 * @return int 
	 */
	int GetSize()
	{
		return Size;
	}
	/**
	 * @brief Get the Front node
	 * 
	 * @return QueueNode* 
	 */
	QueueNode* GetFront()
	{
		return Front;
	}
};