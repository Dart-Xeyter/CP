struct Node {
    int x, type, size;
    bool rev;
    Node *left, *right, *parent;
    Node* link;

    Node(int x1): x(x1), type(-1), size(1), rev(false),
        left(nullptr), right(nullptr), parent(nullptr), link(nullptr) {}
};

void update(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    if (tree->parent == nullptr) {
        tree->type = -1;
    } else if (tree->parent->left == tree) {
        tree->type = 0;
    } else {
        tree->type = 1;
    }
    tree->size = 1;
    if (tree->left != nullptr) {
        tree->size += tree->left->size;
    }
    if (tree->right != nullptr) {
        tree->size += tree->right->size;
    }
}

void push(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    if (tree->rev) {
        if (tree->left != nullptr) {
            tree->left->rev ^= 1, tree->left->type = 1;
        }
        if (tree->right != nullptr) {
            tree->right->rev ^= 1, tree->right->type = 0;
        }
        swap(tree->left, tree->right);
        tree->rev = false;
    }
}

void zig(Node* tree) {
    if (tree == nullptr || tree->parent == nullptr) {
        return;
    }
    Node *me = tree, *up = tree->parent;
    if (tree->type == 0) {
        up->left = me->right, me->parent = up->parent;
        me->right = up, up->parent = me;
        if (up->left != nullptr) {
            up->left->parent = up;
        }
        update(up->left);
        if (up->type == 0) {
            me->parent->left = me;
        } else if (up->type == 1) {
            me->parent->right = me;
        }
    } else {
        up->right = me->left, me->parent = up->parent;
        me->left = up, up->parent = me;
        if (up->right != nullptr) {
            up->right->parent = up;
        }
        update(up->right);
        if (up->type == 0) {
            me->parent->left = me;
        } else if (up->type == 1) {
            me->parent->right = me;
        }
    }
    update(up), update(me), update(me->parent);
}

void zig_zig(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    zig(tree->parent);
    zig(tree);
}

void zig_zag(Node* tree) {
    zig(tree);
    zig(tree);
}

Node* splay(Node* tree) {
    if (tree == nullptr) {
        return tree;
    }
    vector<Node*> parents = {tree};
    while (parents.back() != nullptr) {
        parents.push_back(parents.back()->parent);
    }
    reverse(parents.begin(), parents.end());
    for (Node* q : parents) {
        push(q);
    }
    while (tree->parent != nullptr && tree->parent->parent != nullptr) {
        if (tree->type == tree->parent->type) {
            zig_zig(tree);
        } else {
            zig_zag(tree);
        }
    }
    zig(tree);
    return tree;
}

Node* min(Node* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    push(tree);
    while (tree != nullptr && tree->left != nullptr) {
        tree = tree->left;
        push(tree);
    }
    splay(tree);
    return tree;
}

Node* max(Node* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    push(tree);
    while (tree != nullptr && tree->right != nullptr) {
        tree = tree->right;
        push(tree);
    }
    splay(tree);
    return tree;
}

Node* find(Node* tree, int k) {
    if (k < 0 || tree == nullptr || k >= tree->size) {
        return nullptr;
    }
    push(tree);
    while (true) {
        int left = (tree->left != nullptr ? tree->left->size : 0);
        if (k == left) {
            break;
        }
        if (k < left) {
            tree = tree->left;
        } else {
            k -= left+1, tree = tree->right;
        }
        push(tree);
    }
    splay(tree);
    return tree;
}

Node* merge(Node* tree1, Node* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
    tree1 = max(tree1);
    tree1->right = tree2, tree2->parent = tree1;
    update(tree2), update(tree1);
    return tree1;
}

pair<Node*, Node*> split(Node* tree, int k) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    if (k <= 0) {
        return {nullptr, tree};
    }
    if (k >= tree->size) {
        return {tree, nullptr};
    }
    Node* root = find(tree, k);
    Node *tree1 = root->left, *tree2 = root;
    if (root->left != nullptr) {
        root->left->parent = nullptr;
    }
    root->left = nullptr;
    push(tree1), push(tree2);
    update(tree1), update(tree2);
    return {tree1, tree2};
}

Node* add(Node* tree, int x, int k) {
    Node* vertex = new Node(x);
    pair<Node*, Node*> trees = split(tree, k);
    return merge(merge(trees.first, vertex), trees.second);
}

Node* del(Node* tree, int k) {
    pair<Node*, Node*> trees = split(tree, k+1);
    pair<Node*, Node*> trees1 = split(trees.first, k);
    return merge(trees1.first, trees.second);
}

void Expose(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    splay(tree);
    Node* max_vertex = max(tree);
    while (max_vertex->link != nullptr) {
        Node* up = max_vertex->link;
        splay(up);
        int left = (up->left != nullptr ? up->left->size : 0);
        pair<Node*, Node*> trees = split(up, left);
        Node *vertex = max(trees.first), *vertex1 = min(trees.second);
        if (vertex != nullptr) {
            vertex->link = vertex1;
        }
        max_vertex->link = nullptr;
        Node* now = merge(max_vertex, vertex1);
        max_vertex = max(now);
    }
    int left = (tree->left != nullptr ? tree->left->size : 0);
    pair<Node*, Node*> trees = split(tree, left);
    Node *vertex = max(trees.first), *vertex1 = min(trees.second);
    if (vertex != nullptr) {
        vertex->link = vertex1;
    }
}

void make_root(Node* tree) {
    Expose(tree);
    splay(tree);
    tree->rev = true;
    push(tree);
}

void link(Node* tree1, Node* tree2) {
    make_root(tree1);
    tree1->link = tree2;
}

void cut(Node* tree1, Node* tree2) {
    make_root(tree1);
    Expose(tree2);
    splay(tree1);
    split(tree1, 1);
}

int len(Node* tree1, Node* tree2) {
    make_root(tree1);
    Expose(tree2);
    splay(tree1);
    Node* max1 = max(tree1);
    splay(tree2);
    Node* max2 = max(tree2);
    if (max1 != max2) {
        return -1;
    }
    splay(tree1);
    return tree1->size-1;
}

