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
LeafNode::LeafNode() {

}

LeafNode::LeafNode(const int& data) {

}

LeafNode::LeafNode(const int& data, LeafNode* leftPtr, LeafNode* rightPt) {

}

void LeafNode::setData(const int& data) {

}

int LeafNode::getData() {
    return 0;
}

bool LeafNode::isLeafNode() const {
    return true;
}

auto LeafNode::getLeftLeafPtr() const {

}

auto LeafNode::getRightLeafPtr() const {

}

void LeafNode::setLeftLeaf(LeafNode* leftLeaf) {

}

void LeafNode::setRightLeaf(LeafNode* rightLeaf) {

}

//BSTree protected

int BSTree::getHeightHelper(LeafNode* subTreePtr) const {
	return 0;
}

int BSTree::getNumOfNodesHelper(LeafNode* subTreePtr) const {
	return 0;
}

auto BSTree::balancedAdd(LeafNode* subTreePtr, LeafNode* newNodePtr) {
	return;
}

bool BSTree::removeValue(LeafNode* subTreePtr, const int target) {
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

}

BSTree::BSTree(const int data) {

}

BSTree::BSTree(const int data, BSTree* leftTreePtr, BSTree* rightTreePtr) {

}

BSTree::BSTree(const BSTree* aTree) {

}

BSTree::~BSTree() {

}

bool BSTree::isEmpty() const {
	return true;
}

int BSTree::getHeight() const {
	return 0;
}

int BSTree::getNumOfNodes() const {
	return 0;
}

int BSTree::getRootData() const {
	return 0;
}

void BSTree::setRootData(const int newData) {

}

bool BSTree::add(const int newData) {
	return true;
}

bool BSTree::remove(const int data) {
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
