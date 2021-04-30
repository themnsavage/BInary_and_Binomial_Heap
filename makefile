all: Phase3Main.o CDA.o Heap.o BHeap.o
	g++ Phase3Main.o CDA.o Heap.o Bheap.o -o Phase3

phase1Main.o: Phase3Main.cpp
	g++ -c Phase3Main.cpp

CDA.o: CDA.cpp 
	g++ -c CDA.cpp
Heap.o: Heap.cpp
	g++ -c Heap.cpp
BHeap.o: BHeap.cpp
	g++ -c BHeap.cpp
clean:
	rm *.o output