
#include "BSTree.h"
#include <iostream>


// constructor
BSTree::BSTree():root(nullptr) {}

// copy constructor
BSTree::BSTree(const BSTree& rhs) {
    copy_helper(rhs.root, root);
}

// move constructor
BSTree::BSTree(BSTree&& rhs):BSTree() {
    swap(*this, rhs);
}

// assignment operator (copy and move)
BSTree& BSTree::operator=(BSTree rhs) {
    swap(*this, rhs);
    return *this;
}

// destructor
BSTree::~BSTree() {
    destruct_helper(root);
}

// find a node by key
// attention: nested class as output parameter must be
// initialized with clas scope
void BSTree::find(int key) const {
    Node* ans = find(key, root);
    if (!ans) {
        std::cout << key << " was NOT found\n";
    } else {
        std::cout << key << " was found\n";
    }
}

// pre_order traversal: parent-left-right
void BSTree::print_pre_order() const {
    std::cout << std::endl;
    if (!root) {
        std::cout << "tree is empty\n";
    } else {
        print_pre_order(root);
    }
    std::cout << std::endl << std::endl;
}

// in_order traversal: left-parent-right
// output is ordered by size of key_val
void BSTree::print_in_order() const {
    std::cout << std::endl;
    if (!root) {
        std::cout << "tree is empty\n";
    } else {
        print_in_order(root);
    }
    std::cout << std::endl << std::endl;
}

// post_order traversal: left-right-parent
void BSTree::print_post_order() const {
    std::cout << std::endl;
    if (!root) {
        std::cout << "tree is empty\n";
    } else {
        print_post_order(root);
    }
    std::cout << std::endl << std::endl;
}

// insert a new node
void BSTree::insert(int key) {
    Node* new_node    = new Node;
    new_node->key_val = key;
    new_node->left    =  nullptr;
    new_node->right   =  nullptr;
    if (!root) {
        root = new_node;
    } else {
        insert(new_node, root);
    }
}

// remove the item passed as argument from the tree
void BSTree::remove(int val) {
    Node* ans = find(val, root);
    if (!ans) {
        std::cout << val << " is NOT in the tree\n";
    } else {
        remove_data(val, root);
    }
}


// utility functions - - - - - - - - - - - - - - - - - - -


// utility function used by copy constructor
void BSTree::copy_helper(Node* from, Node*& to) {
    if (!from) {
        to = nullptr;
    } else {
        to = new Node;
        to->key_val = from->key_val;
        copy_helper(from->left, to->left);
        copy_helper(from->right, to->right);
    }
}

// utility function used by destructor
void BSTree::destruct_helper(Node* leaf) {
    if (!leaf) {return;}
    destruct_helper(leaf->left);
    destruct_helper(leaf->right);
    delete leaf;
}

// utility function used by find(int key)
BSTree::Node* BSTree::find(int key, Node* leaf) const {
    if (!leaf){
        return nullptr;
    } else {
        if (key == leaf->key_val) {
            return leaf;
        } else if (key < leaf->key_val) {
            return find(key, leaf->left);
        } else {
            return find(key, leaf->right);
        }
    }
}

// utility function used by print_pre_order()
void BSTree::print_pre_order(Node* leaf) const {
    if (!leaf) {return;}
    std::cout << leaf->key_val << " ";
    print_pre_order(leaf->left);
    print_pre_order(leaf->right);
}

// utility function used by print_in_order()
void BSTree::print_in_order(Node* leaf) const {
    if (!leaf) {return;}
    print_in_order(leaf->left);
    std::cout << leaf->key_val << " ";
    print_in_order(leaf->right);
}

// utility function used by print_post_order()
void BSTree::print_post_order(Node* leaf) const {
    if (!leaf) {return;}
    print_post_order(leaf->left);
    print_post_order(leaf->right);
    std::cout << leaf->key_val << " ";
}

// utility function used by insert(int key)
void BSTree::insert(Node* new_node, Node* leaf) {
    if (new_node->key_val < leaf->key_val) {
        if (leaf->left == nullptr) {
            leaf->left = new_node;
        } else {
            insert(new_node, leaf->left);
        }
    } else if (new_node->key_val > leaf->key_val) {
        if (leaf->right == nullptr){
            leaf->right = new_node;
        } else {
            insert(new_node, leaf->right);
        }
    } else {
        std::cout << new_node->key_val << " already exist!";
        std::cout << std::endl;
        return;
    }
}

// these two utility functions are used by remove()
void BSTree::remove_data(int val, Node*& leaf) {
    if (val == leaf->key_val) {
        remove_node(leaf);
    } else if (val < leaf->key_val) {
        remove_data(val, leaf->left);
    } else {
        remove_data(val, leaf->right);
    }
}
void BSTree::remove_node(Node*& tree_node) {
    Node* del_ptr = tree_node;
    // case 0: Node has zero childeren
    if (!(tree_node->left) && !(tree_node->right)) {
        delete del_ptr;
        tree_node = nullptr;
    // case 1: Node has 1 child on left
    } else if (tree_node->left && !(tree_node->right)) {
        tree_node = tree_node->left;
        // disconect the old node from the tree
        del_ptr->left = nullptr;
        delete del_ptr;
    // case 2: Node has 1 child on right
    } else if (!(tree_node->left) && tree_node->right) {
        tree_node = tree_node->right;
        // disconect the old node from the tree
        del_ptr->right = nullptr;
        delete del_ptr;
    // case 3: Node has 2 children
    } else {
        Node* parent = tree_node;
        Node* left_most = tree_node->right;
        while (left_most->left) {
            parent = left_most;
            left_most = parent->left;
        }
        tree_node->key_val = left_most->key_val;
        del_ptr = left_most;
        if (parent == tree_node) {
            parent->right = left_most->right;
        } else {
            parent->left  = left_most->right;
        }
        delete del_ptr;
    }
}


