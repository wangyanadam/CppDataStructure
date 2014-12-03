#ifndef BINOMIAL_HEAP_CPP
#define BINOMIAL_HEAP_CPP

#include "Binomial_Heap.hpp"

using namespace std;

Binomial_Tree_Node::Binomial_Tree_Node(void *e,int key,int deg) {
	element = e;
	KeyValue = key;
	
	parent = NULL;
	
	for (int i = 0;i < 64;i++) {
		children[i] = NULL;
	}
	
	depth = 0;
	degree = 0;
	max_degree = deg;
}

Binomial_Tree_Node::~Binomial_Tree_Node() {
	
}

int Binomial_Tree_Node::GetDepth(Binomial_Tree_Node *node) {
	if (node == NULL) return -1;
	else return node->depth;
}

int Binomial_Tree_Node::GetDegree(Binomial_Tree_Node *node) {
	if (node == NULL) return -1;
	else return node->degree;
}

int Binomial_Tree_Node::GetMaxDegree(Binomial_Tree_Node *node) {
	if (node == NULL) return -1;
	else return node->max_degree;
}

Binomial_Tree_Node *Binomial_Tree_Node::GetParent(Binomial_Tree_Node *node) {
	if (node == NULL) return NULL;
	else return node->parent;
}

Binomial_Tree_Node *Binomial_Tree_Node::GetChild(Binomial_Tree_Node *node,int idx) {
	if (node == NULL) return NULL;
	else if (idx > node->degree || idx < 1) return NULL;
	else return node->children[idx - 1];
}

int Binomial_Tree_Node::GetKeyValue(Binomial_Tree_Node *node) {
	if (node == NULL) return -1;
	else return node->KeyValue;
}

void *Binomial_Tree_Node::GetElement(Binomial_Tree_Node *node) {
	if (node == NULL) return NULL;
	else return node->element;
}

Binomial_Heap::Binomial_Heap(int degree,Binomial_Tree_Node **new_roots) {
	max_degree = degree;
	
	for (int i = 0;i <= 64;i++) roots[i] = NULL;
	if (new_roots != NULL) for (int i = 0;i <= max_degree;i++) roots[i] = new_roots[i];
	
	DelElem = NULL;
	Print = NULL;
}

Binomial_Heap::~Binomial_Heap() {
	
}

void Binomial_Heap::DeleteTree(Binomial_Tree_Node *node) {
	if (node == NULL) return;
	
	for (int i = 0;i < node->degree;i++) {
		DeleteTree(node->children[i]);
		if (node->children[i] != NULL) delete node->children[i];
	}
}

int Binomial_Heap::GetMaxDegree() {
	return max_degree;
}

Binomial_Tree_Node *Binomial_Heap::GetRoot(int idx) {
	if (idx > max_degree + 1 || idx < 1) return NULL;
	return roots[idx - 1];
}

void Binomial_Heap::ReplaceHeapRoots(Binomial_Tree_Node **new_roots,int degree) {
	if (new_roots != NULL) for (int i = 0;i <= max_degree;i++) roots[i] = new_roots[i];
	max_degree = degree;
}

void *Binomial_Heap::GetMinElem() {
	int min_key = -1;
	int idx = 0;
	int min_idx = 0;
	
	while (idx <= max_degree && roots[idx] == NULL) idx++;
	
	if (idx > max_degree) return NULL;
	
	min_key = Binomial_Tree_Node::GetKeyValue(roots[idx]);
	min_idx = idx;
	
	for (int i = idx + 1;i <= max_degree;i++) {
		if (roots[i] == NULL) continue;
		
		int key = Binomial_Tree_Node::GetKeyValue(roots[i]);
			
		if (min_key > key) {
			min_key = key;
			min_idx = i;
		}
	}
	
	return roots[min_idx]->element;
}

void *Binomial_Heap::PopMinElem() {
	int min_key = -1;
	int idx = 0;
	int min_idx = 0;
	
	while (idx <= max_degree && roots[idx] == NULL) idx++;
	
	if (idx > max_degree) return NULL;
	
	min_key = Binomial_Tree_Node::GetKeyValue(roots[idx]);
	min_idx = idx;
	
	for (int i = idx + 1;i <= max_degree;i++) {
		if (roots[i] == NULL) continue;
		
		int key = Binomial_Tree_Node::GetKeyValue(roots[i]);
		
		if (min_key > key) {
			min_key = key;
			min_idx = i;
		}
	}
	
	void *result = roots[min_idx]->element;
	
	Binomial_Tree_Node **new_roots = new Binomial_Tree_Node *[max_degree + 1];
	for (int i = 0;i <= max_degree;i++) {
		if (i <= roots[min_idx]->degree - 1) {
			new_roots[i] = roots[min_idx]->children[i];
			new_roots[i]->parent = NULL;
		}
		else new_roots[i] = NULL;
	}
	
	Binomial_Heap *heap = new Binomial_Heap(max_degree,new_roots);
	delete [] new_roots;
	delete roots[min_idx];
	roots[min_idx] = NULL;
	Union(heap);
	delete heap;
	
	return result;
}

