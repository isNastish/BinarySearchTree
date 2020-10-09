#include <iostream>
#include "HeaderTree.h"
#define ll long long

using std::cout;
using std::cin;
using std::endl;

class Bintree
{
private:
	struct node
	{
		char* fullN;
		ll int number;
		struct node* left_node;
		struct node* right_node;
		struct node* parent;
	}*rootN;

	//Distruct tree.
	
	void distructTree(struct node* rootP)
	{
		if (rootP != NULL)
		{
			distructTree(rootP->left_node);
			distructTree(rootP->right_node);

			//when leave the node! not beetwen recursive calls!
			free(rootP->fullN);
			rootP->fullN = nullptr;
			free(rootP);
			rootP = nullptr;
			
		}
	}

	//Push function.
	struct node* push(struct node* rootP, char* fullN, ll int number)
	{
		if (NULL == rootP)
		{
			rootP = (struct node*)malloc(sizeof(struct node));
			rootP->fullN = alloc(fullN);
			rootP->number = number;
			rootP->right_node = rootP->left_node = rootP->parent = NULL;
		}
		else if (mystrcmp(rootP->fullN, fullN) > 0)
		{
			rootP->left_node = push(rootP->left_node, fullN, number);
			rootP->left_node->parent = rootP;
		}
		else
		{
			rootP->right_node = push(rootP->right_node, fullN, number);
			rootP->right_node->parent = rootP;
		}
		return rootP;
	}

	//Print function.
	void print(struct node* rootP)
	{
		if (rootP != NULL)
		{
			print(rootP->left_node);
			cout << rootP->fullN << ": " << rootP->number << endl;
			print(rootP->right_node);
		}
	}

	//Seaarch
	struct node* search(struct node* rootP, char* key)
	{
		int temp = mystrcmp(rootP->fullN, key);
		if (NULL == rootP || temp == 0)
			return rootP;
		else if (temp > 0)
			return search(rootP->left_node, key);
		else
			return search(rootP->right_node, key);
	}

	//Min - node with min value.
	struct node* treeMin(struct node* rootP)
	{
		while (rootP->left_node != NULL) rootP = rootP->left_node;
		return rootP;
	}

	//Max - node with max value.
	struct node* treeMax(struct node* rootP)
	{
		while (rootP->right_node != NULL) rootP = rootP->right_node;
		return rootP;
	}

	//Successor
	struct node* successor(struct node* sourceP)
	{
		if (sourceP->right_node != NULL)
			return treeMin(sourceP->right_node);
		struct node* parentTmp = sourceP->parent;
		while (parentTmp != NULL && sourceP == parentTmp->right_node)
		{
			sourceP = parentTmp;
			parentTmp = parentTmp->parent;
		}
		return parentTmp;
	}

	//Predecessor
	struct node* predecessor(struct node* sourceP)
	{
		if (sourceP->left_node != NULL)
			return treeMax(sourceP->left_node);
		struct node* parentTmp = sourceP->parent;
		while (parentTmp != NULL && sourceP == parentTmp->left_node)
		{
			sourceP = parentTmp;
			parentTmp = parentTmp->parent;
		}
		return parentTmp;
	}

	//Transplant - deleteN supporting function.
	void transplant(struct node* rootP, struct node* sourceP, struct node* sourceBranch)
	{
		//replace two branches
		if (NULL == sourceP->parent) // if sourceP - root too.
			rootP = sourceBranch;
		else if (sourceP == sourceP->parent->left_node) // if sourceP - left child of his parent.
			sourceP->parent->left_node = sourceBranch;
		else sourceP->parent->right_node = sourceBranch; // if sourceP - right child of his parent.
		if (sourceBranch != NULL) // if sourceP right child != NULL.
			sourceBranch->parent = sourceP->parent;
	}

	//Deleting - function that deletes given node!
	void deleteN(struct node* rootP, struct node *sourceP)
	{
		if (NULL == sourceP->left_node)
			transplant(rootP, sourceP, sourceP->right_node);
		else if (NULL == sourceP->right_node)
			transplant(rootP, sourceP, sourceP->left_node);
		else
		{
			struct node* tempP = treeMin(sourceP->right_node);
			if (tempP->parent != sourceP)
			{
				tempP->right_node = sourceP->right_node;
				tempP->right_node->parent = tempP;
			}
			transplant(rootP, sourceP, tempP);
			tempP->left_node = sourceP->left_node;
			tempP->left_node->parent = tempP;
		}
	}

public:
	Bintree() { rootN = NULL; }
	void push(char* key, ll int number) {rootN = push(rootN, key, number);}
	void print() { print(rootN); }
	void treeMin()
	{
		struct node* tempP = treeMin(rootN);
		if (!tempP) cout << "Wasn't found!\n";
		else cout << tempP->fullN << ": " << "+380" << tempP->number << endl;;
	}
	void treeMax()
	{
		struct node* tempP = treeMax(rootN);
		if (!tempP) cout << "Wasn't found\n";
		else cout << tempP->fullN << ": " << "+380" << tempP->number << endl;
	}
	void search(char* key)
	{
		struct node* tempP = search(rootN, key);
		if (!tempP) cout << "Wasn't found!\n";
		else cout << tempP->fullN << ": " << "+380" << tempP->number << endl;
	}
	void successor(char *key)
	{
		struct node* tempP = search(rootN, key);
		if (!tempP) cout << "Don't exist!\n";
		else
		{
			struct node* succP = successor(tempP);
			if (!succP) { cout << "This node doesn't have successor!\n"; return; } // we trying to find successor of the biggest value.
			cout << succP->fullN << ": " << "+380" << succP->number << endl;
		}
	}
	void predecessor(char* key)
	{
		struct node* tempP = search(rootN, key);
		if (!tempP) cout << "Don't exist!\n";
		else
		{
			struct node* predcP = predecessor(tempP);
			if (!predcP) { cout << "This node doesn't have predecessor!\n"; return; } //we trying to predecessor of the smallest value.
			cout << predcP->fullN << ": " << "+380" << predcP->number << endl;
		}
	}
	void deleteN(char *key)
	{
		struct node* todeleteN = search(rootN, key);
		if (!todeleteN) cout << "Node wasn't found!\n";
		else deleteN(rootN, todeleteN);
	}
	//NOTE don't forget to free memory!
	~Bintree() 
	{ 
		distructTree(rootN); 
		rootN = nullptr;
		if (!rootN) cout << "The tree was destroyed!\n";
	}
	
};

//Test
void treeTest(Bintree &T)
{
	/*
	 Test function, you can test here whatever you want,
	 but this is my way of testing binary search tree!
	*/
	int i = 4;
	char fullN[NAME_LEN];
	while (i)
	{
		ll int num;
		int len = getline(fullN);
		cout << "num: ";
		cin >> num;
		cin.ignore();
		T.push(fullN, num);
		--i;
	}
	cout << "\n\n";

	//Print all elements.
	T.print();

	cout << "\n\n";
	getline(fullN);
	T.search(fullN);

	//Min, Max nodes.
	T.treeMin();
	T.treeMax();

	//Successor, predecessor.
	cout << "\n\n";
	getline(fullN);
	T.successor(fullN);
	T.predecessor(fullN);

	//Delete node by key.
	cout << "\n\n";
	getline(fullN);
	T.deleteN(fullN);

	//Final Print
	cout << "\n\n";
	T.print();

	cout << "\n\n";

}

int main()
{
	Bintree T;
	treeTest(T);
	return 0;
}