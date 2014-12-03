#include "AVL_Tree.hpp"
#include <sstream>

using namespace std;

void *Copy(void *elem) {
	if (elem == NULL) return NULL;
	
	string *cpyElem = new string(*(string *)elem);
	return cpyElem;
}

string Key(void *elem) {
	if (elem == NULL) return "";
	
	return (*(string *)elem);
}

string Print(void *elem) {
	if (elem == NULL) return "";
	
	return (*(string *)elem);
}

int main() {
	AVL_Tree *tree = new AVL_Tree();
	tree->Copy = &Copy;
	tree->Print = &Print;
	tree->Key = &Key;
	
	string line,input,command;
	
	while (getline(cin,line)) {
		if (line.compare("exit") == 0) break;
		
		istringstream ss(line);
		ss >> command;
		ss >> input;
		
		string *new_record;
		new_record = new string;
		*new_record = input;
		
		if (command.compare("insert") == 0) tree->Insert(new_record);
		
		if (command.compare("delete") == 0) tree->Delete(tree->Key(new_record));
		
		if (command.compare("min") == 0) cout << "The element with the current minimum key is " << tree->Print(tree->Min()) << "." << endl;
		
		if (command.compare("max") == 0) cout << "The element with the current maximum key is " << tree->Print(tree->Max()) << "." << endl;
		
		if (command.compare("popmin") == 0) cout << "The element with the current minimum key is " << tree->Print(tree->PopMin()) << "." << endl;
		
		if (command.compare("popmax") == 0) cout << "The element with the current maximum key is " << tree->Print(tree->PopMax()) << "." << endl;
		
		cout << "Now there are " << tree->Size() << " elements in the AVL tree." << endl;
		cout << "The tree's height is " << tree->Height() << ". Shown as below:" << endl;
		tree->Display();
		cout << endl;
	}
	
	cout << endl;
	cout << "The remaining tree:" << endl;
	tree->Display();
	
	return 0;
}
