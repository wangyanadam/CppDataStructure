#ifndef _AVL_CPP_
#define _AVL_CPP_

#include "AVL_Tree.hpp"

using namespace std;

AVL_Tree::AVL_Tree() {
	root = NULL;
	num_node = 0;
	tree_height = 0;
	Copy = NULL;
	Key = NULL;
	Print = NULL;
}

AVL_Tree::~AVL_Tree() {
	if (root != NULL) {
		DeleteSubtree(root);
		root = NULL;
	}
}

Tree_Node::Tree_Node(void *elem) {
	element = elem;
	height = 1;
	left = NULL;
	right = NULL;
	parent = NULL;
	KeyValue = "";
}

Tree_Node::~Tree_Node() {
	
}

int Tree_Node::GetHeight(Tree_Node *in) {
	if (in == NULL) return 0;
	else return in->height;
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

string Tree_Node::GetKeyValue(Tree_Node *in) {
	if (in == NULL) return "";
	else return in->KeyValue;
}

int Tree_Node::GetHeight() {
	return height;
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

string Tree_Node::GetKeyValue() {
	return KeyValue;
}

void Tree_Node::SetHeight(int in) {
	height = in;
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

void Tree_Node::SetKeyValue(string s) {
	KeyValue = s;
}

void AVL_Tree::Insert(void *element) {
	Tree_Node *new_node;
	
	if (num_node == 0) {
		new_node = new Tree_Node(element);
		new_node->KeyValue = Key(element);
		root = new_node;
		num_node++;
	}
	else {
		Tree_Node *current = root;
		bool flag = true;
		bool duplicate = false;
		while (flag) {
			if (current->KeyValue.compare(Key(element)) > 0) {
				if (current->left != NULL) current = current->left;
				else {
					new_node = new Tree_Node(element);
					new_node->KeyValue = Key(element);
					current->left = new_node;
					new_node->parent = current;
					new_node->left = NULL;
					new_node->right = NULL;
					num_node++;
					flag = false;
				}
			}
			else if (current->KeyValue.compare(Key(element)) < 0){
				if (current->right != NULL) current = current->right;
				else {
					new_node = new Tree_Node(element);
					new_node->KeyValue = Key(element);
					current->right = new_node;
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
		
		Tree_Node *parent_node = new_node->parent;
		Tree_Node *pre_node = new_node;
		int left_height = Tree_Node::GetHeight(parent_node->left);
		int right_height = Tree_Node::GetHeight(parent_node->right);
		bool balanced = false;
		while (!balanced && parent_node != NULL && left_height - right_height < 2 && right_height - left_height <2) {
			int height_update;
			
			if (left_height > right_height) height_update = left_height + 1;
			else height_update = right_height + 1;
			
			if (height_update == parent_node->height) balanced = true;
			else parent_node->height = height_update;
			
			pre_node = parent_node;
			parent_node = parent_node->parent;
			if (parent_node != NULL) {
				left_height = Tree_Node::GetHeight(parent_node->left);
				right_height = Tree_Node::GetHeight(parent_node->right);
			}
		}
		
		if (!balanced && pre_node != root && pre_node == parent_node->left && Tree_Node::GetHeight(pre_node->left) >= Tree_Node::GetHeight(pre_node->right)) Rotate(pre_node);
		else if (!balanced && pre_node != root && pre_node == parent_node->left && Tree_Node::GetHeight(pre_node->left) < Tree_Node::GetHeight(pre_node->right)) {
			Tree_Node *rot = pre_node->right;
			Rotate(rot);
			Rotate(rot);
		}
		else if (!balanced && pre_node != root && pre_node == parent_node->right && Tree_Node::GetHeight(pre_node->left) > Tree_Node::GetHeight(pre_node->right)) {
			Tree_Node *rot = pre_node->left;
			Rotate(rot);
			Rotate(rot);
		}
		else if (!balanced && pre_node != root && pre_node == parent_node->right && Tree_Node::GetHeight(pre_node->left) <= Tree_Node::GetHeight(pre_node->right)) Rotate(pre_node);
		else ;
	}
	
	tree_height = Tree_Node::GetHeight(root);
}

void AVL_Tree::Delete(string keyValue) {	
	Tree_Node *node = Find(keyValue);
	
	if (node == NULL) return;
	
	Tree_Node *successor = node;
	if (successor->right != NULL) {
		successor = successor->right;
		while (successor->left != NULL) successor = successor->left;
	}
	num_node--;
	
	Tree_Node *begin;
	if (successor->right != NULL) {
		begin = successor->right;
		if (successor->parent != NULL) {
			if (successor->parent->left == successor) successor->parent->left = begin;
			else successor->parent->right = begin;
		}
		begin->parent = successor->parent;
		if (begin != NULL && begin->parent == NULL) root = begin;
		begin->height = 1;
		begin = begin->parent;
	}
	else if (successor->left != NULL) {
		begin = successor->left;
		if (successor->parent != NULL) {
			if (successor->parent->left == successor) successor->parent->left = begin;
			else successor->parent->right = begin;
		}
		begin->parent = successor->parent;
		if (begin != NULL && begin->parent == NULL) root = begin;
		begin->height = 1;
		begin = begin->parent;
	}
	else {
		begin = successor->parent;
		if (begin != NULL) {
			if (begin->left == successor) {
				begin->left = NULL;
			}
			else if (begin->right == successor) {
				begin->right = NULL;
			}
		}
		if (begin != NULL && begin->parent == NULL) root = begin;
	}
	
	if (successor == node) {
		delete successor;
		successor = NULL;
	}
	else {
		node->element = successor->element;
		node->KeyValue = successor->KeyValue;
		delete successor;
		successor = NULL;
	}
	
	bool balanced = false;
	int old_height;
	
	while (begin != NULL && !balanced) {
		int height_b_right = Tree_Node::GetHeight(begin->right);
		int height_b_left = Tree_Node::GetHeight(begin->left);
		int height_update;
		
		if (height_b_right > height_b_left) height_update = height_b_right + 1;
		else height_update = height_b_left + 1;
		
		old_height = begin->height;
		begin->height = height_update;

		if (height_b_left - height_b_right > 1) {
			if (Tree_Node::GetHeight(begin->left->left) >= Tree_Node::GetHeight(begin->left->right)) {
				Tree_Node *rot = begin->left;
				Rotate(rot);
				begin = rot;
			}
			else if (Tree_Node::GetHeight(begin->left->right) > Tree_Node::GetHeight(begin->left->left)) {
				Tree_Node *rot = begin->left->right;
				Rotate(rot);
				Rotate(rot);
				begin = rot;
			}
			else;
		}
		else if (height_b_right - height_b_left > 1) {
			if (Tree_Node::GetHeight(begin->right->right) >= Tree_Node::GetHeight(begin->right->left)) {
				Tree_Node *rot = begin->right;
				Rotate(rot);
				begin = rot;
			}
			else if (Tree_Node::GetHeight(begin->right->left) > Tree_Node::GetHeight(begin->right->right)) {
				Tree_Node *rot = begin->right->left;
				Rotate(rot);
				Rotate(rot);
				begin = rot;
			}
		}
		
		if (old_height == begin->height) balanced = true;
		
		begin = begin->parent;
	}
	
	if (num_node == 0) root = NULL;	
	tree_height = Tree_Node::GetHeight(root);
}

Tree_Node *AVL_Tree::Find(string keyValue) {
	Tree_Node *node = root;
	bool found = false;
	while (node != NULL && !found) {
		if (node->KeyValue.compare(keyValue) == 0) found = true;
		else if (node->KeyValue.compare(keyValue) < 0) node = node->right;
		else node = node->left;
	}
	
	return node;
}

void AVL_Tree::Augment(string keyValue,void *newElem) {
	Delete(keyValue);
	Insert(newElem);
}

Tree_Node *AVL_Tree::GetTheRoot() {
	if (num_node == 0) return NULL;
	else return root;
}

void *AVL_Tree::Pop(string keyValue) {
	Tree_Node *node = Find(keyValue);
	
	if (node == NULL) return NULL;
	
	void *resultElem = node->element;
	
	Tree_Node *successor = node;
	if (successor->right != NULL) {
		successor = successor->right;
		while (successor->left != NULL) successor = successor->left;
	}
	num_node--;
	
	Tree_Node *begin;
	if (successor->right != NULL) {
		begin = successor->right;
		if (successor->parent != NULL) {
			if (successor->parent->left == successor) successor->parent->left = begin;
			else successor->parent->right = begin;
		}
		begin->parent = successor->parent;
		if (begin != NULL && begin->parent == NULL) root = begin;
		begin->height = 1;
		begin = begin->parent;
	}
	else if (successor->left != NULL) {
		begin = successor->left;
		if (successor->parent != NULL) {
			if (successor->parent->left == successor) successor->parent->left = begin;
			else successor->parent->right = begin;
		}
		begin->parent = successor->parent;
		if (begin != NULL && begin->parent == NULL) root = begin;
		begin->height = 1;
		begin = begin->parent;
	}
	else {
		begin = successor->parent;
		if (begin != NULL) {
			if (begin->left == successor) {
				begin->left = NULL;
			}
			else if (begin->right == successor) {
				begin->right = NULL;
			}
		}
		if (begin != NULL && begin->parent == NULL) root = begin;
	}
	
	if (successor == node) {
		delete successor;
		successor = NULL;
	}
	else {
		node->element = successor->element;
		node->KeyValue = successor->KeyValue;
		delete successor;
		successor = NULL;
	}
	
	bool balanced = false;
	int old_height;
	
	while (begin != NULL && !balanced) {
		int height_b_right = Tree_Node::GetHeight(begin->right);
		int height_b_left = Tree_Node::GetHeight(begin->left);
		int height_update;
		
		if (height_b_right > height_b_left) height_update = height_b_right + 1;
		else height_update = height_b_left + 1;
		
		old_height = begin->height;
		begin->height = height_update;

		if (height_b_left - height_b_right > 1) {
			if (Tree_Node::GetHeight(begin->left->left) >= Tree_Node::GetHeight(begin->left->right)) {
				Tree_Node *rot = begin->left;
				Rotate(rot);
				begin = rot;
			}
			else if (Tree_Node::GetHeight(begin->left->right) > Tree_Node::GetHeight(begin->left->left)) {
				Tree_Node *rot = begin->left->right;
				Rotate(rot);
				Rotate(rot);
				begin = rot;
			}
			else;
		}
		else if (height_b_right - height_b_left > 1) {
			if (Tree_Node::GetHeight(begin->right->right) >= Tree_Node::GetHeight(begin->right->left)) {
				Tree_Node *rot = begin->right;
				Rotate(rot);
				begin = rot;
			}
			else if (Tree_Node::GetHeight(begin->right->left) > Tree_Node::GetHeight(begin->right->right)) {
				Tree_Node *rot = begin->right->left;
				Rotate(rot);
				Rotate(rot);
				begin = rot;
			}
		}
		
		if (old_height == begin->height) balanced = true;
		
		begin = begin->parent;
	}
	
	if (num_node == 0) root = NULL;	
	tree_height = Tree_Node::GetHeight(root);
	
	return resultElem;
}

void AVL_Tree::Rotate(Tree_Node *node) {
	if (node != root) {
		Tree_Node *parent_node = node->parent;
		int height_p_left, height_p_right;
		int height_n_left, height_n_right;
		
		if (parent_node->right == node) {
			parent_node->right = node->left;
			node->left = parent_node;
			node->parent = parent_node->parent;
			if (parent_node != root) {
				if (parent_node->parent->right == parent_node) parent_node->parent->right = node;
				else parent_node->parent->left = node;
			}
			parent_node->parent = node;
			if (parent_node->right != NULL) {
				parent_node->right->parent = parent_node;
			}
			
			if (parent_node->right != NULL) height_p_right = parent_node->right->height;
			else height_p_right = 0;
			
			if (parent_node->left != NULL) height_p_left = parent_node->left->height;
			else height_p_left = 0;
			
			if (height_p_right > height_p_left) {
				parent_node->height = height_p_right + 1;
			}
			else {
				parent_node->height = height_p_left + 1;
			}
			
			if (node->right != NULL) height_n_right = node->right->height;
			else height_n_right = 0;
			
			if (node->left != NULL) height_n_left = node->left->height;
			else height_n_left = 0;			
			
			if (height_n_right > height_n_left) {
				node->height = height_n_right + 1;
			}
			else {
				node->height = height_n_left + 1;
			}
		}
		else {
			parent_node->left = node->right;
			node->right = parent_node;
			node->parent = parent_node->parent;
			if (parent_node != root) {
				if (parent_node->parent->right == parent_node) parent_node->parent->right = node;
				else parent_node->parent->left = node;
			}
			parent_node->parent = node;
			if (parent_node->left != NULL) {
				parent_node->left->parent = parent_node;
			}

			if (parent_node->right != NULL) height_p_right = parent_node->right->height;
			else height_p_right = 0;

			if (parent_node->left != NULL) height_p_left = parent_node->left->height;
			else height_p_left = 0;

			if (height_p_right > height_p_left) {
				parent_node->height = height_p_right + 1;
			}
			else {
				parent_node->height = height_p_left + 1;
			}

			if (node->right != NULL) height_n_right = node->right->height;
			else height_n_right = 0;

			if (node->left != NULL) height_n_left = node->left->height;
			else height_n_left = 0;

			if (height_n_right > height_n_left) {
				node->height = height_n_right + 1;
			}
			else {
				node->height = height_n_left + 1;
			}
		}
	}
	
	if (node->parent == NULL) root = node;
}

void AVL_Tree::Display() {
	if (root != NULL) {
		cout << Print(root->GetElement());
		if (Tree_Node::GetHeight(root->left) == Tree_Node::GetHeight(root->right)) cout << " (E)" << endl;
		else if (Tree_Node::GetHeight(root->left) > Tree_Node::GetHeight(root->right)) cout << " (L)" << endl;
		else cout << " (R)" << endl;
	}
	else cout << "(EMPTY)" << endl;
	if (root != NULL) {
		Display_Subtree(root->left,""," +-- ",false);
		Display_Subtree(root->right,""," \\-- ",true);
	}
}

void AVL_Tree::Display_Subtree(Tree_Node *node,string pre1,string pre2,bool last) {	
	if (node != NULL) {
		cout << pre1 << pre2 << Print(node->element);
		if (Tree_Node::GetHeight(node->left) == Tree_Node::GetHeight(node->right)) cout << " (E)" << endl;
		else if (Tree_Node::GetHeight(node->left) > Tree_Node::GetHeight(node->right)) cout << " (L)" << endl;
		else cout << " (R)" << endl;
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

void AVL_Tree::DeleteSubtree(Tree_Node *in) {
	if (in->left != NULL) DeleteSubtree(in->left);
	if (in->right != NULL) DeleteSubtree(in->right);
	delete in;
}

void *AVL_Tree::Min() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->left != NULL) node = node->left;
	
	return Copy(node->element);
}

void *AVL_Tree::Max() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->right != NULL) node = node->right;
	
	return Copy(node->element);
}

void *AVL_Tree::PopMin() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->left != NULL) node = node->left;
	string keyValue = node->KeyValue;
	
	return Pop(keyValue);
}

void *AVL_Tree::PopMax() {
	if (root == NULL) return NULL;
	
	Tree_Node *node = root;
	while (node->right != NULL) node = node->right;
	string keyValue = node->KeyValue;
	
	return Pop(keyValue);
}

void *AVL_Tree::GetElem(string keyValue) {
	Tree_Node *node = Find(keyValue);
	
	if (node == NULL) return NULL;
	
	return Copy(node->element);
}

#endif
