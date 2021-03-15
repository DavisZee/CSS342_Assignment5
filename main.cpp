/*
 * Created on 02/26/2021
 * Modified by Davis Zhong on 02/26/2021
 * 
*/

// testing gitHub
#include <iostream>
#include "BSTree.h"
#include <cassert>
using namespace std;



// Purpose: Tests basic constructors of the BSTree class.
// Preconditon: Requires no arguments, assumes the class is included
//              and the class constructors are available.
// Postcondition: Constructors ran, success message printed.
void testConstructors(){
    //works
    BSTree defaultTree();
    //works
    BSTree arrayTree(10);
    //works
    BSTree copyTree(arrayTree);
    cout << "Test Constructors Passed" << endl << endl;
    
} // end of testConstructors

// Purpose: Tests the success of the add methods of the BSTree class.
// Preconditon: No arguments required.
// Postcondition: all assertions pass, success message printed.
void testAdd() {
    BSTree BST1(5);
    assert(BST1.add(12));   //Test adding
    assert(BST1.add(25));   //Test linking to newly added number
    assert(BST1.add(11));   //Test linking to newly added number
    assert(BST1.add(-12));  //Test negative number

    // Making sure duplicates are not allowed
    assert(!BST1.add(12));
    assert(!BST1.add(-12));

    //Make sure to validate the construction of the tree with traversals
    //Make sure to use findNode to test if the threads work
    cout << "Test Add Passed" << endl << endl;
} // end of testAdd

// Purpose: To test the contains and remove methods.
// Preconditon: Requires no arguments.
// Postcondition: All assertions pass, success message printed.
void testContains() {
    BSTree BST1(10);
    assert(BST1.contains(3));   //Test contains and return false
    assert(!BST1.contains(12)); //Test contains and return false
    assert(!BST1.contains(0));  //Test avoiding dummy node

    assert(BST1.add(14));       //Add new node 
    assert(BST1.contains(14));  //Test contains on new node
    assert(BST1.add(-122));     //Add new negative node
    assert(BST1.contains(-122));//Test contains on new negative node]
    assert(BST1.add(12));       //Add new node in between
    assert(BST1.contains(12));  //Test contains on new node that is not largest

    assert(BST1.remove(12));    //Remove a value
    assert(!BST1.remove(12));   //check contains on removed value

    cout << "Test Contains Passed" << endl << endl;

    //Add tests for contains after removal
} // end of testContains

// Purpose: To test the remove method of the BSTree class.
// Preconditon: No arguments required.
// Postcondition: All assertions pass, success message printed.
void testRemove() {
    BSTree BST1(10);
    assert(BST1.remove(2));        //Test remove
    assert(!BST1.remove(2));       //Test duplicate remove
    assert(BST1.add(2));           //Add value again
    assert(BST1.remove(2));        //Test added value
    assert(!BST1.remove(123));     //Test non-existent value
    assert(BST1.add(13));          //Add new value
    assert(BST1.remove(13));       //Remove recently added value

    cout << "Test Remove Passed" << endl << endl;
} // end of testRemove

// Purpose: To test the traversal method of the BSTree class
// Preconditon: No arguments required.
// Postcondition: All assertions pass, success message printed.
void testTraversal() {
    
    BSTree BST1(5);                             
    string str = BST1.inorderTrav();                        
    assert(str == "1 2 3 4 5 ");            //Test inorderTraversal
    assert(BST1.add(23));
    assert(BST1.add(-1));
    str = BST1.inorderTrav();
    assert(str == "-1 1 2 3 4 5 23 ");      //Test traversal after addition
    assert(!BST1.add(1));
    str = BST1.inorderTrav();
    assert(str == "-1 1 2 3 4 5 23 ");      //Test traversal after failed addition

    assert(BST1.remove(3));
    str = BST1.inorderTrav();
    assert(str == "-1 1 2 4 5 23 ");        //Test traversal after deletion
    assert(BST1.remove(2));
    str = BST1.inorderTrav();
    assert(str == "-1 1 4 5 23 ");          //Test traversal after second deletion
    assert(!BST1.remove(2));
    str = BST1.inorderTrav();
    assert(str == "-1 1 4 5 23 ");          //Test traversal after failed deletion

    assert(BST1.add(45));                 
    assert(BST1.add(3));
    assert(BST1.add(2));
    str = BST1.inorderTrav();
    assert(str == "-1 1 2 3 4 5 23 45 ");   //Test traversal after multiple addition and deletion
    
    BSTree copyTree(BST1);
    str = copyTree.inorderTrav();
    assert(str == "-1 1 2 3 4 5 23 45 ");   //Test traversal on copy tree

    cout << "Test Traversal Passed" << 
    endl << endl;
} // end of test traversal

// Purpose: To run tests that are required in the assignment. Create a threaded
//          binary tree of a size n then remove all even numbers from the tree.
// Preconditon: No arguments required.
// Postcondition: assertion passes, success message ran.
void assignmentTest() {
    //Create tree with 20 nodes
    int size = 40;
    BSTree myTree(size);
    //Delete only the even nodes
    for (int i = 2; i <= size; i+=2) {
        myTree.remove(i);
    }
    string str = myTree.inorderTrav();
    assert(str == "1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 ");
    
    cout << "Assignment Test Passed" << endl << endl;
}

// Purpose: To test the outstream operator overload of BSTree class.
// Preconditon: No arguments required.
// Postcondition: Success fully prints out the tree in order.
void testOutStream() {
    BSTree BST1(8); 
    //
    // testing my << operator
    //
    cout << BST1 << endl;
    cout << "Ostream Test Passed" << endl << endl;
}

// Purpose: Main method.
// Preconditon: No arguments required.
// Postcondition: All tests that are called passes, successful execution
//                message printed.
int main() {
    cout << "Begin Testing!" << endl << endl;
    // test1();
    //int a = 5;
    testConstructors();
    testAdd();    
    testContains();
    testRemove();
    //testTraversal();
    testOutStream();
    cout << "************BEGIN ASSIGNMENT REQUIRED TEST************" << endl;
    //assignmentTest();
    cout << "Done!" << endl;

    return 0;
} // end of main