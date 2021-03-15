/*
 * Assignment 5
 * 
 * By Davis Zhong
 * By Affan Dhankwala
 * 
 * Due: March 14, 2021
 * 
 * This class allows for the creation of a doubly threaded Binary Search 
 * Tree object and relies on the class of LeafNodes as nodes. It also 
 * conducts searching, adding, and remove in Olog(N) time complexity 
 * by comparing only the required nodes. This class has an overloaded ostream
 * operator to print out any tree's inorder traversal. The traversal's 
 * time complexity is O(N) because it has to traverse every node and print
 * its details. The traversal is done solely through treading with no recursion
 * to backtrack. This class also implements a dummy node to simplify the addition
 * and removal operations and all of the tree remains on the left side of said
 * Dummy node. Since the dummy node's default value is 0, this prohibits the 
 * addition of 0 to our tree. THIS IS A RESTRICTION ON THE TREE. Valgrind and 
 * Clangtidy have been run on this code and resulted in no memory leakage
 * and no warnings.
 * 
*/
#include <cassert>
#include <iostream>
#include <string>

#include "BSTree.h"

using namespace std;

 
// Purpose: Default no arg constructor of LeafNode.
// Preconditon: No arguments in object creation.
// Postcondition: All variables of LeafNode are set to defaults.
LeafNode::LeafNode() : leftChild{ this }, rightChild{ this }, hasLeftChild{ false }, 
hasRightChild{ false }
{}

// Purpose: Constructor with data in argument.
// Preconditon: Integer variable is argument in object creation.
// Postcondition: LeafNode variables are set to defaults but data is assigned
//                to newData input.
LeafNode::LeafNode(const int& newData) : data{newData}, leftChild{nullptr}, 
    rightChild{nullptr}, hasLeftChild{ false }, hasRightChild{ false }
{}

// Purpose: Print out inorder traversal ofBSTree instance to console
// Precondition: tree is not null
// Postcondition: Returns ostream out that stores inorder traversal of tree
ostream& operator<<(ostream& out, const BSTree& tree) {

    BSTree aTree = tree;
    return out << aTree.inorder(tree.rootPtr);

} 
// end of << op overload

// BSTree protected

// Purpose: To help add values to a tree in a balanced order, mainly used in
//          BSTree(int) constructor.
// Preconditon: Argument call has two integer values, start is not equivalent
//              to end.
// Postcondition: Values are added to the tree in a balanced fashion.
void BSTree::balancedAdd(int start, int end) {
    // Base case: if start is greater than end the tree has added all available
    // values and should begin returning
    if (start > end) return;
    // find mid point between start and end
    int mid = (start + end) / 2;
    // call add method
    add(mid);
    // recursive bottom half
    balancedAdd(start, mid - 1);
    // recursive top half
    balancedAdd(mid + 1, end);

} // end of balancedAdd
// Purpose: Finds a target node in a tree.
// Preconditon: LeafNode pointer and int target data is not null.
// Postcondition: Node is either found or not found and a pointer/nullptr is
//                returned accordingly.
LeafNode* BSTree::findNode(LeafNode* treePtr, const int target) const {
    if (treePtr->data == target) return treePtr;
    //If there is nowhere to go then we have hit the bottom and have not found node.
    else if (treePtr->hasRightChild == false && treePtr->hasLeftChild == false) return nullptr;

    else if (treePtr->data > target) return findNode(treePtr->leftChild, target);

    else if (treePtr->data < target) return findNode(treePtr->rightChild, target);

    //At this point, target was not in the tree and thus return null ptr
    return nullptr;
}

// Purpose: Creates an deep copy of tree
// Preconditon: oldTreeRootPtr is not nullptr
// Postcondition: Creates a new instance of tree and is identical copy
void BSTree::copyTree(LeafNode* oldTreeRootPtr) {

    if (oldTreeRootPtr->data == rootPtr->data)
        return;
    add(oldTreeRootPtr->data);

    if (oldTreeRootPtr->hasLeftChild)
        copyTree(oldTreeRootPtr->leftChild);

    if (oldTreeRootPtr->hasRightChild)
        copyTree(oldTreeRootPtr->rightChild);
}

