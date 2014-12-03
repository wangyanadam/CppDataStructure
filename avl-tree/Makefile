AVL_TreeTest: AVL_TreeTest.o AVL_Tree.o
	g++ -o AVL_TreeTest -g AVL_TreeTest.o AVL_Tree.o

AVL_TreeTest.o: AVL_TreeTest.cpp AVL_Tree.hpp
	g++ -g -c -Wall AVL_TreeTest.cpp

AVL_Tree.o: AVL_Tree.cpp AVL_Tree.hpp
	g++ -g -c -Wall AVL_Tree.cpp

clean:
	rm -f *.o
