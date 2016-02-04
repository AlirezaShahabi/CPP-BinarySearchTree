

// CHECK IF A TREE IS A BINARY SEARCH TREE




// Non-efficient method O(N^2) - - - - - - - - - - - - - - - -

// check if a tree is a binary search tree it. recieves the
// root of the tree
bool is_bst(Node* root) {
    if (!root) {return true;}
    if (left_is_less(root->left, root->data) &&
        right_is_greater(root->right, root->data) &&
        is_bst(root->left) && is_bst(root->right)) {
        return true;
    } else {
        return false;
    }
}

// check if all the elements in the left sub_tree are less
// than the value of the root
bool left_is_less(Node* left_child, int root_data) {
    if (!left_child) {return true;}
    if (left_child->data < root_data &&
        left_is_less(left_child->left, root_data) &&
        left_is_less(left_child->right, root_data)) {
        return true;
    } else {
        return false;
    }
}

// check if all the elements in the right sub_tree are
// greater than the value of the root
bool right_is_greater(Node* right_child, int root_data) {
    if (!right_child) {return true;}
    if (right_child->data < root_data &&
        right_is_greater(right_child->left, root_data) &&
        right_is_greater(right_child->right, root_data)) {
        return true;
    } else {
        return false;
    }
}




// more efficient method O(N) - - - - - - - - - - - - - - - -  

// create a range for every node

bool is_bst2(Node* root) {
    if (!root) {return true;}
    is_bst_helper(root, INT_MIN, INT_MAX);
    
}

bool is_bst_helper(Node* root, int min_val, int max_val) {
    if (!root) {return true;}
    if (root->data > min_val && root->data < max_val &&
        is_bst2(root->left, min_val, root->data) &&
        is_bst2(root->data, root->data, max_val)) {
        return true;
    } else {
        return false;
    }
}







