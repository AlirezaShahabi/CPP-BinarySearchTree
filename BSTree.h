
#ifndef BSTREE_H
#define BSTREE_H

#include <memory>

class BSTree {

friend void swap(BSTree&, BSTree&);

private:
    struct Node{
        int key_val;
        Node* left;
        Node* right;
    };
    Node* root;
    // utility function for copy construct/destruct
    void copy_helper(Node*, Node*&);
    void destruct_helper(Node*);
    // utility functions for find/print elements
    Node* find(int, Node*) const;
    void print_pre_order(Node*) const;
    void print_in_order(Node*) const;
    void print_post_order(Node*) const;
    // utility functions for add/remove elements
    void insert(Node*, Node*);
    void remove_data(int, Node*&);
    void remove_node(Node*&);
    
public:
    // constructor-copy/move/assignment-destruct
    BSTree();
    BSTree(const BSTree&);
    BSTree(BSTree&&);
    BSTree& operator=(BSTree);
    ~BSTree();
    // find - print
    void find(int) const;
    void print_pre_order() const;
    void print_in_order() const;
    void print_post_order() const;
    // add - remove
    void insert(int);
    void remove(int);
    
};

#endif

// friend function used by copy/move 
inline void swap(BSTree& lhs, BSTree& rhs) {
    using std::swap;
    swap(lhs.root, rhs.root);
}




