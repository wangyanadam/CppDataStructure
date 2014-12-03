#ifndef _RB_H_
#define _RB_H_

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Tree_Node;

class RB_Tree {
public:
	RB_Tree();
	virtual ~RB_Tree();
	
	void Insert(void *);
	void Delete(int);
	void Display();
	
	void *Min();
	void *Max();
	void *PopMin();
	void *PopMax();
	void *Pop(int);
	void *GetElem(int);
	
	bool Empty() {return num_node <= 0;}
	int Size() {return num_node;}
	
	void *(*Copy)(void *);
	int (*Key)(void *);
	string (*Print)(void *);
	
private:
	Tree_Node *root;
	int num_node;
	
	void Rotate_Left(Tree_Node *);
	void Rotate_Right(Tree_Node *);
	
	void RB_INSERT_FIXUP(Tree_Node *);
	void RB_DELETE_FIXUP(Tree_Node *);
	
	void Display_Subtree(Tree_Node *,string,string,bool);
	void DeleteSubtree(Tree_Node *);
	
	Tree_Node *Find(int);
	Tree_Node *GetTheRoot();
};

class Tree_Node {
public:
	Tree_Node(void *element);
	virtual ~Tree_Node();
	
	Tree_Node *GetLeft();
	Tree_Node *GetRight();
	Tree_Node *GetParent();
	char GetColor();
	void *GetElement();
	int GetKeyValue();
	
	static Tree_Node *GetLeft(Tree_Node *);
	static Tree_Node *GetRight(Tree_Node *);
	static Tree_Node *GetParent(Tree_Node *);
	static char GetColor(Tree_Node *);
	static void *GetElement(Tree_Node *);
	static int GetKeyValue(Tree_Node *);
	
	void SetLeft(Tree_Node *);
	void SetRight(Tree_Node *);
	void SetParent(Tree_Node *);
	void SetColor(char);
	void SetElement(void *);
	void SetKeyValue(int);
	
private:
	friend class RB_Tree;
	
	void *element;
	char color;
	int KeyValue;
	
	Tree_Node *left;
	Tree_Node *right;
	Tree_Node *parent;
};

#endif
