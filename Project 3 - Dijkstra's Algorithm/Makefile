# Andrew Lorber
# DSA II Project 3 - Dijkstra's Algorithm
# Make File

dijkstra: main.o graph.o heap.o hash.o
	g++ -std=c++11 -o dijkstra.out main.o graph.o heap.o hash.o

main.o: main.cpp graph.h heap.h hash.h
	g++ -std=c++11 -c main.cpp

graph.o: graph.cpp graph.h heap.h hash.h
	g++ -std=c++11 -c graph.cpp

heap.o: heap.cpp heap.h hash.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o dijkstra.out main.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.out *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