// Purpose: To reroute parent pointers if target has no children.
// Preconditon: LeafNode pointers of parent and ptr are not nullptr.
// Postcondition: parent pointers are rerouted and target node is deleted.
void BSTree::deleteNoChild(LeafNode* ptr, LeafNode* parent) {
    // checks whether the target is the left or right child of the parent
    if (ptr == parent->leftChild) {
        //Now the left thread of parent is a thread
        parent->hasLeftChild = false;
        parent->leftChild = ptr->leftChild;
    }
    else {
        // linking pointers
        parent->hasRightChild = false;
        parent->rightChild = ptr->rightChild;
    } // end of if
    // clean up ptr
    delete ptr;
    ptr = nullptr;
} // end of deleteNoChild

// Purpose: To reroute parent pointers if target has a child node.
// Preconditon: ptr must have a child node, LeafNodes are not nullptr.
// Postcondition: Child node is deleted and parent pointers are rerouted.
void BSTree::deleteOneChild(LeafNode* ptr, LeafNode* parent) {
    LeafNode* child;
    // Find out whether ptr has right or left child
    if (ptr->hasLeftChild) {
        child = ptr->leftChild;
    }
    else {
        child = ptr->rightChild;
    } // end if

    // link left/right child accordingly
    if (ptr == parent->leftChild) {
        parent->leftChild = child;
    }
    else parent->rightChild = child;
    // end if

    // find successor and predecessor of the ptr node
    LeafNode* successor = inorderSuccessor(ptr);
    LeafNode* predecessor = inorderPredecessor(ptr);
    // link threads together
    if (ptr->hasLeftChild) {
        predecessor->rightChild = successor;
    }
    else if (ptr->hasRightChild) successor->leftChild = predecessor;
    // clean up ptr
    delete ptr;
    ptr = nullptr;
} // end of deleteonechild method

// Purpose: To delete a node with two children nodes, link them to the parent,
//          and thread them accordingly.
// Preconditon: LeafNodes are not null.
// Postcondition: Target node deleted and everything is linked properly.
void BSTree::deleteTwoChild(LeafNode* ptr) {
    // find the successor nodes for ptr and the parent
    LeafNode* successor = ptr->rightChild;
    LeafNode* parentSuccessor = ptr;
    // traverse as far to the left as possible of the successor
    while (successor->hasLeftChild) {
        parentSuccessor = successor;
        successor = successor->leftChild;
    } // end of while loop
    ptr->data = successor->data;

    // checks if successor is a leaf
    if ((!successor->hasLeftChild) && !(successor->hasRightChild)) deleteNoChild(successor, parentSuccessor);

    else deleteOneChild(successor, parentSuccessor);
    // end if
} // end of deleteTwoChild method

// Purpose: Looks for the next successor of the target node.
// Preconditon: LeafNode pointer is not nullptr.
// Postcondition: Successor is found and returned.
LeafNode* BSTree::inorderSuccessor(LeafNode* ptr) {
    //If there is a thread then return the next threaded node
    if (!ptr->hasRightChild) {
        return ptr->rightChild;
    }
    //If no thread then inorder successor is the leftmost node of node to right
    ptr = ptr->rightChild;
    while (ptr->hasLeftChild) {
        ptr = ptr->leftChild;
    }
    return ptr;
}

// Purpose: Looks for the predecessor the the target node.
// Preconditon: LeafNode pointer is not nullptr.
// Postcondition:  Predecessor is found and returned.
LeafNode* BSTree::inorderPredecessor(LeafNode* ptr) {
    if (!ptr->hasLeftChild) {
        return ptr->leftChild;
    }
    ptr = ptr->leftChild;
    while (ptr->hasRightChild) {
        ptr = ptr->rightChild;
    }
    return ptr;
}

