/*
HuffCom.cpp
Description: The actual application (contains the main() function) that runs the other classes together
	to actually implement the process of compression/decompression
Authors: Jiancheng Xu & Carla Louw
Date: March 17, 2019
*/
#include "PriorityQueue.h"
#include "BitStream.h"
#include <cstring>

using namespace std;


//the first byte will be from 0 - 256, which means the length of the tree
//then is the tree, 11111111 means the end of the node and 00000000 means "-1";

int main(int argc, char* argv[])
{
	// error
	if (argc != 4){
      cout << "Please input the correct format! (example: ./huff -c source.txt compressedSource.huff)" << endl;
			return 0;
	}
	// to do:
	int mode = -1; // 1 means -c, 0 means -d
  if (strcmp(argv[1], "-c") == 0){
	    mode = 1;
	} else if (strcmp(argv[1], "-d") == 0){
	    mode = 0;
	} else {
	    cout << "please write the correct mode! (-c or -d)" << endl;
	    return 0;
	}
	BitStream streamer(mode);
	// load file
	if (!streamer.loadFile(argv[2])){
		cout << "the file does not exist!" << endl;
		return 0;
	}
	// save file
	streamer.writeToFile(argv[3]);
  return 0;
}
