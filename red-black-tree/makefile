RB_TreeTest: RB_TreeTest.o RB_Tree.o
	g++ -o RB_TreeTest -g RB_TreeTest.o RB_Tree.o

RB_TreeTest.o: RB_TreeTest.cpp RB_Tree.hpp
	g++ -g -c -Wall RB_TreeTest.cpp

RB_Tree.o: RB_Tree.cpp RB_Tree.hpp
	g++ -g -c -Wall RB_Tree.cpp

clean:
	rm -f *.o
