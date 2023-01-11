struct Node {
    int x, type;
    Node *left, *right, *parent;

    Node(int x1) : x(x1), left(nullptr), right(nullptr), parent(nullptr), type(-1) {}
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

struct Splay;

Splay merge(Splay tree1, Splay tree2);
pair<Splay, Splay> split(Splay tree, int x);

struct Splay {
    Node* root;

    Splay(Node* root1 = nullptr) : root(root1) {}

    void splay(Node* tree) {
        if (tree == nullptr) {
            root = tree;
            return;
        }
        while (tree->parent != nullptr && tree->parent->parent != nullptr) {
            if (tree->type == tree->parent->type) {
                zig_zig(tree);
            } else {
                zig_zag(tree);
            }
        }
        zig(tree);
        root = tree;
    }

    Node* min(Node* tree) {
        if (tree == nullptr) {
            return nullptr;
        }
        while (tree != nullptr && tree->left != nullptr) {
            tree = tree->left;
        }
        splay(tree);
        return tree;
    }

    Node* max(Node* tree) {
        if (tree == nullptr) {
            return nullptr;
        }
        while (tree != nullptr && tree->right != nullptr) {
            tree = tree->right;
        }
        splay(tree);
        return tree;
    }

    Node* lower_bound(int x) {
        Node *tree = root, *last = nullptr, *min_was = nullptr;
        while (tree != nullptr) {
            if (tree->x == x) {
                splay(tree);
                return tree;
            }
            if (x < tree->x) {
                last = min_was = tree, tree = tree->left;
            } else {
                last = tree, tree = tree->right;
            }
        }
        splay(last);
        if (min_was != nullptr) {
            splay(min_was);
        }
        return min_was;
    }

    bool find(int x) {
        Node* tree = lower_bound(x);
        return (tree != nullptr && tree->x == x);
    }

    void add(int x) {
        pair<Splay, Splay> trees = split(*this, x);
        pair<Splay, Splay> trees1 = split(trees.first, x-1);
        trees1.second = Splay(new Node(x));
        *this = merge(merge(trees1.first, trees1.second), trees.second);
    }

    void del(int x) {
        pair<Splay, Splay> trees = split(*this, x);
        pair<Splay, Splay> trees1 = split(trees.first, x-1);
        *this = merge(trees1.first, trees.second);
    }

    Node* next(Node* tree) {
        if (tree == nullptr || tree->right == nullptr) {
            return nullptr;
        }
        splay(tree);
        return min(tree->right);
    }

    Node* last(Node* tree) {
        if (tree == nullptr || tree->left == nullptr) {
            return nullptr;
        }
        splay(tree);
        return max(tree->left);
    }
};

Splay merge(Splay tree1, Splay tree2) {
    if (tree1.root == nullptr) {
        return tree2;
    }
    if (tree2.root == nullptr) {
        return tree1;
    }
    tree1 = tree1.max(tree1.root);
    tree1.root->right = tree2.root, tree2.root->parent = tree1.root;
    update(tree2.root), update(tree1.root);
    return tree1;
}

pair<Splay, Splay> split(Splay tree, int x) {
    if (tree.root == nullptr) {
        return {Splay(), Splay()};
    }
    tree.lower_bound(x);
    Node* root = tree.root;
    if (root == nullptr) {
        return {Splay(), Splay()};
    }
    Splay tree1, tree2;
    if (root->x <= x) {
        tree1 = Splay(root), tree2 = Splay(root->right);
        if (root->right != nullptr) {
            root->right->parent = nullptr;
        }
        root->right = nullptr;
    } else {
        tree1 = Splay(root->left), tree2 = Splay(root);
        if (root->left != nullptr) {
            root->left->parent = nullptr;
        }
        root->left = nullptr;
    }
    update(tree1.root), update(tree2.root);
    return {tree1, tree2};
}

