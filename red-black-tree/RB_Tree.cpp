#ifndef _RB_CPP_
#define _RB_CPP_

#include "RB_Tree.hpp"

using namespace std;

RB_Tree::RB_Tree() {
	root = NULL;
	num_node = 0;
	
	Copy = NULL;
	Key = NULL;
	Print = NULL;
}

RB_Tree::~RB_Tree() {
	if (root != NULL) {
		DeleteSubtree(root);
		root = NULL;
	}
}

Tree_Node::Tree_Node(void *elem) {
	element = elem;
	color = 'R';
	left = NULL;
	right = NULL;
	parent = NULL;
	KeyValue = -1;
}

Tree_Node::~Tree_Node() {
	
}

char Tree_Node::GetColor(Tree_Node *in) {
	if (in == NULL) return 0;
	else return in->color;
}

Tree_Node *Tree_Node::GetLeft(Tree_Node *in) {
	if (in == NULL) return NULL;
	else return in->left;
}

Tree_Node *Tree_Node::GetRight(Tree_Node *in) {
	if (in == NULL) return NULL;
	else return in->right;
}

Tree_Node *Tree_Node::GetParent(Tree_Node *in) {
	if (in == NULL) return NULL;
	else return in->parent;
}

void *Tree_Node::GetElement(Tree_Node *in) {
	if (in == NULL) return NULL;
	else return in->element;
}

int Tree_Node::GetKeyValue(Tree_Node *in) {
	if (in == NULL) return -1;
	else return in->KeyValue;
}

char Tree_Node::GetColor() {
	return color;
}

Tree_Node *Tree_Node::GetLeft() {
	return left;
}

Tree_Node *Tree_Node::GetRight() {
	return right;
}

Tree_Node *Tree_Node::GetParent() {
	return parent;
}

void *Tree_Node::GetElement() {
	return element;
}

int Tree_Node::GetKeyValue() {
	return KeyValue;
}

void Tree_Node::SetColor(char in) {
	color = in;
}

void Tree_Node::SetLeft(Tree_Node *in) {
	left = in;
}

void Tree_Node::SetRight(Tree_Node *in) {
	right = in;
}

void Tree_Node::SetParent(Tree_Node *in) {
	parent = in;
}

void Tree_Node::SetElement(void *elem) {
	element = elem;
}

void Tree_Node::SetKeyValue(int s) {
	KeyValue = s;
}

void RB_Tree::Insert(void *element) {
	Tree_Node *new_node;
	
	if (num_node == 0) {
		new_node = new Tree_Node(element);
		new_node->KeyValue = Key(element);
		new_node->color = 'B';
		root = new_node;
		num_node++;
	}
	else {
		Tree_Node *current = root;
		bool flag = true;
		bool duplicate = false;
		
		while (flag) {
			if (current->KeyValue > Key(element)) {
				if (current->left != NULL) current = current->left;
				else {
					new_node = new Tree_Node(element);
					current->left = new_node;
					
					new_node->KeyValue = Key(element);
					new_node->color = 'R';
					
					new_node->parent = current;
					new_node->left = NULL;
					new_node->right = NULL;
					
					num_node++;
					flag = false;
				}
			}
			else if (current->KeyValue < Key(element)){
				if (current->right != NULL) current = current->right;
				else {
					new_node = new Tree_Node(element);
					current->right = new_node;
					
					new_node->KeyValue = Key(element);
					new_node->color = 'R';
					
					new_node->parent = current;
					new_node->left = NULL;
					new_node->right = NULL;
					
					num_node++;
					flag = false;
				}
			}
			else {
				duplicate = true;
				flag = false;
			}
		}
		
		if (duplicate) return;
		
		RB_INSERT_FIXUP(new_node);
	}
}

void RB_Tree::Delete(int keyValue) {	
	Tree_Node *z = Find(keyValue);
	
	if (z == NULL) return;
	
	Tree_Node *y = z;
	if (z->right != NULL && z->left != NULL) {
		y = y->left;
		while (y->right != NULL) y = y->right;
	}
	num_node--;
	
	Tree_Node *x;
	if (y->left != NULL) x = y->left;
	else x = y->right;
	
	if (x == NULL) {
		x = new Tree_Node(NULL);
		x->color = 'B';
	}
	x->parent = y->parent;
	
	if (y->parent == NULL) root = x;
	else if (y->parent->left == y) y->parent->left = x;
	else y->parent->right = x;
	
	if (y != z) {
		z->KeyValue = y->KeyValue;
		z->element = y->element;
	}
	
	if (y->color == 'B') RB_DELETE_FIXUP(x);
	
	if (x->KeyValue == -1) {
		if (root == x) root = NULL;
		else if (x->parent->left == x) x->parent->left = NULL;
		else x->parent->right = NULL;
		
		delete x;
	}
	
	delete y;
	
	return;
}

void *RB_Tree::Pop(int keyValue) {
	void *result = Find(keyValue)->element;
	
	Delete(keyValue);
	
	return result;
}

Tree_Node *RB_Tree::Find(int keyValue) {
	Tree_Node *node = root;
	bool found = false;
	while (node != NULL && !found) {
		if (node->KeyValue == keyValue) found = true;
		else if (node->KeyValue < keyValue) node = node->right;
		else node = node->left;
	}
	
	return node;
}

