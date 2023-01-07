mt19937 randint(179);

struct Node {
    int x, y;
    Node *l, *r, *parent;
    int size, sum;

    Node(int x1): x(x1), y(randint()), l(nullptr), r(nullptr), parent(nullptr), size(1), sum(x) {}
};

void update(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    tree->size = 1, tree->sum = tree->x;
    if (tree->l != nullptr) {
        tree->size += tree->l->size, tree->sum += tree->l->sum;
    }
    if (tree->r != nullptr) {
        tree->size += tree->r->size, tree->sum += tree->r->sum;
    }
}

void change_parent(Node* tree, Node* parent) {
    if (tree == nullptr) {
        return;
    }
    tree->parent = parent;
}

void change_left(Node* tree, Node* left) {
    if (tree == nullptr) {
        return;
    }
    tree->l = left;
    change_parent(left, tree);
    update(tree);
}

void change_right(Node* tree, Node* right) {
    if (tree == nullptr) {
        return;
    }
    tree->r = right;
    change_parent(right, tree);
    update(tree);
}

Node* merge(Node* tree1, Node* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
    if (tree1->y < tree2->y) {
        change_parent(tree1->r, nullptr);
        change_right(tree1, merge(tree1->r, tree2));
        return tree1;
    }
    change_parent(tree2->l, nullptr);
    change_left(tree2, merge(tree1, tree2->l));
    return tree2;
}

pair<Node*, Node*> split(Node* tree, int k) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    int t = (tree->l != nullptr ? tree->l->size : 0);
    if (k <= t) {
        change_parent(tree->l, nullptr);
        pair<Node*, Node*> trees = split(tree->l, k);
        change_left(tree, trees.second);
        return {trees.first, tree};
    }
    change_parent(tree->r, nullptr);
    pair<Node*, Node*> trees = split(tree->r, k-t-1);
    change_right(tree, trees.first);
    return {tree, trees.second};
}

Node* add(Node* tree, int k, Node* vertex) {
    pair<Node*, Node*> trees = split(tree, k);
    return merge(merge(trees.first, vertex), trees.second);
}

Node* del(Node* tree, int k) {
    pair<Node*, Node*> trees1 = split(tree, k);
    pair<Node*, Node*> trees2 = split(trees1.second, 1);
    return merge(trees1.first, trees2.second);
}

Node* root(Node* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    while (tree->parent != nullptr) {
        tree = tree->parent;
    }
    return tree;
}

int find_pos(Node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    int ans = (tree->l != nullptr ? tree->l->size : 0);
    while (tree->parent != nullptr) {
        if (tree->parent->l != tree) {
            ans += (tree->parent->l != nullptr ? tree->parent->l->size : 0)+1;
        }
        tree = tree->parent;
    }
    return ans;
}

Node* find_element(Node* tree, int k) {
    if (tree == nullptr) {
        return nullptr;
    }
    int t = (tree->l != nullptr ? tree->l->size : 0);
    if (k == t) {
        return tree;
    }
    if (k < t) {
        return find_element(tree->l, k);
    }
    return find_element(tree->r, k-t-1);
}

