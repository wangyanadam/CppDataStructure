#ifndef _AVL_H_
#define _AVL_H_

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Tree_Node;

class AVL_Tree {
public:
	AVL_Tree();
	virtual ~AVL_Tree();
	
	void Insert(void *);
	void Delete(string);	
	void Augment(string,void *);
	void Display();
	
	void *Pop(string);
	void *Min();
	void *Max();
	void *PopMin();
	void *PopMax();
	void *GetElem(string);
	
	bool Empty() {return num_node <= 0;}
	int Size() {return num_node;}
	int Height() {return tree_height;}
	
	void *(*Copy)(void *);
	string (*Key)(void *);
	string (*Print)(void *);
	
private:
	Tree_Node *root;
	int num_node;
	int tree_height;
	
	void Rotate(Tree_Node *);
	void Display_Subtree(Tree_Node *,string,string,bool);
	void DeleteSubtree(Tree_Node *);
	
	Tree_Node *Find(string);
	Tree_Node *GetTheRoot();
};

class Tree_Node {
public:
	Tree_Node(void *element);
	virtual ~Tree_Node();
	
	Tree_Node *GetLeft();
	Tree_Node *GetRight();
	Tree_Node *GetParent();
	int GetHeight();
	void *GetElement();
	string GetKeyValue();
	
	static Tree_Node *GetLeft(Tree_Node *);
	static Tree_Node *GetRight(Tree_Node *);
	static Tree_Node *GetParent(Tree_Node *);
	static int GetHeight(Tree_Node *);
	static void *GetElement(Tree_Node *);
	static string GetKeyValue(Tree_Node *);
	
	void SetLeft(Tree_Node *);
	void SetRight(Tree_Node *);
	void SetParent(Tree_Node *);
	void SetHeight(int);
	void SetElement(void *);
	void SetKeyValue(string);
	
private:
	friend class AVL_Tree;
	
	void *element;
	int height;
	string KeyValue;
	Tree_Node *left;
	Tree_Node *right;
	Tree_Node *parent;
};

#endif