void RB_Tree::RB_INSERT_FIXUP(Tree_Node *z) {
	while (z->parent != NULL && z->parent->color == 'R') {
		if (z->parent->parent->left == z->parent) {
			Tree_Node *y = z->parent->parent->right;
			
			if (y != NULL && y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				
				z = z->parent->parent;
			}
			else if (z == z->parent->right) {
				z = z->parent;
				Rotate_Left(z);
			}
			else {
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				Rotate_Right(z->parent->parent);
			}
		}
		else {
			Tree_Node *y = z->parent->parent->left;
			
			if (y != NULL && y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				
				z = z->parent->parent;
			}
			else if (z == z->parent->left) {
				z = z->parent;
				Rotate_Right(z);
			}
			else {
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				Rotate_Left(z->parent->parent);
			}
		}
	}
	
	root->color = 'B';
}

void RB_Tree::RB_DELETE_FIXUP(Tree_Node *x) {
	while (x != root && x->color == 'B') {
		if (x == x->parent->left) {
			Tree_Node *w = x->parent->right;
			
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				Rotate_Left(x->parent);
			}
			else if ((w->left == NULL || w->left->color == 'B') && (w->right == NULL || w->right->color == 'B')) {
				w->color = 'R';
				x = x->parent;
			}
			else if ((w->left != NULL && w->left->color == 'R') && (w->right == NULL || w->right->color == 'B')) {
				if (w->left != NULL) w->left->color = 'B';
				w->color = 'R';
				Rotate_Right(w);
			}
			else {
				w->color = x->parent->color;
				x->parent->color = 'B';
				if (w->right != NULL) w->right->color = 'B';
				Rotate_Left(x->parent);
				x = root;
			}
		}
		else {
			Tree_Node *w = x->parent->left;
			
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				Rotate_Right(x->parent);
			}
			else if ((w->right == NULL || w->right->color == 'B') && (w->left == NULL || w->left->color == 'B')) {
				w->color = 'R';
				x = x->parent;
			}
			else if ((w->right != NULL && w->right->color == 'R') && (w->left == NULL || w->left->color == 'B')) {
				if (w->right != NULL) w->right->color = 'B';
				w->color = 'R';
				Rotate_Left(w);
			}
			else {
				w->color = x->parent->color;
				x->parent->color = 'B';
				if (w->left != NULL) w->left->color = 'B';
				Rotate_Right(x->parent);
				x = root;
			}
		}
	}
	
	x->color = 'B';
}

Tree_Node *RB_Tree::GetTheRoot() {
	if (num_node == 0) return NULL;
	else return root;
}

void RB_Tree::Rotate_Left(Tree_Node *x) {
	if (x == NULL || x->right == NULL) return;
	
	Tree_Node *y = x->right;
	x->right = y->left;
	if (y->left != NULL) y->left->parent = x;
	
	y->parent = x->parent;
	if (x->parent == NULL) root = y;
	else if (x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;
	
	y->left = x;
	x->parent = y;
}

void RB_Tree::Rotate_Right(Tree_Node *x) {
	if (x == NULL || x->left == NULL) return;
	
	Tree_Node *y = x->left;
	x->left = y->right;
	if (y->right != NULL) y->right->parent = x;
	
	y->parent = x->parent;
	if (x->parent == NULL) root = y;
	else if (x->parent->right == x) x->parent->right = y;
	else x->parent->left = y;
	
	y->right = x;
	x->parent = y;
}

void RB_Tree::Display() {
	if (root != NULL) {
		cout << Print(root->GetElement());
		cout << " (" << root->GetColor() << ")" << endl;
	}
	else cout << "(EMPTY)" << endl;
	if (root != NULL) {
		Display_Subtree(root->left,""," +-- ",false);
		Display_Subtree(root->right,""," \\-- ",true);
	}
}

void RB_Tree::Display_Subtree(Tree_Node *node,string pre1,string pre2,bool last) {	
	if (node != NULL) {
		cout << pre1 << pre2 << Print(node->element);
		cout << " (" << node->GetColor() << ")" << endl;
	}
	else cout << pre1 << pre2 << "NULL" << endl;
	
	if (node != NULL) {
		if (!last) pre1 = pre1 + " |   ";
		else pre1 = pre1 + "     ";
		pre2 = " +-- ";
		Display_Subtree(node->left,pre1,pre2,false);
		pre2 = " \\-- ";
		Display_Subtree(node->right,pre1,pre2,true);
	}
}

void RB_Tree::DeleteSubtree(Tree_Node *in) {
	if (in->left != NULL) DeleteSubtree(in->left);
	if (in->right != NULL) DeleteSubtree(in->right);
	delete in;
}

void *RB_Tree::Min() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->left != NULL) node = node->left;
	
	return Copy(node->element);
}

void *RB_Tree::Max() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->right != NULL) node = node->right;
	
	return Copy(node->element);
}

void *RB_Tree::PopMin() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->left != NULL) node = node->left;
	int keyValue = node->KeyValue;
	
	return Pop(keyValue);
}

void *RB_Tree::PopMax() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->right != NULL) node = node->right;
	int keyValue = node->KeyValue;
	
	return Pop(keyValue);
}

void *RB_Tree::GetElem(int keyValue) {
	Tree_Node *node = Find(keyValue);
	
	if (node == NULL) return NULL;
	
	return Copy(node->element);
}

#endif
