
// tester function


#include "BSTree.h"
#include <iostream>


int main() {
    
    BSTree bst1;
    
    // test member function
    bst1.insert(10);
    bst1.insert(23);
    bst1.insert(4);
    bst1.insert(9);
    bst1.insert(19);
    bst1.insert(27);
    bst1.insert(1);
    bst1.insert(30);
    bst1.insert(25);
    bst1.insert(6);
    bst1.insert(5);
    bst1.insert(36);
    bst1.insert(-2);
    bst1.insert(-8);
    bst1.insert(-9);
    bst1.insert(-3);
    bst1.insert(26);
    bst1.insert(7);
    bst1.insert(8);
    
    bst1.insert(8);
    bst1.print_pre_order();
    bst1.print_in_order();
    bst1.print_post_order();
    bst1.find(8);
    bst1.find(22);
    
    // test copy constructor
    BSTree bst2(bst1);
    bst2.print_in_order();
    BSTree bst3 = bst1;
    bst3.print_in_order();
    
    // test member function
    int key_vals[] = {10,9,19,27,1,-2,30,-9,23,4,-3,6,5,36,-8,25,26,7,8}; 
    for (int i=0; i<19; ++i) {
        std::cout << "removing " << key_vals[i] << ":  ";
        bst2.remove(key_vals[i]);
        bst2.print_in_order();
    }
    
    // test member functions on an empty tree
    BSTree bst4;
    bst4.print_in_order();
    bst4.remove(50);
    bst4.find(80);
    
    // test copy assignment operator
    bst4 = bst3;
    bst4.print_in_order();
        
    // test move constructor and move assignment operator
    BSTree bst5 = std::move(bst3);
    bst5.print_in_order();
    
    BSTree bst6;
    bst6.insert(45);
    bst6.insert(54);
    bst6.insert(50);
    bst6.insert(60);
    bst6.insert(11);
    
    bst6.print_in_order();
    bst6 = std::move(bst4);
    bst6.print_in_order();
    
    return 0;
}


