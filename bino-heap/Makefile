Binomial_Heap_Test: Binomial_Heap_Test.o Binomial_Heap.o
	g++ -o Binomial_Heap_Test -g Binomial_Heap_Test.o Binomial_Heap.o

Binomial_Heap_Test.o: Binomial_Heap_Test.cpp Binomial_Heap.hpp
	g++ -g -c -Wall Binomial_Heap_Test.cpp

Binomial_Heap.o: Binomial_Heap.cpp Binomial_Heap.hpp
	g++ -g -c -Wall Binomial_Heap.cpp

clean: 
	rm -f *.o