// Purpose: Conducts inorder traversal of tree and stores all 
//          node datas in order. 
// Precondition: BSTree is not null and root is not null
// Postcondition: Returns string of all nodes in tree
string BSTree::inorder(LeafNode* root) {
    LeafNode* ptr = root->leftChild;
    //Go to most left node
    while (ptr->hasLeftChild) {
        ptr = ptr->leftChild;
    }
    //At this point we are at the right-most node
    string traversal = "";
    //Continue right until we loop back to the dummy node
    while (ptr != root) {
        traversal += to_string(ptr->data) + " ";
        ptr = inorderSuccessor(ptr);
    }
    return traversal;
}

//BSTree public

// Purpose: Create a null instance of BSTree and allocate dummy node
// Preconditon: None
// Postcondition: Creates BSTree object with dummy node
BSTree::BSTree(){
   //In the case of empty, root will be a dummy node
   //Dummy node
    rootPtr = new LeafNode();
    //Link whole tree to be on left of dummy node
    rootPtr->hasRightChild = false;
    rootPtr->hasLeftChild = false;
    rootPtr->leftChild = rootPtr;
    rootPtr->rightChild = rootPtr;
}

// Purpose: Populate the BSTree object with numbers from 1 - data
//          and ensure a balanced tree. Also call default constructor
//          to retain dummy node
// Preconditon: Data > 0
// Postcondition: Creates BSTree object with n = data nodes
BSTree::BSTree(const int data) : BSTree() {
    //This method will add all values from 1 - data into BSTree
    //Call BalancedAdd to add all values into tree in correct order
    balancedAdd(1, data);

}

// Purpose: Copy constructor for BSTree.
// Preconditon: Has a BSTree object in argument that is not null.
// Postcondition: A copy of the tree in argument is created.
BSTree::BSTree(const BSTree& aTree) : BSTree(){
    // call to helper method that copies the tree
    copyTree(aTree.rootPtr->leftChild);
} 

// end of BSTree copy constructor

// Purpose: Destructor for BSTree.
// Preconditon: No arguments.
// Postcondition: Tree is empty and all nodes are deleted properly with no
//                memory leaks.
BSTree::~BSTree() {
    // calls helper method that traverses tree recursively
    // and deletes all nodes properly
    clear(rootPtr);
} 

// end of BSTree destructor

// Purpose: Checks to see if the BSTree is empty.
// Preconditon: No arguments.
// Postcondition: boolean value of whether the tree is empty is returned.
bool BSTree::isEmpty() const {
	return (rootPtr->hasLeftChild); // if root is nullptr then tree is empty
}

// Purpose: To add a new element of int value into the tree as a node.
// Preconditon: Integer variable in argument is not null.
// Postcondition: Value is either successfully added to the tree or is not
//                added to the tree, boolean value returned.
bool BSTree::add(const int newData) {
    LeafNode* tempNode = new LeafNode(newData);
    // first check if tree is empty
    if ((rootPtr->leftChild == rootPtr) && (rootPtr->rightChild == rootPtr)) {
        // At this point the tree is empty and only has dummy node
        // Reroute all pointers of root to tempNode
        tempNode->leftChild = rootPtr->leftChild;
        tempNode->rightChild = rootPtr->rightChild;
        // Insert tempNode into tree
        rootPtr->leftChild = tempNode;
        rootPtr->hasLeftChild = true;
        return true;
    }
    // Tree is not empty so we will add it
    // pointer for traversal that avoids the dummy node
    LeafNode* ptr = rootPtr->leftChild;

    // Keep looping until internally stopped by return
    while (true) {
        // check for duplicate value
        if (newData == ptr->data) {
            // clean up node in heap and return
            delete tempNode;
            tempNode = nullptr;
            return false; 
        }

        // if value is larger than the current node data then insert or move
        // to the right
        if (newData > ptr->data) {
            if (!ptr->hasRightChild) {
                tempNode->rightChild = ptr->rightChild;
                tempNode->hasRightChild = ptr->hasRightChild;
                tempNode->hasLeftChild = false;

                //Point to inorder successor 
                tempNode->leftChild = ptr;
                ptr->hasRightChild = true;
                ptr->rightChild = tempNode;
                return true;
            }else ptr = ptr->rightChild;
        } // end if
        
        // if value is smaller than current node data then insert or move left
        if (newData < ptr->data) {
            if (!ptr->hasLeftChild) {
                // At this point we know that the leftChild does not 
                // point to any inorder predecessor. 
                tempNode->leftChild = ptr->leftChild;
                tempNode->hasLeftChild = ptr->hasLeftChild;
                tempNode->hasRightChild = false;

                //Point to inorder successor 
                tempNode->rightChild = ptr;
                ptr->hasLeftChild = true;
                ptr->leftChild = tempNode;
                return true;
            }else ptr = ptr->leftChild;

        } // end if
    } // end while loop
} // end of add method

