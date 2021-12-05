#include <iostream>
#include "../src/RedBlackTree.cpp"
using namespace std;
void PrintMarkdownNode(Node *n)
{
	if (n->Color == red)
		cout << "\tstyle N" << n->Data << "  fill:#600000,color:#ffffff\n";
	else if (n->LChild != nullptr)
		cout << "\tstyle N" << n->Data << "  fill:#000000,color:#ffffff\n";
	if (n->LChild->LChild != nullptr)
	{
		PrintMarkdownNode(n->LChild);
		cout << "\tN" << n->Data << "((" << n->Data << "))-->N" << n->LChild->Data << "((" << n->LChild->Data << "))\n";
	}
	if (n->RChild->LChild != nullptr)
	{
		PrintMarkdownNode(n->RChild);
		cout << "\tN" << n->Data << "((" << n->Data << "))-->N" << n->RChild->Data << "((" << n->RChild->Data << "))\n";
	}
}
void PrintMarkdownGraph(Node *node)
{
	cout << "\n```mermaid\ngraph TD\n";
	PrintMarkdownNode(node);
	cout << "```\n";
}

void TestTreePrinting(int *array, int size)
{
	RedBlackTree tree;
	for (int i = 0; i < size; i++)
		tree.AddElement(array[i]);
	tree.PrintTree(PrintMarkdownGraph);
}