//HuffmansTree.h
/*
Class Description: Contains and defines the operations necessary for (re)building the Huffman Tree,
	as well as those necessary for computing the Huffman code of a character and to
	translate Huffman code into the correct character.
Class Invariants: -
Author: Jiacheng Xu & Carla Louw
Date: March 17, 2019
*/
#pragma once
#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

class BitStream;

//Description: A "Node" specifically designed for the Huffman
//	Tree algorithm and the method of implementation used here.
//	Note: To prevent confusion with previous Node classes.
class HuffmansNode
{
public:
	//Description: Constructor
    HuffmansNode(){
        asciiOfCharacter = 0;
        weight = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
	//Description: Parameterized Constructor (Two Parameters)
    HuffmansNode(long int ch, long int wei){
        asciiOfCharacter = ch;
        weight = wei;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
	//Description: Paramaterized Constructor (One Parameter)
    HuffmansNode(long int ch){
        asciiOfCharacter = ch;
        weight = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
	//Description: Destructor
    ~HuffmansNode(){
        delete left;
        delete right;
        left = right = NULL;
    };
	//Description: Tests if the HuffmanNode is a leaf or not
    bool isLeaf(){
        return (this->right == NULL && this->left == NULL);
    }
	//Public Attributes
    long int asciiOfCharacter;
    long int weight;
    HuffmansNode* right;
    HuffmansNode* left;
    HuffmansNode* parent;
};

class HuffmansTree
{
private: //establish the attributes of the class
    HuffmansNode* root;
    long int nodeCount;
    long int rootWeight;
    char treeData[256];
    long int treeDataCount;
    long int codeOfcharacters[256][256]; //
    HuffmansNode* prevNode;
    HuffmansNode* trackNode;
    unsigned char bitBuff;
    void recursionOfDeleting(HuffmansNode* curr);

    //Description: Recursively finds the leafs of a tree and keeps track of how
    //	 many lefts (0) and rights (1) it takes to find it
    //Precondition: Tree must exist
    void recursionOfNodes(string code, HuffmansNode* curr);

    //Description: use recursion to print the tree in order
    void printTreeInPreorder(HuffmansNode* node, BitStream* writer);
public: //establish the methods/operations of this class

    //Description: Default Constructor
    HuffmansTree();

    //Description: Parameterized Constructor
    HuffmansTree(long int ch, long int wei);

    //Description: Destructor
    ~HuffmansTree();

    //Description: Deletes the tree without deleting its nodes (in case they are used by other trees)
    //Precondition: There is a Tree to clear
    //Postcondition: Tree is clear without effecting other Trees
    void clearTree();

    //Description: A Getter, returns a pointer to the root of
    //	the HuffmanNode of interest
    //Precondition: The HuffmanNode exists
    //Postcondition: A pointer to the root is returned.
    HuffmansNode* getRoot();

    //Description: A Getter, returns the nodeCount of
    //	the HuffmanTree of interest
    //Precondition: The HuffmanTree exists
    //Postcondition: The nodeCount is returned.
    long int getCount();

    //Description: A Getter, returns the weight (at the root) of
    //	the HuffmanTree of interest
    //Precondition: The HuffmanTree exists
    //Postcondition: The weight is returned.
    long int getWeight();

    //Description: A Getter, returns the priotity of
    //	the HuffmanTree of interest
    //Precondition: The HuffmanTree exists
    //Postcondition: The priority is returned.
    long int getPriority();

    //Description: Combines the left Huffman Tree (this) to the right Huffman Tree (rightTree)
    //Precondition: RightTree has to exist (cannot be empty)
    //Postcondition:The two trees are combined into one larger tree
    bool combine(HuffmansTree* rightTree);

    //Description: Code the shape of the tree  with 'tree pieces' using a character Number(ascii code)
    //Precondition: The node count cannot exceed the data count in the tree
    //Postcondition: Tree piece(s) are created.
    int createTreeShap(char);

    //Description: Code the shape of the tree using a bits
    //Precondition: The node count cannot exceed the data count in the tree
    //Postcondition: Tree piece(s) are created
    int createTreeShap(int bit);

    //Description: Creates the array that contains the actual binary code to be contained in the compression file
    //Precondition: Tree cannot be empty
    //Postcodition: The array has been created.
    bool createCodeArray();

    //Description: Prints the contents (leaves) of the tree
    void cOutTheTree(HuffmansNode* curr);

    //Description: Creates an empty tree
    void createTreeData();

    //Description: Create a tree using a pointer as a parameter (Deep Copy)
    void createTreeData(HuffmansNode* node);

    //Description: use recursion to print the tree in order
    void printTreeInPreorder(BitStream* writer);

    //Description: Old function for creating the tree through data, if data is zero -> not a leaf,
    // 		otherwise a leaf is created to store the data. If data is (-2) -> end of branch, go back and find the next
    // 		available right.
    //Postcondition: Tree is created appropriately.
    void readTree(long int dataOfTree);

    //Description: Traverses the tree, if 0-. go left; if 1-> go right; if node then return the value.
    //		Then reset to root once a leaf is found. If return value is -256 then it is not a leaf;
    //		if return value is -128 to 127, then we have a character.
    //Postcondition: Tree is traversed.
    long int trackNodeFromTree(long int bit);

    //Description: Returns the amount of data is in the tree (the number of leaves)
    long int getTheSizeOfTreeData();

    //Description: A Getter (of sorts), allows the retrieval of data
    // 		using a specified index in the array of the tree
    //postcondition: Returns the data in the array at the index specified
    char getTreeDataByIndex(long int i);

    //Description: Takes a character and inserts it into the tree
    //Precondition: There is a character to insert
    //Postcondition: The character is inserted and the TreeDataCount is incremented.
    void setTreeData(int i, char buf);

    //Description: Writes the binary information to the buffer
    //Precondition: There is binary information to write into the buffer
    //Postcondition: The output buffer contains the necessary binary code
    int writeToOutputBuffer(char* buffer, long int bufferLen, BitStream* writer);
};
