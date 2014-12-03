#include "Binomial_Heap.hpp"

#include <sstream>
#include <cstdio>

using namespace std;

void del(void *elem) {
	delete (int *)elem;
};

int key(void *elem) {
	return atoi((*(string *)elem).c_str());
};

string print(void *elem) {
	return *(string *)elem;
}

int main() {
	int max_degree;
	cin >> max_degree;
	getchar();
	
	Binomial_Heap *heap = new Binomial_Heap(max_degree,NULL);
	heap->DelElem = del;
	heap->Key = key;
	heap->Print = print;
	
	cout << "max_degree = " << heap->GetMaxDegree() << endl << endl;
	
	Binomial_Tree_Node *nodes[999];
	for (int i = 0;i < 999;i++) nodes[i] = NULL;
	int num_nodes = -1;
	
	string s;
	while (getline(cin,s)) {
		istringstream ss(s);
		
		string command,operator1,operator2;
		ss >> command;
		ss >> operator1;
		ss >> operator2;
		
		if (command.compare("insert") == 0) {
			string *elem;
			elem = new string(operator1);
			int key = atoi(operator2.c_str());
			
			num_nodes++;
			nodes[num_nodes] = new Binomial_Tree_Node(elem,key,heap->GetMaxDegree());
			heap->Insert(nodes[num_nodes]);
		}
		else if (command.compare("min") == 0) {
			void *elem = heap->GetMinElem();
			if (elem == NULL) {
				cout << "Empty!" << endl;
				continue;
			}
			cout << heap->Print(elem) << endl;
		}
		else if (command.compare("popmin") == 0) {
			void *elem = heap->PopMinElem();
			if (elem == NULL) {
				cout << "Empty!" << endl;
				continue;
			}
			cout << heap->Print(elem) << endl;
		}
		else if (command.compare("delete") == 0) {
			int delete_node_idx = atoi(operator1.c_str());
			heap->Delete(nodes[delete_node_idx]);
			nodes[delete_node_idx] = NULL;
		}
		else if (command.compare("update") == 0) {
			int update_node_idx = atoi(operator1.c_str());
			int update_key_value = atoi(operator2.c_str());
			nodes[update_node_idx] = heap->UpdateKey(nodes[update_node_idx],update_key_value);
		}
		else break;
	}
	
	return 0;
}
