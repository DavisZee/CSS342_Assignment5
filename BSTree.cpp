/*
 * Created on 02/26/2021
 * Modified by Davis Zhong on 02/26/2021
 * Modified by Affan Dhankwala on 3/3/2021
*/

#include <cassert>
#include <iostream>

#include "BSTree.h"

using namespace std;

ostream& operator<<(ostream& out, const BSTree& tree) {
	return out;
}

// LeafNode Public:

// constructor
LeafNode::LeafNode() : leftChild{ nullptr }, rightChild{ nullptr }, lThread{ false }, 
rThread{ false }
{}

// constructor with data input
LeafNode::LeafNode(const int& newData) : data{newData}, leftChild{nullptr}, 
    rightChild{nullptr}, lThread{ false }, rThread{ false }
{}

//constructure with all variables argument
LeafNode::LeafNode(const int& newData, LeafNode* leftPtr, LeafNode* rightPtr) : 
    data{newData}, leftChild{leftPtr}, rightChild{rightPtr}, lThread{ false }, rThread{ false }
{}


void LeafNode::setData(const int& newData) {
    data = newData;
}

int LeafNode::getData() {
    return data;
}

bool LeafNode::isLeafNode() const {
    return (leafState == true);
}

auto LeafNode::getLeftChildPtr() const {
    return leftChild;
}

auto LeafNode::getRightChildPtr() const {
    return rightChild;
}

void LeafNode::setLeftChild(LeafNode* leftLeaf) {
    leftChild = leftLeaf;
}

void LeafNode::setRightChild(LeafNode* rightLeaf) {
    rightChild = rightLeaf;
}

//BSTree protected

int BSTree::getHeightHelper(LeafNode* subTreePtr) const {
    if (subTreePtr == nullptr) return 0;
    
    int leftHeight = getHeightHelper(subTreePtr->leftChild);
    int rightHeight = getHeightHelper(subTreePtr->rightChild);


    //returns the max of leftHeight and rightHeight (+ 1 to account for itself)
    return (leftHeight < rightHeight) ? rightHeight + 1: leftHeight + 1;
}

int BSTree::getNumOfNodesHelper(LeafNode* subTreePtr) const {
    if (subTreePtr == nullptr) return 0;
    int counter = 0;
    //Recursively traverse tree going left then right if have those children
    
    counter += getNumOfNodesHelper(subTreePtr->leftChild);
    counter += getNumOfNodesHelper(subTreePtr->rightChild);
  
    //Return the count (+1 to account for itself)
    return counter + 1;
}



bool BSTree::removeValue(LeafNode* subTreePtr, const int target) {
    // careful of mem leak
	return true;
}

auto BSTree::moveValuesUpTree(LeafNode* subTreePtr) {
	return;
}

LeafNode* BSTree::findNode(LeafNode* treePtr, const int target) const {
	LeafNode* lf = new LeafNode();
	return lf;
}

LeafNode* BSTree::copyTree(LeafNode* oldTreeRootPtr) {
    if (oldTreeRootPtr == nullptr) return nullptr;
    LeafNode* temp = new LeafNode();
    temp = oldTreeRootPtr;
    
    temp->leftChild = copyTree(oldTreeRootPtr->leftChild);
    temp->rightChild = copyTree(oldTreeRootPtr->rightChild);
    
    return oldTreeRootPtr;
}

//destroys all nodes in the tree and makes sure there is no mem leak
void BSTree::burnTheTree(LeafNode* subTreePtr) {

}

void BSTree::preorder(void visit(int), LeafNode* treePtr) {

}

void BSTree::inorder(void visit(int), LeafNode* treePtr) {

}

void BSTree::postorder(void visit(int), LeafNode* treePtr) {

}

//BSTree public

BSTree::BSTree() {
    //In the case of empty, root will be a dummy node
    rootPtr = new LeafNode();
}

BSTree::BSTree(const int data) {
   //This method will add all values from 1 - data into BSTree

    //Dummy node
    rootPtr = new LeafNode();
    //Link whole tree to be on left of dummy node
    rootPtr->rThread = true;
    rootPtr->lThread = false;
    rootPtr->leftChild = rootPtr;
    rootPtr->rightChild = rootPtr;
    //Add all values from 1 - data into tree
    for (int i = 0; i < data; i++) {
        add(i + 1);
    }
    //rootPtr = sortedArrToTree(values, 1, data);

    //delete[] values;
}



void BSTree::balancedAdd(int arr[], int start, int end) {
    // maybe check and set leafState in this metho
    

    //if (subTreePtr == nullptr) {
    //    newNodePtr->leafState = true;
    //    return newNodePtr;
    //}
   
    //else if (subTreePtr->data > newNodePtr->data) {
    //    subTreePtr->leafState = false;
    //    subTreePtr->leftChild = balancedAdd(subTreePtr->leftChild, newNodePtr);
    //    if (subTreePtr->leftChild == nullptr) return nullptr;
    //}
    //else if (subTreePtr->data < newNodePtr->data) {
    //    subTreePtr->leafState = false;
    //    subTreePtr->rightChild = balancedAdd(subTreePtr->rightChild, newNodePtr);
    //    if (subTreePtr->rightChild == nullptr) return nullptr;
    //}
    ////Want to make sure duplicates are not stored
    //else if (subTreePtr->data == newNodePtr->data) {
    //    return nullptr;
    //}
    //return subTreePtr;
    //
}

