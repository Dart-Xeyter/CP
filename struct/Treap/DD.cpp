mt19937 randint(179);

struct Node {
    int x, y;
    Node *l, *r;
    int size;

    Node(int x1): x(x1), y(randint()), l(nullptr), r(nullptr), size(1) {}
};

void update(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    tree->size = 1;
    if (tree->l != nullptr) {
        tree->size += tree->l->size;
    }
    if (tree->r != nullptr) {
        tree->size += tree->r->size;
    }
}

Node* merge(Node* tree1, Node* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
    if (tree1->y < tree2->y) {
        tree1->r = merge(tree1->r, tree2);
        update(tree1);
        return tree1;
    }
    tree2->l = merge(tree1, tree2->l);
    update(tree2);
    return tree2;
}

pair<Node*, Node*> split(Node* tree, int x) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    if (tree->x <= x) {
        pair<Node*, Node*> trees = split(tree->r, x);
        tree->r = trees.first;
        update(tree);
        return {tree, trees.second};
    }
    pair<Node*, Node*> trees = split(tree->l, x);
    tree->l = trees.second;
    update(tree);
    return {trees.first, tree};
}

pair<Node*, Node*> split_num(Node* tree, int k) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    int t = (tree->l != nullptr ? tree->l->size : 0);
    if (t < k) {
        pair<Node*, Node*> trees = split_num(tree->r, k-t-1);
        tree->r = trees.first;
        update(tree);
        return {tree, trees.second};
    }
    pair<Node*, Node*> trees = split_num(tree->l, k);
    tree->l = trees.second;
    update(tree);
    return {trees.first, tree};
}

Node* add(Node* tree, int x) {
    pair<Node*, Node*> trees = split(tree, x);
    Node* now = new Node(x);
    return merge(merge(trees.first, now), trees.second);
}

Node* del(Node* tree, int x) {
    pair<Node*, Node*> trees = split(tree, x);
    int k = (trees.first != nullptr ? trees.first->size-1 : 0);
    pair<Node*, Node*> trees1 = split_num(trees.first, k);
    return merge(trees1.first, trees.second);
}

int num_x(Node* tree, int x) {
    int ans = 0;
    while (tree != nullptr) {
        if (tree->x <= x) {
            ans += (tree->l != nullptr ? tree->l->size : 0)+1;
            tree = tree->r;
        } else {
            tree = tree->l;
        }
    }
    return ans;
}

