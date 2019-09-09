//HuffmansTree.cpp
/*
Class Description: Contains and defines the operations necessary for (re)building the Huffman Tree,
	as well as those necessary for computing the Huffman code of a character and to
	translate Huffman code into the correct character.
Class Invariants: -
Author: Jiacheng Xu & Carla Louw
Date: March 17, 2019
*/
#include "HuffmansTree.h"
#include "BitStream.h"

//Description: Default Constructor
HuffmansTree::HuffmansTree(){
    root = NULL;
    nodeCount = 0;
    rootWeight  = 0;
    treeDataCount = 0;
    trackNode = NULL;
}

//Description: Parameterized Constructor
HuffmansTree::HuffmansTree(long int ch, long int wei){
    root = new HuffmansNode(ch, wei);
    nodeCount = 1;
    treeDataCount = 0;
    rootWeight = wei;
    trackNode = root;
}

//Description: Destructor
HuffmansTree::~HuffmansTree(){
    delete root;
}

/*
void HuffmansTree::recursionOfDeleting(HuffmansNode* curr){
    if (curr == NULL){
        return;
    } else {
        recursionOfDeleting(curr->left);
        recursionOfDeleting(curr->right);
        curr->asciiOfCharacter = -1;
        curr->weight = 0;
        curr->left = NULL;
        curr->right = NULL;
        delete curr;
        curr = NULL;
    }
}
*/

//Description: Deletes the tree without deleting its nodes (in case they are used by other trees)
//Precondition: There is a Tree to clear
//Postcondition: Tree is clear without effecting other Trees
void HuffmansTree::clearTree(){
    root = NULL;
    nodeCount = 0;
    rootWeight  = 0;
}

//Description: A Getter, returns a pointer to the root of the 
// 	HuffmanNode of interest
//Precondition: The HuffmanNode exists
//Postcondition: A pointer to the root is returned.
HuffmansNode* HuffmansTree::getRoot(){
    return root;
}

//Description: A Getter, returns the nodeCount of the 
// 	HuffmanTree of interest
//Precondition: The HuffmanTree exists
//Postcondition: nodeCount is returned.
long int HuffmansTree::getCount(){
    return nodeCount;
}

//Description: A Getter, returns the weight (at the root) of the 
// 	HuffmanTree of interest
//Precondition: The HuffmanTree exists
//Postcondition: weight is returned.
long int HuffmansTree::getWeight(){
    return rootWeight;
}

//Description: A Getter, returns the priority of the 
// 	HuffmanTree of interest
//Precondition: The HuffmanTree exists
//Postcondition: priotity is returned.
long int HuffmansTree::getPriority(){
    return rootWeight;
}

//Description: Combines the left Huffman Tree (this) to the right // 	Huffman Tree (rightTree)
//Precondition: RightTree has to exist (cannot be empty)
//Postcondition:The two trees are combined into one larger tree
bool HuffmansTree::combine(HuffmansTree* rightTree){
    HuffmansNode* rightNode = rightTree->getRoot();
    if (rightNode == NULL){
        cout << "combine has problem." << endl;
        return false;
    }
    HuffmansNode* newRoot = new HuffmansNode();
    newRoot->left = root;
    root->parent = newRoot;
    root = newRoot;
    root->right = rightNode;
    rightNode->parent = root;
    rootWeight += rightTree->getWeight();
    nodeCount += rightTree->getCount();
    trackNode = root;
    return true;
}

//Description: Code the shape of the tree with 'tree pieces' using a character Number(ascii code)
//Precondition: The node count cannot exceed the data count in the tree
//Postcondition: Tree piece(s) are created
int HuffmansTree::createTreeShap(char charNumber){
    //cout << charNumber;
    int ret = 0;
    for (int j = 7; j >= 0; j--){
        if (nodeCount >= treeDataCount){
            break;
        }
        int bit = ((charNumber >> j) & 1);
        //cout << bit;
        ret += createTreeShap(bit);
    }
    return ret;
}

