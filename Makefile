all: huff

huff: HuffCom.o BitStream.o FrequencyCounter.o HuffmansTree.o PriorityQueue.o 
	g++ -Wall -o huff HuffCom.o BitStream.o FrequencyCounter.o HuffmansTree.o PriorityQueue.o 

HuffCom.o: HuffCom.cpp
	g++ -c HuffCom.cpp

BitStream.o: BitStream.cpp BitStream.h
	g++ -c BitStream.cpp

FrequencyCounter.o: FrequencyCounter.cpp FrequencyCounter.h
	g++ -c FrequencyCounter.cpp

HuffmansTree.o: HuffmansTree.cpp HuffmansTree.h
	g++ -c HuffmansTree.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	g++ -c PriorityQueue.cpp

clean:
	rm -f huff *.o
