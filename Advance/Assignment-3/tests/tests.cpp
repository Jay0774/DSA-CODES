#include "../src/MaxFlow_MPM_Heap.cpp"
#include <string>

void RunTest(int TestId, string TestDescription, string Expected, string Actual)
{
	cout << "\nStarting Test #" << TestId << ":" << TestDescription << "\n";
	if (Expected.compare(Actual) == 0)
		cout << "Test #" << TestId << " has passed successfully.";
	else
		cout << "Test #" << TestId << " has failed.\nExpected: \n"
			 << Expected << "\n\nActual:\n"
			 << Actual;
}

string GetIntArrayString(int *x, int size)
{
	string z = "[ ";
	for (int i = 0; i < size; i++)
	{
		z.append(to_string(x[i]));
		z.append(", ");
	}
	z.append("]");
	return z;
}

string GetQueueString(Queue &x)
{
	string z = "[ ";
	QueueNode *node = x.GetFront();
	while (node != nullptr)
	{
		z.append(to_string(node->Data));
		z.append(", ");
		node = node->Next;
	}
	z.append("]");
	return z;
}