//Description: Code the shape of the tree using a bits
//Precondition: The node count cannot exceed the data count in the tree
//Postcondition: Tree piece(s) are created
int HuffmansTree::createTreeShap(int bit){
    if (root == NULL){
        root = new HuffmansNode();
        prevNode = root;
        nodeCount = 0;
        trackNode = root;
        if(!bit){
            root->asciiOfCharacter = treeData[0];
            nodeCount++;
            return 1;
        } else {
            return 0;
        }
    } else if (bit){
        if (!prevNode->left){
            prevNode->left = new HuffmansNode();
            prevNode->left->parent = prevNode;
            prevNode = prevNode->left;
        } else {
            prevNode->right = new HuffmansNode();
            prevNode->right->parent = prevNode;
            prevNode = prevNode->right;
        }
        return 0;
    } else {
        if (!prevNode->left){
            prevNode->left = new HuffmansNode();
            prevNode->left->asciiOfCharacter = treeData[nodeCount];
            nodeCount++;
            prevNode->left->parent = prevNode;
            while (prevNode && prevNode->right){
                prevNode = prevNode->parent;
            }
        } else {
            prevNode->right = new HuffmansNode();
            prevNode->right->asciiOfCharacter = treeData[nodeCount];
            nodeCount++;
            prevNode->right->parent = prevNode;
            while (prevNode && prevNode->right){
                prevNode = prevNode->parent;
            }
        }
        return 1;
    }
}

//Description: Creates the array that contains the actual binary code to be contained in the compression file
//Precondition: Tree cannot be empty
//Postcodition: The array has been created.
bool HuffmansTree::createCodeArray(){
    if(root == NULL){
        cout << "error on createCodeArray!" << endl;
        return false;
    } else {
        recursionOfNodes("", root);
        //cOutTheTree(root);
        return true;
    }
}

//Description: Prints the contents (leaves) of the tree
void HuffmansTree::cOutTheTree(HuffmansNode* curr){
    if (curr != NULL){
        cout << curr->asciiOfCharacter << " ";
        cOutTheTree(curr->left);
        cOutTheTree(curr->right);
    }
}

//Description: Recursively finds the leafs of a tree and keeps track of how
//	 many lefts (0) and rights (1) it takes to find it
//Precondition: Tree must exist
void HuffmansTree::recursionOfNodes(string code, HuffmansNode* curr){
    //cout << code << endl;
    if (nodeCount == 1){
        long int ascii = curr->asciiOfCharacter;
        if (ascii < 0){
            ascii += 256;
        }
        codeOfcharacters[ascii][0] = 1;
        codeOfcharacters[ascii][1] = -1;
        return;
    } else if (!curr->isLeaf()){
        recursionOfNodes(code+"0", curr->left);
        recursionOfNodes(code+"1", curr->right);
        return;
    } else {
        int ascii = curr->asciiOfCharacter;
        if (ascii < 0){
            ascii += 256;
        }
        int i = 0;
        for(; i < code.size(); i++) {
            codeOfcharacters[ascii][i] = (code[i] - '0');
        }
        /*if (i >=9){
          cout << "code: " << code;
          cout <<" a: "<< ascii << " " << i << " ";
        }*/
        codeOfcharacters[ascii][i] = -1;
        return;
    }
}

//Description: Creates an empty tree
void HuffmansTree::createTreeData(){
    treeDataCount = 0;
    createTreeData(root);
}

//Description: Create a tree using a pointer as a parameter (Deep Copy)
void HuffmansTree::createTreeData(HuffmansNode* node){
    if (!node){
        cout << "error, the root is null." << endl;
        return;
    }
    if (node->isLeaf()) {
        //cout << node->asciiOfCharacter << " ";
        treeData[treeDataCount] = node->asciiOfCharacter;
        treeDataCount++;
    }
    else {
        //cout << "node ";
        createTreeData (node->left);
        createTreeData (node->right);
    }
}

//Description: use recursion to print the tree in order
void HuffmansTree::printTreeInPreorder(BitStream* writer){
    bitBuff = char(0);
    printTreeInPreorder(root, writer);
}

//Description: use recursion to print the tree in order
void HuffmansTree::printTreeInPreorder(HuffmansNode* node, BitStream* writer){
    if (!node){
        cout << "error, the root is null." << endl;
        return;
    }
    if (node->isLeaf()) {
        writer->writeToBit(0);
    }
    else {
        writer->writeToBit(1);
        printTreeInPreorder (node->left, writer);
        printTreeInPreorder (node->right, writer);
    }
}

