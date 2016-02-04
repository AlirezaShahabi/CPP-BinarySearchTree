
// tester function


#include "BST.h"
#include <iostream>


int main() {
    
    BST<int> bst1;
        
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
    bst1.print_level_order();
    bst1.find(8);
    bst1.find(22);
    
    std::cout << "# of items: " << bst1.number_of_items() << std::endl;
    bst1.print_min();
    bst1.print_max();
    bst1.print_height();
    
    // test copy constructor
    BST<int> bst2(bst1);
    bst2.print_in_order();
    BST<int> bst3 = bst1;
    bst3.print_in_order();
    
    bst1.print_in_order();
    // test member function
    int key_vals[] = {10,9,19,27,1,-2,30,-9,23,4,-3,6,5,36,-8,25,26,7,8};
    for (int i = 0; i < 19; ++i) {
        bst2.remove(key_vals[i]);
        std::cout << "removed " << key_vals[i] << ", # of elements: ";
        std::cout << bst2.number_of_items() << ", tree:  ";
        bst2.print_in_order();
        std::cout << std::endl;
    }    
    
    // test member functions on an empty tree
    BST<int> bst4;
    bst4.print_in_order();
    bst4.remove(50);
    bst4.find(80);
    
    // test copy assignment operator
    bst4 = bst3;
    bst4.print_in_order();
        
    // test move constructor and move assignment operator
    BST<int> bst5 = std::move(bst3);
    bst5.print_in_order();
    
    BST<int> bst6;
    bst6.insert(45);
    bst6.insert(54);
    bst6.insert(50);
    bst6.insert(60);
    bst6.insert(11);
    
    bst6.print_in_order();
    bst6.print_level_order();
    std::cout << "# of items: " << bst6.number_of_items() << std::endl;
    bst6.print_min();
    bst6.print_max();
    bst6.print_height();
    
    bst6 = std::move(bst4);
    bst6.print_in_order();
    
    return 0;
}










