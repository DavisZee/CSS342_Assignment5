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
LeafNode::LeafNode() : leftChild{nullptr}, rightChild{nullptr} {}

// constructor with data input
LeafNode::LeafNode(const int& newData) : data{newData}, leftChild{nullptr}, 
    rightChild{nullptr} 
{}

//constructure with all variables argument
LeafNode::LeafNode(const int& newData, LeafNode* leftPtr, LeafNode* rightPtr) : 
    data{newData}, leftChild{leftPtr}, rightChild{rightPtr} 
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

auto BSTree::balancedAdd(LeafNode* subTreePtr, LeafNode* newNodePtr) {
    // maybe check and set leafState in this method
	return;
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

bool BSTree::copyTree(const LeafNode* oldTreeRootPtr) const {
	return true;
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
    //In the case of empty, root will be null
    rootPtr = nullptr;
}

BSTree::BSTree(const int data) {
    ////When call BSTree with only one parameter then set root to that data
    //rootPtr->data = data;
    //rootPtr->leftChild = nullptr;
    //rootPtr->rightChild = nullptr;
    ////Currently it is a leaf so set that to true
    //rootPtr->leafState = true; 
    

    //This method will add all values from 1 - data into BSTree


}

BSTree::BSTree(const int data, BSTree* leftTreePtr, BSTree* rightTreePtr) {
    //Initially set root to data
    rootPtr->data = data;
    //Create leafNode to traverse BStrees
    //Start with left tree 
    LeafNode* rootTemp = rootPtr;
    LeafNode* leftTemp = leftTreePtr->rootPtr;
    LeafNode* rightTemp = rightTreePtr->rootPtr;
    rootPtr->leftChild = leftTemp;
    rootPtr->rightChild = rightTemp;
    //Move to left child
    rootPtr = rootPtr->leftChild;
    
    //At this point we want to traverse entire left and right BSTrees recursively
    //and copy all their elements into root.

}

BSTree::BSTree(const BSTree* aTree) {
    

}

BSTree::~BSTree() {

}

//
bool BSTree::isEmpty() const {
	return rootPtr == nullptr; // if root is nullptr then tree is empty
}

int BSTree::getHeight() const {
	return 0;
}

int BSTree::getNumOfNodes() const {
	return 0;
}

int BSTree::getRootData() const {
	return rootPtr->data;
}

void BSTree::setRootData(const int newData) {
    rootPtr->data = newData;
}

bool BSTree::add(const int newData) {
    LeafNode* tempNode = new LeafNode(newData); // start by creating a new ptr
    // should check and set leafState in this method
    // if tree is empty then set it as the root
    // 
    // if node is now a leaf then turn into a threaded node
    // clear and delete all pointer variables created
    tempNode = nullptr;
    delete tempNode;
	return true;
}

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