LeafNode* BSTree::sortedArrToTree(int arr[], int start, int end) {

    if (start > end) return NULL;

    int mid = (start + end) / 2;

    //Assign root as middle pointer
    LeafNode* midNode = new LeafNode(arr[mid - 1]);


    //Recursively link left and right sides
    midNode->leftChild = sortedArrToTree(arr, start, mid - 1);

    //Recursively link right side
    midNode->rightChild = sortedArrToTree(arr, mid + 1, end);   

    return midNode;
}

BSTree::BSTree(const int data, BSTree* leftTreePtr, BSTree* rightTreePtr) {
    rootPtr->data = data;
    rootPtr->leftChild = copyTree(leftTreePtr->rootPtr);
    rootPtr->rightChild = copyTree(rightTreePtr->rootPtr);
}

BSTree::BSTree(const BSTree* aTree) {
    
    rootPtr = copyTree(aTree->rootPtr);

}

BSTree::~BSTree() {

}

//
bool BSTree::isEmpty() const {
	return rootPtr == nullptr; // if root is nullptr then tree is empty
}

int BSTree::getHeight() const {
    return getHeightHelper(rootPtr);
}

int BSTree::getNumOfNodes() const {
    return getNumOfNodesHelper(rootPtr);
}

int BSTree::getRootData() const {
	return rootPtr->data;
}

void BSTree::setRootData(const int newData) {
    rootPtr->data = newData;
}

bool BSTree::add(const int newData) {
    //first check if tree is empty
    if ((rootPtr->leftChild == rootPtr) && (rootPtr->rightChild == rootPtr)) {
        //At this point the tree is empty and only has dummy node
        LeafNode* tempNode = new LeafNode();
        //Reroute all pointers of root to tempNode
        tempNode->data = newData;
        tempNode->leftChild = rootPtr->leftChild;
        tempNode->lThread = rootPtr->lThread;
        tempNode->rThread = false;
        tempNode->rightChild = rootPtr->rightChild;
        //Insert tempNode into tree
        rootPtr->leftChild = tempNode;
        rootPtr->lThread = true;
        return true;
    }
    //Tree is not empty so we will have to just add it
    LeafNode* ptr = new LeafNode();
    //This will avoid the dummy node
    ptr = rootPtr->leftChild;
    //Keep looping until internally stopped by return
    while (1) {
        if (newData == ptr->data) return false;
        if (newData < ptr->data) {
            //In this case, we need to navigate left
            LeafNode* tempNode = new LeafNode(newData);
            if (ptr->lThread == false) {
                //At this point we know that the leftChild does not point to any
                //inorder predecessor. 
                tempNode->leftChild = ptr->leftChild;
                tempNode->lThread = ptr->rThread;
                tempNode->rThread = false;

                //Point to inorder successor 
                tempNode->rightChild = ptr;
                ptr->lThread = true;
                ptr->leftChild = tempNode;
                return true;
            }
            else ptr = ptr->leftChild;

        }
        //Do same thing if it is larger than the current node data
        if (newData > ptr->data) {
            LeafNode* tempNode = new LeafNode(newData);
            if (ptr->rThread == false) {
                tempNode->rightChild = ptr->rightChild;
                tempNode->rThread = ptr->rThread;
                tempNode->lThread = false;
                tempNode->leftChild = ptr;

                ptr->rThread = true;
                ptr->rightChild = tempNode;
                return true;
            }
            else ptr = ptr->rightChild;
        }
    }
}

    
    
    
//    
//    
//    
//    
//    LeafNode* tempNode = new LeafNode(newData); // start by creating a new ptr
//    // should check and set leafState in this method
//    // if tree is empty then set it as the root
//    // 
//    // if node is now a leaf then turn into a threaded node
//    // clear and delete all pointer variables created
//    
//    //Point tempNode to rootPtr
//    if (rootPtr == nullptr) {
//        //This is the only node so it is a leaf as well
//        
//        rootPtr = tempNode;
//    }
//    else {
//        //Call it twice...not ideal but we dont use extra memory
//        LeafNode* p = balancedAdd(rootPtr, tempNode);
//        if (!p) return false;
//        rootPtr = p;
//    }
//
//    tempNode = nullptr;
//    delete tempNode;
//	return true;
//}

bool BSTree::remove(const int data) {
    // careful of mem leak here
	return true;
}

void BSTree::clear() {
    
}

int BSTree::getEntry(const int anEntry) {
	return 0;
}

bool BSTree::contains(const int anEntry) const {
	return true;
}

void BSTree::preorderTrav(void visit(int&)) const {

}

void BSTree::inorderTrav(void visit(int&)) const {

}

void BSTree::postorderTrav(void visit(int&)) const {

}

BSTree& BSTree::operator= (const BSTree& rightHandSIde) {
    return *this;
}
