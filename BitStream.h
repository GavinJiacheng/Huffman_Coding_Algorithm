//BitStream.h
/*
Class Description: Class responsible for reading 'bits' from a file and
	writing 'bits', or a sequence of 'bits', to a file.
Class Invariants: -
Author: Jiacheng Xu & Carla Louw
Date: March 17, 2019
*/
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "FrequencyCounter.h"

class BitStream
{
private:
    char* buffer;
    long int length;
    char* outputBuffer;
    long int lengthOfOutput;
    int mode;
    long int currentIndex;
    char bitBuff;
    int currentBit;
    PriorityQueue* treeQueue;
    HuffmansTree* mainTree;
    FrequencyCounter counter;
public:
    //Description: Default Constructor
    BitStream();

    //Description: Parameterized Constructor
    BitStream(int inputMode);

    //Description: Destructor (for dynamic allocation)
    //Precondition: A BitStream object exists to be destructed
    //Postcondition: BitStream object is deleted
    ~BitStream();

    //Description: Reader File, takes in characters and reads the
    //	binary bit code associated with it.
    //Postcondition: File is read into a buffer as the binary code.
    bool loadFile(char* argv);

    //Description: Takes in either (-c) or (-d) to for later specification of compression
    // 		or decompression
    void setMode(int inputMode);

    //Description: Establishes the correct code in an 8-digit format, will move
    // 	through all bytes present
    void  writeToBit(int bit);

    //Description: Checks to see how many 0's are placed on the end of a byte (as placeholders)
    //		and places the necessary 0s since a byte must have 8 bits and the unspecified places are set to 0
    //Postcondition: Byte is completed with the necessary number of zeros at the end
    int checkBitTail();

    //Description: Takes all the bytes created an joins them into one long string (for reading purposes)
    //Postcondition: Bytes are joined into one string of bytes.
    void setBitStream();

    //Description: Takes to Huffman Trees and joins them into one,
    //	specifically joining tree2 onto tree1 (deep copy), then deleting tree2
    //Precondition: There are trees to join
    //Postcondition: Trees are joined into one and set as maintree.
    void mergeHuffmansTrees();

    //Description: Writes the data (bytes) to an external file
    bool writeToFile(char* argv);

    //Description: Takes in binary code and forms the appropriate tree from it
    //Precondition: There is binary code to read from
    //Postcondition: Appropriate tree is formed from the binary instructions
    long int createTreeFromBinary();
};
