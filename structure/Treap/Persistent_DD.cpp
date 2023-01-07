mt19937 randint(179);

struct Node {
    int x, size;
    Node *l, *r;

    Node(int x1): x(x1), size(1), l(nullptr), r(nullptr) {}
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

Node* copy(Node* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    Node* now = new Node(tree->x);
    now->l = tree->l, now->r = tree->r;
    update(now);
    return now;
}

Node* merge(Node* tree1, Node* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
    if (randint() % (tree1->size+tree2->size) < tree1->size) {
        Node* now = copy(tree1);
        now->r = merge(tree1->r, tree2);
        update(now);
        return now;
    }
    Node* now = copy(tree2);
    now->l = merge(tree1, tree2->l);
    update(now);
    return now;
}

pair<Node*, Node*> split(Node* tree, int k) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    int left = (tree->l == nullptr ? 0 : tree->l->size);
    Node* now = copy(tree);
    if (k <= left) {
        pair<Node*, Node*> trees = split(tree->l, k);
        now->l = nullptr;
        update(now);
        trees.second = merge(trees.second, now);
        return trees;
    }
    pair<Node*, Node*> trees = split(tree->r, k-left-1);
    now->r = nullptr;
    update(now);
    trees.first = merge(now, trees.first);
    return trees;
}

pair<Node*, bool> change(Node* tree, int pos) {
    auto trees1 = split(tree, pos+1);
    auto trees2 = split(trees1.first, pos);
    Node* will = copy(trees2.second);
    bool flag = (will->x == 1);
    will->x = 1-will->x;
    return {merge(merge(trees2.first, will), trees1.second), flag};
}

