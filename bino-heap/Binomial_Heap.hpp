#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Binomial_Tree_Node {
public:
	Binomial_Tree_Node(void *,int,int);
	virtual ~Binomial_Tree_Node();
	
	static int GetDepth(Binomial_Tree_Node *);
	static int GetDegree(Binomial_Tree_Node *);
	static int GetMaxDegree(Binomial_Tree_Node *);
	
	static Binomial_Tree_Node *GetParent(Binomial_Tree_Node *);
	static Binomial_Tree_Node *GetChild(Binomial_Tree_Node *,int);
	
	static int GetKeyValue(Binomial_Tree_Node *);
	static void *GetElement(Binomial_Tree_Node *);
	
private:
	friend class Binomial_Heap;
	
	int depth;
	int degree;
	int max_degree;
	
	Binomial_Tree_Node *parent;
	Binomial_Tree_Node *children[64];
	
	int KeyValue;
	void *element;
};

class Binomial_Heap {
public:
	Binomial_Heap(int,Binomial_Tree_Node **);
	virtual ~Binomial_Heap();
	
	int GetMaxDegree();
	Binomial_Tree_Node *GetRoot(int);
	void ReplaceHeapRoots(Binomial_Tree_Node **,int);
	
	void *GetMinElem();
	void *PopMinElem();
	void Insert(Binomial_Tree_Node *);
	
	Binomial_Tree_Node *UpdateKey(Binomial_Tree_Node *,int);
	void Union(Binomial_Heap *);
	void Delete(Binomial_Tree_Node *);
	
	void (*DelElem)(void *);
	string (*Print)(void *);
	int (*Key)(void *);
	
private:
	int max_degree;
	Binomial_Tree_Node *roots[65];
	void DeleteTree(Binomial_Tree_Node *);
};

#endif
