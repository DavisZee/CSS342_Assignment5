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
  // state of if this node is a leaf node or not
  // if it is a leaf node then it will be true, otherwise false
 bool leafState;

  // child nodes
  LeafNode* leftChild;
  LeafNode* rightChild;

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

protected:
  // helper methods
  int getHeightHelper (LeafNode* subTreePtr) const;
  int getNumOfNodesHelper(LeafNode* subTreePtr) const;

  // Recursively adds nodes left then right to keeps tree balanced, this is 
  // an unnecessarry method, does not need to be implemented
  auto balancedAdd(LeafNode* subTreePtr, LeafNode* newNodePtr);

  // removes target value from tree, supposed to be virtual auto return type
  // in the book. Changed to bool return type
  bool removeValue(LeafNode* subTreePtr, const int target);

  // copies values up tree to overwrite value in current node until a node is 
  // reached. The node is then removed since its value is stored in the parent
  auto moveValuesUpTree(LeafNode* subTreePtr);

  // recursively searches for target value, returns nullptr if not found.
  // changed from auto to node pointer
  LeafNode* findNode(LeafNode* treePtr, const int target) const;

  // copies the tree rooted at treePtr and returns a pointer to the root of
  // the copy. Changed from auto to bool
  bool copyTree(const LeafNode* oldTreeRootPtr) const;

  // recursively deletes all nodes from tree
  void burnTheTree(LeafNode* subTreePtr);

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
  int getEntry(const int anEntry); // I think its supposed to be a getItem also throws exception
  bool contains(const int anEntry) const;

  // traversal methods
  void preorderTrav(void visit(int&)) const;
  void inorderTrav(void visit(int&)) const;
  void postorderTrav(void visit(int&)) const;

  // overload ops
  BSTree& operator= (const BSTree& rightHandSIde);

}; // end of BSTree

#endif // BSTREE_H