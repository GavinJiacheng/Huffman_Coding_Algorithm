//FrequencyCounter.h
/*
Class Description: Class designed to create a frequency table that stores characters and
	the frequency with which they appear.
Class Invariants:
Author: Jiacheng Xu & Carla Louw
Date: March 17, 2019
*/
#pragma once
#include "HuffmansTree.h"
#include "PriorityQueue.h"

class FrequencyCounter
{
private:
	  long int weightOfAsciiTable[256];
	  int characters[256];
	  int charactersNumber;
public:
	//Description: Default Constructor
  	FrequencyCounter();

	//Description: Adds a character to the frequency table
	//Postcondition: The frequency of the character is 	
	//	incremented
  	void addCharacter(char ch);

	//Description: Takes the frequency and builds it into the  
	//	approptiate position of the priority queue
	//Postcondition: Character with it's new frequency is created as a piece 
	// 	for the tree and inserted into the priority queue
  	void buildingTrees(PriorityQueue* Q);
};