// Purpose: To remove node with provided data value.
// Preconditon: Integer variable in argument is not null.
// Postcondition: Node is either not found or removed from the tree and 
//                corresponding boolean value is returned.
bool BSTree::remove(const int data) {
    // Set parent to dummy node and our pointer to the real root
    LeafNode* parent = rootPtr, *ptr = rootPtr->leftChild;
    bool found = false;
    // Can use findNode function but we won't get the parent node 
    // (need that for linking)

    // Traverse tree until find target node and remember parent
    while (ptr != nullptr) {
        if (data == ptr->data) {
            found = true;   //We found the node
            break;
        }
        // assign parent before moving to the next node
        parent = ptr;

        // if data is less than current move left otherwise move right
        if (data < ptr->data){
            // check to see if at a leaf
            if (ptr->hasLeftChild == true) {
                ptr = ptr->leftChild;
            }
            else break;
        }
        else {
            // check to see if at a leaf
            if (ptr->hasRightChild == true) {
                ptr = ptr->rightChild;
            }
            else break;
        } // end if
    } // end of while loop
    // if not found then end method here and return false
    if (!found) return false;
    
    // At this point we have the target node and we have its parent as well

    // Now we have to remove and link the new nodes depending on their children

    // If ptr has two children, then both threads will be true and we would need to
    // reroute the pointers for both children
    if (ptr->hasRightChild && ptr->hasLeftChild) {
        deleteTwoChild(ptr);
    }
    //If ptr only has one child
    else if ((ptr->hasRightChild && !(ptr->hasLeftChild))||(!(ptr->hasRightChild) && (ptr->hasLeftChild))) {
        deleteOneChild(ptr, parent);
    }
 
    // If ptr has no children (is a leaf)
    else {
        deleteNoChild(ptr, parent);
    }
    // node removal is complete return true
	return true;
} // end of BSTree remove method

// Purpose: To traverse and delete all nodes in tree.
// Preconditon: LeafNode pointer is not nullptr.
// Postcondition: All nodes deleted, tree is empty, no mem leaks.
void BSTree::clear(LeafNode* trav) {
    // checks if nodes for leaf nodes, if not, recursively traverse and delete
    if (trav->hasLeftChild) {
            clear(trav->leftChild);
        }
    if (trav->hasRightChild) {
            clear(trav->rightChild);
    }
    
    //cout << " " << trav->data; 
    // clean up the current node
    delete trav;
    trav = nullptr;
} // end of clear method



// Purpose: Return a boolean indicating if a target Entry is present
// Preconditon: BSTree object cannot be null
// Postcondition: Returns boolean indicating if target found
bool BSTree::contains(const int anEntry) const {
    //Return true if findNode returns a ptr and false if returns nullptr
    return (findNode(rootPtr->leftChild, anEntry) != nullptr) ? true : false;
}

// Purpose: Traverse threaded binary search tree in order.
// Preconditon: BSTree object cannot be null
// Postcondition: Tree is traversed in order and a string of data in order is
//                returned.
string BSTree::inorderTrav() {    
    // calls a helper method to traverse tree in order using threads
    return inorder(rootPtr);
}

