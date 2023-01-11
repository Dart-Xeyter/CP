struct Node {
    int left, right;
    Node *l, *r;
    int size;

    Node(int left1, int right1):
        left(left1), right(right1), l(nullptr), r(nullptr), size(0) {}
};

void make_sons(Node* tree) {
    int m = ((tree->left+tree->right) >> 1);
    if (tree->l == nullptr) {
        tree->l = new Node(tree->left, m);
    }
    if (tree->r == nullptr) {
        tree->r = new Node(m, tree->right);
    }
}

void add(Node* tree, int x) {
    int l = tree->left, r = tree->right;
    tree->size++;
    if (r-l == 1) {
        return;
    }
    make_sons(tree);
    int m = ((l+r) >> 1);
    if (x < m) {
        add(tree->l, x);
    } else {
        add(tree->r, x);
    }
}

void del(Node* tree, int x) {
    int l = tree->left, r = tree->right;
    tree->size--;
    if (r-l == 1) {
        return;
    }
    make_sons(tree);
    int m = ((l+r) >> 1);
    if (x < m) {
        del(tree->l, x);
    } else {
        del(tree->r, x);
    }
}

int num_x(Node* tree, int x) {
    int l = tree->left, r = tree->right;
    if (r-l == 1) {
        return tree->size*(x == l);
    }
    make_sons(tree);
    int m = ((l+r) >> 1);
    if (x < m) {
        return num_x(tree->l, x);
    }
    return num_x(tree->r, x)+tree->l->size;
}

