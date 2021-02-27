/*
 * Created by Davis Zhong on 02/26/2021
 *
 * 
*/
#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

using namespace std;

// only BinarySearchTree class can create Leaf objects

class BSTree;

class Leaf {
  friend class BSTree;
  friend ostream &operator<<(ostream &out, const BSTree &tree);

private:
  // constructor
  explicit Leaf(int value);

  // data contained in the object
  int data{0};

};

class BSTree {
  // display
  friend ostream &operator<<(ostream &out, const BSTree &tree);

private:
  
public:
  
};

#endif // BSTREE_H