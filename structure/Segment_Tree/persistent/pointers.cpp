struct Node {
    int x;
    Node *l, *r;

    Node(int x1 = 0): x(x1), l(nullptr), r(nullptr) {}
};

void update(Node* tree) {
    tree->x = (tree->l != nullptr ? tree->l->x : 0)+(tree->r != nullptr ? tree->r->x : 0);
}

Node* build(int l, int r) {
    Node* now = new Node();
    if (r-l == 1) {
        return now;
    }
    int m = (l+r)/2;
    now->l = build(l, m), now->r = build(m, r);
    update(now);
    return now;
}

Node* change(Node* tree, int l, int r, int q, int x) {
    if (r-l == 1) {
        return new Node(x);
    }
    Node* now = new Node();
    int m = (l+r)/2;
    if (q < m) {
        now->l = change(tree->l, l, m, q, x), now->r = tree->r;
    } else {
        now->l = tree->l, now->r = change(tree->r, m, r, q, x);
    }
    update(now);
    return now;
}

int ans(Node* tree, int l, int r, int l1, int r1) {
    if (l1 >= r || l >= r1) {
        return 0;
    }
    if (l1 <= l && r <= r1) {
        return tree->x;
    }
    int m = (l+r)/2;
    return ans(tree->l, l, m, l1, r1)+ans(tree->r, m, r, l1, r1);
}

