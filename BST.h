#ifndef BST_H                                                                 //
#define BST_H

#include <iostream>
#include <string>
#include <vector>

template <typename T> class BST {

private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& inp):data(inp), left(nullptr), right(nullptr) {}
        Node():data(), left(nullptr), right(nullptr) {}
    };
    Node* root;
    std::size_t size;
    // utility functions used for copy-delete
    void copy_helper(Node*, Node*&);
    void delete_helper(Node*);
    // utility functions used for add/remove elements
    void insert(Node*&, Node*);
    bool remove(Node*&, const T&);
    void remove_node(Node*&);
    // utility functions used for depth first traversal
    void print_pre_order(Node*) const;
    void print_in_order(Node*) const;
    void print_post_order(Node*) const;
    // utility functions used for breadth first traversal
    void print_level(const std::vector<Node*>&) const;
    bool make_next_level(const std::vector<Node*>&, std::vector<Node*>&) const;
    // other utility functions
    Node* find(Node*, const T&) const;
    int height(Node*) const;

public:
    // constructor - assignment - destructor
    BST();
    BST(const BST&);
    BST(BST&&);
    BST& operator=(BST);
    ~BST();
    // swap
    void swap(BST&);
    // add/remove element
    void insert(const T&);
    void remove(const T&);
    // depth first traversal
    void print_pre_order() const;
    void print_in_order() const;
    void print_post_order() const;
    // bredth first traversal
    void print_level_order() const;
    // get other information from tree
    void find(const T&) const;
    inline std::size_t number_of_items() const {return size;}
    void print_min() const;
    void print_max() const;
    void print_height() const;
    bool check_empty() const;
};

#endif


// public member functions - - - - - - - - - - - - - - - - - - - - - - - - - -

// constructor
template <typename T> BST<T>::BST():root(nullptr), size(0) {}

// copy constructor
template <typename T> BST<T>::BST(const BST& rhs):root(nullptr), size(rhs.size)
{copy_helper(rhs.root, root);}

//move constructor
template <typename T> BST<T>::BST(BST&& rhs):BST() {swap(rhs);}

// assignment operator (copy and move)
template <typename T> BST<T>& BST<T>::operator=(BST rhs) {
    swap(rhs);
    return *this;
}

// destructor
template <typename T> BST<T>::~BST() {delete_helper(root);}

// swap two BST objects
template <typename T> void BST<T>::swap(BST& rhs) {
    using std::swap;
    swap(this->root, rhs.root);
    swap(this->size, rhs.size);
}

// add data to the tree
template <typename T> void BST<T>::insert(const T& data) {
    Node* new_node = new Node(data);
    if (!root) {
        root = new_node;
        ++size;
    } else {
        insert(new_node, root);
    }
}

// remove data from the tree
template <typename T> void BST<T>::remove(const T& data) {
    bool ans = remove(root, data);
    if (!ans) {std::cout << data << " is NOT in the tree" << std::endl;}
}

// print pre order
template <typename T> void BST<T>::print_pre_order() const {
    if (!check_empty()) {
        print_pre_order(root);
        std::cout << std::endl;
    }
}

// print in order
template <typename T> void BST<T>::print_in_order() const {
    if (!check_empty()) {
        print_in_order(root);
        std::cout << std::endl;
    }
}

// print post order
template <typename T> void BST<T>::print_post_order() const {
    if (!check_empty()) {
        print_post_order(root);
        std::cout << std::endl;
    }
}

// print level order
template <typename T> void BST<T>::print_level_order() const {
    if (!check_empty()) {
        std::vector<Node*> level1, level2;
        level1.push_back(root);
        print_level(level1);
        bool condition = make_next_level(level1, level2);
        while (condition) {
            level1 = level2;
            print_level(level1);
            level2.clear();
            condition = make_next_level(level1, level2);
        }
    }
}

// find whether or not tree contains data
template <typename T> void BST<T>::find(const T& data) const {
    Node* ans = find(root, data);
    std::string str = ans ? " FOUND " : " NOT FOUND ";
    std::cout << data << str << "in the tree" << std::endl;
}

// print the smallest value
template <typename T> void BST<T>::print_min() const {
    if (!check_empty()) {
        Node* left_most = root;
        while (left_most->left) {left_most = left_most->left;}
        std::cout << left_most->data << std::endl;
    }
}

// print the biggest value
template <typename T> void BST<T>::print_max() const {
    if (!check_empty()) {
        Node* right_most = root;
        while (right_most->right) {right_most = right_most->right;}
        std::cout << right_most->data << std::endl;
    }
}

