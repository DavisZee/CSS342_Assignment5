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

int main() {
    cout << "Begin Testing!" << endl << endl;
    // test1();
    int a = 5;
    cout << "Done!" << endl;
    return 0;
}