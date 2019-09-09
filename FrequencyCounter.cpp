//FrequencyCounter.cpp
/*
Class Description: Class designed to create a frequency table that stores characters and
	the frequency with which they appear.
Class Invariants:
Author: Jiacheng Xu & Carla Louw
Date: March 17, 2019
*/

#include "FrequencyCounter.h"

//Description: Default Constructor
FrequencyCounter::FrequencyCounter(){
    for(int i = 0; i < 256; i++){
		    weightOfAsciiTable[i] = 0;
	  }
    charactersNumber = 0;
}

//Description: Adds a character to the frequency table
//Postcondition: The frequency of the character is incremented
void FrequencyCounter::addCharacter(char ch){
    int indexOfChar = int(ch);
    if (indexOfChar < 0){
        indexOfChar += 256;
    }
    weightOfAsciiTable[indexOfChar] ++;
    if (weightOfAsciiTable[indexOfChar] == 1){
        characters[charactersNumber] = indexOfChar;
        charactersNumber ++;
    }
}

//Description: Takes the frequency and builds it into the  
//	approptiate position of the priority queue
//Postcondition: Character with it's new frequency is created as
// 	a piece for the tree and inserted into the priority queue
void FrequencyCounter::buildingTrees(PriorityQueue* Q){
    //cout << "character number is: " << charactersNumber << endl;
	  for (long int i = 0; i< charactersNumber; i++){
		    long int ch = characters[i];
		    long int wei = weightOfAsciiTable[ch];
		    HuffmansTree* newTree = new HuffmansTree(ch, wei);
		    Q->enqueue(newTree);
		}
}
