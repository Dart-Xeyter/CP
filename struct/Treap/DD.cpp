mt19937 randint(17957179);

struct Node {
    static Node* null;

    int x, y, size, sum;
    Node *l, *r;

    Node(int x): x(x), y(randint()), size(1), sum(x) {
        if (null == nullptr) {
            size = 0, null = this;
        }
        l = r = null;
    }
};

Node* Node::null = new Node(0);
Node* null = Node::null;

void update(Node* tree) {
    tree->size = 1, tree->sum = tree->x;
    tree->size += tree->l->size, tree->sum += tree->l->sum;
    tree->size += tree->r->size, tree->sum += tree->r->sum;
}

Node* merge(Node* tree1, Node* tree2) {
    if (tree1 == null || tree2 == null) {
        return tree1 == null ? tree2 : tree1;
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
    if (tree == null) {
        return {null, null};
    }
    if (tree->x <= x) {
        auto [left, right] = split(tree->r, x);
        tree->r = left;
        update(tree);
        return {tree, right};
    }
    auto [left, right] = split(tree->l, x);
    tree->l = right;
    update(tree);
    return {left, tree};
}

Node* add(Node* tree, int x) {
    Node* node = new Node(x);
    auto [left, right] = split(tree, x);
    return merge(merge(left, node), right);
}

Node* del(Node* tree, int x) {
    auto [less_equal, more] = split(tree, x);
    auto [less, equal] = split(less_equal, x-1);
    Node *eq_l = equal->l, *eq_r = equal->r;
    return merge(merge(less, eq_l), merge(eq_r, more));
}

