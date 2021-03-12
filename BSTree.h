/*
 * Created on 02/26/2021
 * Modified by Davis Zhong on 02/26/2021
 * Modified by Affan Dhankwala on 3/3/2021
 * 
*/
#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

using namespace std;

// only BinarySearchTree class can create LeafNode objects

class BSTree;

// LeafNode is a node of the BSTree
class LeafNode {
  friend class BSTree;
  friend ostream &operator<<(ostream &out, const BSTree &tree);

private:
  // constructor
  // explicit LeafNode(int value);

  // data contained in the object
  int data{0};
  // child nodes
	LeafNode* leftChild, *rightChild;
  // left and right threads
  // if either is true, then there is a node in that direction
  // if false, then there is a thread in that direction
	bool lThread, rThread;


public:
  // constructors
  LeafNode();
  LeafNode(const int& data);
  LeafNode(const int& data, LeafNode* leftPtr, LeafNode* rightPtr);

  // setters and getters for the data
  void setData(const int& data);
  int getData();

  // checks if the node has any children nodes
  bool isLeafNode() const;

  // setters and getters for child pointers
  auto getLeftChildPtr() const;
  auto getRightChildPtr() const;

  void setLeftChild(LeafNode* leftLeaf);
  void setRightChild(LeafNode* rightLeaf);

}; // end of LeafNode

class BSTree {
  // display
  friend ostream &operator<<(ostream &out, const BSTree &tree);

private:
  // pointer to the root of the BSTree
  LeafNode* rootPtr;

  // Helpert to convert a sorted array into a tree
  LeafNode* sortedArrToTree(int arr[], int start, int end);
  


protected:
  // helper methods
  int getHeightHelper (LeafNode* subTreePtr) const;
  int getNumOfNodesHelper(LeafNode* subTreePtr) const;

  // Recursively adds nodes left then right to keeps tree balanced, this is 
  // an unnecessarry method, does not need to be implemented
  void balancedAdd(int start, int end);

  // recursively searches for target value, returns nullptr if not found.
  // changed from auto to node pointer
  LeafNode* findNode(LeafNode* treePtr, const int target) const;

  // copies the tree rooted at treePtr and returns a pointer to the root of
  // the copy. Changed from auto to bool
  LeafNode* copyTree( LeafNode* oldTreeRootPtr);

  void deleteNoChild(LeafNode* ptr, LeafNode* parent);

  void deleteOneChild(LeafNode* ptr, LeafNode* parent);

  void deleteTwoChild(LeafNode* ptr, LeafNode* parent);

  LeafNode* inorderSuccessor(LeafNode* ptr);

  LeafNode* inorderPredecessor(LeafNode* ptr);

  // recursive traversal helper methods, might not be all necessary
  void preorder(void visit(int), LeafNode* treePtr);
  void inorder(void visit(int), LeafNode* treePtr);
  void postorder(void visit(int), LeafNode* treePtr);

public:
  // constructor and destructors
  BSTree();
  BSTree(const int data);
  BSTree(const int data, BSTree* leftTreePtr, BSTree* rightTreePtr);
  BSTree(const BSTree* aTree);

  virtual ~BSTree();

  // BSTree interface methods
  bool isEmpty() const;
  int getHeight() const;
  int getNumOfNodes() const;
  int getRootData() const; // supposed to also throw PrecondViolatedExcept
  void setRootData(const int newData);
  bool add(const int newData);
  bool remove(const int data);
  void clear();
  bool contains(const int anEntry) const;
  // toString by level
  string toStringGivenLevel(LeafNode* root, int level);
  // toString all levels
  string toStringTree();

  string inorderTrav();

  // overload ops
  BSTree& operator= (const BSTree& rightHandSIde);

}; // end of BSTree

#endif // BSTREE_H