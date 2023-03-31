avl_t *avl_remove(avl_t *root, int value) {
    if (root == NULL) {
        // The tree is empty, cannot remove any node
        return NULL;
    }
    
    // Search for the node with the desired value
    if (value < root->n) {
        root->left = avl_remove(root->left, value);
    } else if (value > root->n) {
        root->right = avl_remove(root->right, value);
    } else {
        // Node with the desired value is found
        avl_t *temp;
        if (root->left == NULL || root->right == NULL) {
            // Node has no child or only one child
            temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                // Node has no child
                temp = root;
                root = NULL;
            } else {
                // Node has only one child
                *root = *temp;
            }
            free(temp);
        } else {
            // Node has two children
            temp = root->right;
            while (temp->left) {
                temp = temp->left;
            }
            root->n = temp->n;
            root->right = avl_remove(root->right, temp->n);
        }
    }
    
    // If the tree is empty, return NULL
    if (root == NULL) {
        return NULL;
    }
    
    // Update the height of the current node
    root->height = max(height(root->left), height(root->right)) + 1;
    
    // Check if the tree is unbalanced
    int balance = get_balance(root);
    
    // If the tree is left-heavy, check if it needs a right rotation
    if (balance > 1 && get_balance(root->left) >= 0) {
        return rotate_right(root);
    }
    
    // If the tree is right-heavy, check if it needs a left rotation
    if (balance < -1 && get_balance(root->right) <= 0) {
        return rotate_left(root);
    }
    
    // If the tree is left-heavy and needs a left-right rotation
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    
    // If the tree is right-heavy and needs a right-left rotation
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    
    // If the tree is already balanced, return the root node
    return root;
}
