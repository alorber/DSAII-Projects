# Andrew Lorber
# DSA II Project 2 - Priority Queue
# Make File

useHeap: useHeap.o heap.o hash.o
	g++ -std=c++11 -o useHeap.out useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp heap.h hash.h
	g++ -std=c++11 -c useHeap.cpp

heap.o: heap.cpp heap.h hash.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