Binomial_Tree_Node *Binomial_Heap::UpdateKey(Binomial_Tree_Node *node,int new_key) {
	if (node == NULL) return NULL;
	node->KeyValue = new_key;
	
	Binomial_Tree_Node *temp = node;
	int KeyValue_temp;
	void *element_temp;
	
	while (temp->parent != NULL && temp->KeyValue < temp->parent->KeyValue) {
		KeyValue_temp = temp->KeyValue;
		element_temp = temp->element;
		
		temp->KeyValue = temp->parent->KeyValue;
		temp->element = temp->parent->element;
		
		temp->parent->KeyValue = KeyValue_temp;
		temp->parent->element = element_temp;
		
		temp = temp->parent;
	}
	
	bool flag = false;
	int idx = 0;
	for (int i = 0;i < temp->degree && !flag;i++) {
		if (temp->children[i] == NULL) continue;
		if (temp->KeyValue > temp->children[i]->KeyValue) {
			flag = true;
			idx = i;
		}
	}
	
	while (flag) {
		KeyValue_temp = temp->KeyValue;
		element_temp = temp->element;
		
		temp->KeyValue = temp->children[idx]->KeyValue;
		temp->element = temp->children[idx]->element;
		
		temp->children[idx]->KeyValue = KeyValue_temp;
		temp->children[idx]->element = element_temp;
		
		temp = temp->children[idx];
		
		flag = false;
		idx = 0;
		for (int i = 0;i < temp->degree && !flag;i++) {
			if (temp->children[i] == NULL) continue;
			if (temp->KeyValue > temp->children[i]->KeyValue) {
				flag = true;
				idx = i;
			}
		}
	}
	
	return temp;
}

void Binomial_Heap::Union(Binomial_Heap *heap) {
	if (heap->max_degree != max_degree) return;
	
	long num_nodes_heap1 = 0;
	long num_nodes_heap2 = 0;
	long max_nodes = 0;
	
	for (int i = max_degree;i >= 0;i--) {
		max_nodes = 2 * max_nodes + 1;
		
		num_nodes_heap1 = 2 * num_nodes_heap1;
		num_nodes_heap2 = 2 * num_nodes_heap2;
		
		if (roots[i] != NULL) num_nodes_heap1++;
		if (heap->roots[i] != NULL) num_nodes_heap2++;
	}
	
	if (num_nodes_heap1 + num_nodes_heap2 > max_nodes) return;
	
	if (num_nodes_heap2 == 0) return;
	
	struct RootList {
		Binomial_Tree_Node *root;
		struct RootList *next;
	} *root_list_head,*root_list_tail,*root_list_new;
	root_list_head = NULL;
	root_list_tail = NULL;
	
	for (int i = 0;i <= max_degree;i++) {
		if (roots[i] != NULL) {
			root_list_new = new struct RootList;
			root_list_new->root = roots[i];
			root_list_new->next = NULL;
			
			if (root_list_head == NULL) {
				root_list_head = root_list_new;
				root_list_tail = root_list_head;
			}
			else {
				root_list_tail->next = root_list_new;
				root_list_tail = root_list_tail->next;
			}
		}
		
		if (heap->roots[i] != NULL) {
			root_list_new = new struct RootList;
			root_list_new->root = heap->roots[i];
			root_list_new->next = NULL;
			
			if (root_list_head == NULL) {
				root_list_head = root_list_new;
				root_list_tail = root_list_head;
			}
			else {
				root_list_tail->next = root_list_new;
				root_list_tail = root_list_tail->next;
			}
		}
	}
	
	struct RootList *pre = NULL;
	root_list_new = root_list_head;
	root_list_tail = root_list_new->next;
	
	while (root_list_tail != NULL) {
		if (root_list_new->root->degree != root_list_tail->root->degree || (root_list_tail->next != NULL && root_list_tail->next->root->degree == root_list_new->root->degree)) {
			pre = root_list_new;
			root_list_new = root_list_tail;
		}
		else if (root_list_new->root->KeyValue <= root_list_tail->root->KeyValue) {
			root_list_new->next = root_list_tail->next;
			
			root_list_tail->root->parent = root_list_new->root;
			root_list_new->root->degree++;
			root_list_new->root->children[root_list_new->root->degree - 1] = root_list_tail->root;
			
			delete root_list_tail;
		}
		else {
			if (pre == NULL) root_list_head = root_list_tail;
			else pre->next = root_list_tail;
			
			root_list_new->root->parent = root_list_tail->root;
			root_list_tail->root->degree++;
			root_list_tail->root->children[root_list_tail->root->degree - 1] = root_list_new->root;
			
			delete root_list_new;
			
			root_list_new = root_list_tail;
		}
		root_list_tail = root_list_new->next;
	}
	
	for (int i = 0;i <= max_degree;i++) {
		roots[i] = NULL;
	}
	
	pre = root_list_head;
	while (pre != NULL) {
		roots[pre->root->degree] = pre->root;
		
		root_list_new = pre;
		pre = pre->next;
		
		delete root_list_new;
	}
}

void Binomial_Heap::Delete(Binomial_Tree_Node *node) {
	if (node == NULL) return;
	UpdateKey(node,-1);
	void *elem = PopMinElem();
	DelElem(elem);
}

void Binomial_Heap::Insert(Binomial_Tree_Node *new_node) {
	if (new_node == NULL) return;
	
	Binomial_Tree_Node **new_roots = new Binomial_Tree_Node *[max_degree + 1];
	for (int i = 0;i <= max_degree;i++) new_roots[i] = NULL;
	new_roots[0] = new_node;
	
	Binomial_Heap *heap = new Binomial_Heap(max_degree,new_roots);
	Union(heap);
	
	delete [] new_roots;
	delete heap;
}

#endif
