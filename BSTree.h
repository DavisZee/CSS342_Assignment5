/*
 * Assignment 5
 *
 * By Davis Zhong
 * By Affan Dhankwala
 *
 * Due: March 14, 2021
 *
 * This class defines all the necessary methods that we plan on using in the 
 * BSTree class. It also has methods from the LeafNode class that we likewise
 * implement and use as the nodes for our tree. This code contains helper 
 * methods and public methods all indicated by the headings. Each methods
 * purpose, precondition, and postconditions describing their behavior
 * and implementation. 
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
	bool hasLeftChild, hasRightChild;


public:
  // constructors

  // Purpose: Default no arg constructor of LeafNode.
  // Preconditon: No arguments in object creation.
 // Postcondition: All variables of LeafNode are set to defaults.
  LeafNode();

  // Purpose: Constructor with data in argument.
  // Preconditon: Integer variable is argument in object creation.
  // Postcondition: LeafNode variables are set to defaults but data is assigned
  //                to newData input.
  LeafNode(const int& data);

}; 
  // end of LeafNode

class BSTree {

  // Purpose: Print out inorder traversal ofBSTree instance to console
  // Precondition: tree is not null
  // Postcondition: Returns ostream out that stores inorder traversal of tree
  friend ostream &operator<<(ostream &out, const BSTree &tree);

private:

  // pointer to the root of the BSTree
  LeafNode* rootPtr;
    
protected:

  // helper methods
 
  // Purpose: To help add values to a tree in a balanced order, mainly used in
  //          BSTree(int) constructor.
  // Preconditon: Argument call has two integer values, start is not equivalent
  //              to end.
  // Postcondition: Values are added to the tree in a balanced fashion.
  void balancedAdd(int start, int end);

  // Purpose: Finds a target node in a tree.
  // Preconditon: LeafNode pointer and int target data is not null.
  // Postcondition: Node is either found or not found and a pointer/nullptr is
  //                returned accordingly.
  LeafNode* findNode(LeafNode* treePtr, const int target) const;

  // Purpose: Creates an deep copy of tree
  // Preconditon: oldTreeRootPtr is not nullptr
  // Postcondition: Creates a new instance of tree and is identical copy
  void copyTree( LeafNode* oldTreeRootPtr);

  // Purpose: To reroute parent pointers if target has no children.
  // Preconditon: LeafNode pointers of parent and ptr are not nullptr.
  // Postcondition: parent pointers are rerouted and target node is deleted.
  void deleteNoChild(LeafNode* ptr, LeafNode* parent);

  // Purpose: To reroute parent pointers if target has a child node.
  // Preconditon: ptr must have a child node, LeafNodes are not nullptr.
  // Postcondition: Child node is deleted and parent pointers are rerouted.
  void deleteOneChild(LeafNode* ptr, LeafNode* parent);

  // Purpose: To delete a node with two children nodes, link them to the parent,
  //          and thread them accordingly.
  // Preconditon: LeafNodes are not null.
  // Postcondition: Target node deleted and everything is linked properly.
  void deleteTwoChild(LeafNode* ptr, LeafNode* parent);

  // Purpose: Looks for the next successor of the target node.
  // Preconditon: LeafNode pointer is not nullptr.
  // Postcondition: Successor is found and returned.
  LeafNode* inorderSuccessor(LeafNode* ptr);

  // Purpose: Looks for the predecessor the the target node.
  // Preconditon: LeafNode pointer is not nullptr.
  // Postcondition:  Predecessor is found and returned.
  LeafNode* inorderPredecessor(LeafNode* ptr);

  // recursive traversal helper method

  // Purpose: Conducts inorder traversal of tree and stores all 
  //          node datas in order. 
  // Precondition: BSTree is not null and root is not null
  // Postcondition: Returns string of all nodes in tree
  string inorder(LeafNode* treePtr);

public:
  // constructor and destructors

  // Purpose: Create a null instance of BSTree and allocate dummy node
  // Preconditon: None
  // Postcondition: Creates BSTree object with dummy node
  BSTree();

  // Purpose: Populate the BSTree object with numbers from 1 - data
  //          and ensure a balanced tree. Also call default constructor
  //          to retain dummy node
  // Preconditon: BSTree is not null and data > 0
  // Postcondition: Creates BSTree object with n = data nodes
  BSTree(const int data);

  // Purpose: Copy constructor for BSTree.
  // Preconditon: Has a BSTree object in argument that is not null.
  // Postcondition: A copy of the tree in argument is created.
  BSTree(const BSTree &aTree);

  // Purpose: Destructor for BSTree.
  // Preconditon: No arguments.
  // Postcondition: Tree is empty and all nodes are deleted properly with no
  //                memory leaks.
  virtual ~BSTree();

  // BSTree interface methods

  // Purpose: Checks to see if the BSTree is empty.
  // Preconditon: No arguments.
  // Postcondition: boolean value of whether the tree is empty is returned.
  bool isEmpty() const;

  // Purpose: To add a new element of int value into the tree as a node.
  // Preconditon: Integer variable in argument is not null.
  // Postcondition: Value is either successfully added to the tree or is not
  //                added to the tree, boolean value returned.
  bool add(const int newData);

  // Purpose: To remove node with provided data value.
  // Preconditon: Integer variable in argument is not null.
  // Postcondition: Node is either not found or removed from the tree and 
  //                corresponding boolean value is returned.
  bool remove(const int data);

  // Purpose: To traverse and delete all nodes in tree.
  // Preconditon: LeafNode pointer is not nullptr.
  // Postcondition: All nodes deleted, tree is empty, no mem leaks.
  void clear(LeafNode* root);

  // Purpose: Return a boolean indicating if a target Entry is present
  // Preconditon: BSTree object cannot be null
  // Postcondition: Returns boolean indicating if target found
  bool contains(const int anEntry) const;

  // Purpose: Traverse threaded binary search tree in order.
  // Preconditon: No arguments in parameter.
  // Postcondition: Tree is traversed in order and a string of data in order is
  //                returned.
  string inorderTrav();

}; // end of BSTree

#endif // BSTREE_H