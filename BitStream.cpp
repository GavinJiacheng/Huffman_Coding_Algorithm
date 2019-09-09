//BitStream.cpp
/*
Class Description: Class responsible for reading 'bits' from a file and
	writing 'bits', or a sequence of 'bits', to a file.
Class Invariants: -
Author: Jiacheng Xu & Carla Louw
Date: March 17, 2019
*/

//Description: Default Constructor
#include "BitStream.h"

BitStream::BitStream(){
    buffer = NULL;
    length = 0;
    outputBuffer = NULL;
    lengthOfOutput = 0;
    mainTree = NULL;
    mode = 1;
    currentIndex = 0;
    currentBit = 7;
    bitBuff = char(0);
    treeQueue = new PriorityQueue();
}

//Description: Parameterized Constructor
BitStream::BitStream(int inputMode){
    buffer = NULL;
    length = 0;
    outputBuffer = NULL;
    lengthOfOutput = 0;
    mainTree = NULL;
    mode = inputMode;
    currentIndex = 0;
    currentBit = 7;
    bitBuff = char(0);
    treeQueue = new PriorityQueue();
}

//Description: Destructor (for dynamic)
//Precondition: A BitStream object exists to be destructed
//Postcondition: BitStream object is deleted
BitStream::~BitStream(){
    delete treeQueue;
    treeQueue = NULL;
    delete [] buffer;
    buffer = NULL;
    delete [] outputBuffer;
    mainTree = NULL;
    delete mainTree;
    mainTree = NULL;
}

//Description: Reader File, takes in characters and reads the
//	binary bit code associated with it.
//Postcondition: File is read into a buffer as the binary code.
bool BitStream::loadFile(char* argv){
    //load file:
    ifstream reader(argv, ifstream::binary);
    if (reader){
        reader.seekg (0, reader.end);
        length = reader.tellg();
        reader.seekg (0, reader.beg);
        buffer = new char[length];
        reader.read (buffer,length);
        reader.close();
        if (mode){
            lengthOfOutput = length + 1024;
        }else{
            lengthOfOutput = length * 8;
        }
        outputBuffer = new char[lengthOfOutput];
        setBitStream();
        if (mode){
            cout << argv << " -> " << length << " bytes" << endl;
        }
        return true;
    } else {
        return false;
    }
}

//Description: Takes in either (-c) or (-d) to for later specification of compression
// 	or decompression
void BitStream::setMode(int inputMode){
    mode = inputMode;
}

//Description: Establishes the correct code in an 8-digit format, will move
// 	through all bytes present
void BitStream::writeToBit(int bit){
    if (bit){
        bitBuff |= (1<<currentBit);
    }
    currentBit--;
    if (currentBit == -1){
        outputBuffer[currentIndex] = bitBuff;
        currentIndex++;
        bitBuff = char(0);
        currentBit = 7;
    }
}

//Description: Checks to see how many 0's are placed on the end of a byte (as placeholders)
//	and places the necessary 0s since a byte must have 8 bits and the unspecified places are set to 0
//Postcondition: Byte is completed with the necessary number of zeros at the end
int BitStream::checkBitTail(){
    int ret = 0;
    if (currentBit != 7){
	      ret = currentBit + 1;
        currentBit = 7;
        outputBuffer[currentIndex] = bitBuff;
        currentIndex++;
        bitBuff = char(0);
    }
	return ret;
}

//Description: Takes all the bytes created an joins them into one long string (for reading purposes)
//Postcondition: Bytes are joined into one string of bytes.
void BitStream::setBitStream(){
    if (mode) {
        if (!length){
            lengthOfOutput = 0;
            return;
        }
        for (long int i = 0; i < length; i++){
            counter.addCharacter(buffer[i]);
        }
        counter.buildingTrees(treeQueue);
        mergeHuffmansTrees();
        int treeLeafCount = mainTree->getCount();
        outputBuffer[0] = treeLeafCount;
        currentIndex = 1;
        mainTree->createTreeData();
        for (int i = 0; i < treeLeafCount; i++){
            outputBuffer[currentIndex] = mainTree->getTreeDataByIndex(i);
            currentIndex++;
        }
        mainTree->printTreeInPreorder(this);
        checkBitTail();
	      int tailBit = mainTree->writeToOutputBuffer(buffer, length, this);
        lengthOfOutput = currentIndex;
        outputBuffer[lengthOfOutput] = char(tailBit);
        lengthOfOutput++;
		} else {
	      // read binary
        if (!length){
            lengthOfOutput = 0;
            return;
        }
        long int currentIndexOfBits = createTreeFromBinary();
        long int indexOfOutput = 0;
		    long int tailLength = buffer[length-1];
	      // transfer the binary to txt
        for (long int i = currentIndexOfBits; i < length - 1; i++){
            char buff = buffer[i];
	          int tailIndex = 0;
			  if (i == length - 2){
			      tailIndex = tailLength;
			  }
            for (long int j = 7; j >= tailIndex; j--){
                long int bit = ((buff >> j) & 1);
                long int nodeValue = mainTree->trackNodeFromTree(bit);
                if (nodeValue != -256){
                    if(nodeValue > 127){
                        nodeValue -= 256;
                    }
                    outputBuffer[indexOfOutput] = char(nodeValue);
                    indexOfOutput++; // still needs test for the last binary
                }
            }
        }
	  lengthOfOutput = indexOfOutput;
    }
}

//Description: Takes to Huffman Trees and joins them into one,
//	specifically joining tree2 onto tree1 (deep copy), then deleting tree2
//Precondition: There are trees to join
//Postcondition: Trees are joined into one and set as maintree.
void BitStream::mergeHuffmansTrees(){
    while (treeQueue->getElementCount() > 1){
        HuffmansTree* tree1 = treeQueue->peek();
        treeQueue->dequeue();
        HuffmansTree* tree2 = treeQueue->peek();
        treeQueue->dequeue();
        tree1->combine(tree2);
        tree2->clearTree();
        delete tree2;
        treeQueue->enqueue(tree1);
    }
    mainTree = treeQueue->peek();
}

//Description: Writes the data (bytes) to an external file
bool BitStream::writeToFile(char* argv){
    ofstream outfile (argv, ofstream::binary);
    outfile.write (outputBuffer,lengthOfOutput);
    outfile.close();
    if (mode){
        cout << argv << " -> " << lengthOfOutput << " bytes" << endl;
        if (lengthOfOutput > length){
            cout << "*** Size of compressed file > size of source file ***" << endl;
        }
    }
}

//Description: Takes in binary code and forms the appropriate tree from it
//Precondition: There is binary code to read from
//Postcondition: Appropriate tree is formed from the binary instructions
long int BitStream::createTreeFromBinary(){
    mainTree = new HuffmansTree();
    long int treeLength = buffer[0];
    long int treeLengthCount = 0;
    long int ret = 1;
    //cout << "length: " << length << endl << "treeLength: " << treeLength << endl;
    if (treeLength <= 0){
        treeLength += 256;
    }
    for (int i = 0; i < treeLength; i++){
        mainTree->setTreeData(i, buffer[ret]);
        ret++;
    }
    for (; ret< length && treeLengthCount < treeLength; ret++){
        treeLengthCount += mainTree->createTreeShap(buffer[ret]);
    }
    return ret;
}
