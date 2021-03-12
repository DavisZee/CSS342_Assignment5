/*
 * Created on 02/26/2021
 * Modified by Davis Zhong on 02/26/2021
 * 
*/

// testing gitHub
// should test for duplicates because duplicates not allowed
#include <iostream>
#include "BSTree.h"
#include <cassert>
using namespace std;

void test1() {
    cout << "Hello" << endl;
}

void test2() {
    cout << boolalpha; // prints boolean values as true/false rather than 1/0
    BSTree myTree; // tree object creation
    //
    //test tree by adding in numbers 1 through 10 
    //
    int num(10);
    for (int i = 0; i < num; i++) { // loops 10 times
        assert(myTree.add(i)); // if fail to add then fail assert
    }
    cout << myTree << endl;

}

void testConstructors(){
    //works
    BSTree defaultTree();
    //works
    BSTree arrayTree(10);
    //works
    BSTree copyTree(arrayTree);
    cout << "Test Constructors Passed" << endl;
    
}
void testAdd() {
    BSTree BST1(5);
    assert(BST1.add(12));   //Test adding
    assert(BST1.add(25));   //Test linking to newly added number
    assert(BST1.add(11));   //Test linking to newly added number
    assert(BST1.add(-12));  //Test negative number

    assert(!BST1.add(12));
    assert(!BST1.add(-12));

    //Make sure to validate the construction of the tree with traversals
    //Make sure to use findNode to test if the threads work
    cout << "Test Add Passed" << endl;
}
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

    cout << "Test Contains Passed" << endl;

    //Add tests for contains after removal
}

void testRemove() {
    BSTree BST1(10);
    assert(BST1.remove(2));        //Test remove
    assert(!BST1.remove(2));       //Test duplicate remove
    assert(BST1.add(2));           //Add value again
    assert(BST1.remove(2));        //Test added value
    assert(!BST1.remove(123));     //Test non-existent value
    assert(BST1.add(13));          //Add new value
    assert(BST1.remove(13));       //Remove recently added value

    cout << "Test Remove Passed" << endl;
}

int main() {
    cout << "Begin Testing!" << endl << endl;
    // test1();
    //int a = 5;
    testConstructors();    
    testAdd();    
    testContains();
    testRemove();
    cout << "Done!" << endl;
    return 0;
}