/*
void HuffmansTree::printTreeInPreorder(HuffmansNode* node){
    if (node == NULL){
        return;
    } else {
        // test: cout << node->asciiOfCharacter << " ";
        treeData[treeDataCount]= node->asciiOfCharacter;
        treeDataCount++;
        if (node->isLeaf()){
            treeData[treeDataCount]= char(-2);
            treeDataCount++;
        } else {
            printTreeInPreorder(node->left);
            printTreeInPreorder(node->right);
        }
    }
}
*/

//Description: Old function for creating the tree through data, if data is zero -> not a leaf, 
// 	otherwise a leaf is created to store the data. If data is (-2) -> end of branch, go back and find the next 
// 	available right.
//Postcondition: Tree is created appropriately.    
void HuffmansTree::readTree(long int dataOfTree){
    if (root == NULL){
        root = new HuffmansNode(dataOfTree);
        prevNode = root;
        nodeCount = 1;
        trackNode = root;
    } else {
        if (dataOfTree == -2) {
            do{
                prevNode = prevNode->parent;
            } while (prevNode->right != NULL);
        } else {
            if (dataOfTree == 0){
                dataOfTree = -1;
            }
            HuffmansNode* newNode = new HuffmansNode(dataOfTree);
            newNode->parent = prevNode;
            if (prevNode->left == NULL){
                prevNode->left = newNode;
            } else {
                prevNode->right = newNode;
            }
            prevNode = newNode;
            nodeCount++;
        }
    }
}

//Description: Traverses the tree, if 0-. go left; if 1-> go right; if node then return the value.
//	Then reset to root once a leaf is found. If return value is -256 then it is not a leaf; if return value is -128 to 
// 	127, then we have a character.
//Postcondition: Tree is traversed.
long int HuffmansTree::trackNodeFromTree(long int bit){
    if (trackNode == NULL){
        trackNode = root;
    }
    if (trackNode == NULL){
        cout << "the root is NULL" << endl;
    }
    if (nodeCount == 1){
        if (bit){
            long int ret = trackNode->asciiOfCharacter;
            trackNode = root;
            return ret;
        } else {
            return -256;
        }
    } else {

        if (trackNode->right == NULL){
            cout << "right null" << endl;
        }
        if (trackNode->left == NULL){
            cout << "left null" << endl;
        }

        //cout << "tracknode's long int: " << trackNode->asciiOfCharacter << endl;
        if (bit == 1){
            trackNode = trackNode->right;
            if (!trackNode){
                cout << "the right node is empty."<<endl;
            }
            if (trackNode->isLeaf()){
                long int ret = trackNode->asciiOfCharacter;
                trackNode = root;
                return ret;
            } else {
                return -256;
            }
        } else if (bit == 0){
            trackNode = trackNode->left;
            if (!trackNode){
                cout << "the left node is empty."<<endl;
            }
            if (trackNode->isLeaf()){
                long int ret = trackNode->asciiOfCharacter;
                trackNode = root;
                return ret;
            } else {
                return -256;
            }
        } else {
            return -256;
        }
    }
}

//Description: Returns the amount of data is in the tree (the number of leaves)
long int HuffmansTree::getTheSizeOfTreeData(){
    return treeDataCount;
}

//Description: A Getter (of sorts), allows the retrieval of data 
// 	using a specified index in the array of the tree
//postcondition: Returns the data in the array at the index specified
char HuffmansTree::getTreeDataByIndex(long int i){
    return treeData[i];
}

//Description: Takes a character and inserts it into the tree
//Precondition: There is a character to insert
//Postcondition: The character is inserted and the TreeDataCount is incremented.
void HuffmansTree::setTreeData(int i, char buf){
    treeData[i] = buf;
    if (i >= treeDataCount){
        treeDataCount = i+1;
    }
}

//Description: Writes the binary information to the buffer
//Precondition: There is binary information to write into the buffer
//Postcondition: The output buffer contains the necessary binary code
int HuffmansTree::writeToOutputBuffer(char* buffer, long int bufferLen, BitStream* writer){
    createCodeArray();
    for (long int i = 0; i < bufferLen; i++){
        int currentChar = int(buffer[i]);
        if (currentChar < 0){
            currentChar += 256;
        }
        int j = 0;
		    while (codeOfcharacters[currentChar][j] != -1){
            writer->writeToBit(codeOfcharacters[currentChar][j]);
            j++;
        }
    }
    return writer->checkBitTail();
}