// print the height of the tree
template <typename T> void BST<T>::print_height() const {
    std::cout << "height of the tree: " << height(root) << std::endl;
}

// check wether tree is empty
template <typename T> bool BST<T>::check_empty() const {
    if (!root) {
        std::cout << "Empty tree, nothing to show" << std::endl;
        return true;
    }
    return false;
}


// private utility functions - - - - - - - - - - - - - - - - - - - - - - - - -

// make a deep copy of all the nodes of the tree starting at source (root) to
// a new tree whith target as root
template <typename T> void BST<T>::copy_helper(Node* source, Node*& target) {
    if (!source) {return;}
    target = new Node(source->data);
    copy_helper(source->left, target->left);
    copy_helper(source->right, target->right);
}

// remove all the nodes of the tree starting at curr
template <typename T> void BST<T>::delete_helper(Node* curr) {
    if (!curr) {return;}
    delete_helper(curr->left);
    delete_helper(curr->right);
    delete curr;
}

// add the new_node to the tree with the curr as root
template <typename T> void BST<T>::insert(Node*& new_node, Node* curr) {
    if (new_node->data < curr->data) {
        if (!curr->left) {
            curr->left = new_node;
            ++size;
        } else {
            insert(new_node, curr->left);
        }
    } else if (new_node->data > curr->data) {
        if (!curr->right) {
            curr->right = new_node;
            ++size;
        } else {
            insert(new_node, curr->right);
        }
    } else {
        return;
    }
}

// remove data from the tree starting at curr
template <typename T> bool BST<T>::remove(Node*& curr, const T& data) {
    if (!curr) {return false;}
    if (data == curr->data) {
        remove_node(curr);
        --size;
        return true;
    } else if (data < curr->data) {
        return remove(curr->left, data);
    } else {
        return remove(curr->right, data);
    }
}

// remove the curr node from the tree
template <typename T> void BST<T>::remove_node(Node*& curr) {
    Node* del_node = curr;
    // case 0: Node has zero children
    if (!curr->left && !curr->right) {
        delete del_node;
        curr = nullptr;
    }
    // case 1: Node has 1 child on the left
    else if (curr->left && !curr->right) {
        curr = curr->left;
        del_node->left = nullptr;
        delete del_node;
    }
    // case 2: Node has 1 child on the right
    else if (!curr->left && curr->right) {
        curr = curr->right;
        del_node->right = nullptr;
        delete del_node;
    }
    // case 3: Node has 2 children
    else {
        Node* parent = curr;
        Node* left_most = curr->right;
        while (left_most->left) {
            parent = left_most;
            left_most = left_most->left;
        }
        curr->data = left_most->data;
        del_node = left_most;
        if (parent == curr) {
            parent->right = left_most->right;
        } else {
            parent->left = left_most->right;
        }
        delete left_most;
    }
}

// print pre order
template <typename T> void BST<T>::print_pre_order(Node* curr) const {
    if (!curr) {return;}
    std::cout << curr->data << " ";
    print_pre_order(curr->left);
    print_pre_order(curr->right);
}

// print in order
template <typename T> void BST<T>::print_in_order(Node* curr) const {
    if (!curr) {return;}
    print_in_order(curr->left);
    std::cout << curr->data << " ";
    print_in_order(curr->right);
}

// print post order
template <typename T> void BST<T>::print_post_order(Node* curr) const {
    if (!curr) {return;}
    print_post_order(curr->left);
    print_post_order(curr->right);
    std::cout << curr->data << " ";
}

// print each level
template <typename T>
void BST<T>::print_level(const std::vector<Node*>& level) const {
    for (const auto& p:level) {std::cout << p->data << " ";}
    std::cout << std::endl;
}

// make next level
template <typename T>
bool BST<T>::make_next_level(const std::vector<Node*>& level1,
                             std::vector<Node*>& level2) const {
    for (const auto& p:level1) {
        if (p->left) {level2.push_back(p->left);}
        if (p->right) {level2.push_back(p->right);}
    }
    return level2.empty() ? false:true;
}

// find the nod containing data in the tree starting at curr 
template <typename T>
typename BST<T>::Node* BST<T>::find(Node* curr, const T& data) const {
    if (!curr) {return nullptr;}
    if (data == curr->data) {
        return curr;
    } else if (data < curr->data) {
        return find(curr->left, data);
    } else {
        return find(curr->right, data);
    }
}

// height of the tree
template <typename T> int BST<T>::height(Node* curr) const {
    if (!curr) {return -1;}
    int l_height = height(curr->left);
    int r_height = height(curr->right);
    int curr_height = l_height > r_height ? l_height : r_height;
    return curr_height + 1;
}


