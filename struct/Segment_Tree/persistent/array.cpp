const int C = 4200000;
int cnt = 0;

struct Node {
    int x;
    int l, r;

    Node(int x1 = 0) {
        x = x1;
        l = r = -1;
    }
};

Node nodes[C];

void update(int q) {
    Node &tree = nodes[q];
    tree.x = (tree.l != -1 ? nodes[tree.l].x : 0)+(tree.r != -1 ? nodes[tree.r].x : 0);
}

int build(int l, int r) {
    if (r-l == 1) {
        Node now = Node();
        int is = cnt++;
        if (cnt > C) {
            exit(179);
        }
        nodes[is] = now;
        return is;
    }
    Node now = Node();
    int is = cnt++;
    if (cnt > C) {
        exit(179);
    }
    int m = (l+r)/2;
    now.l = build(l, m), now.r = build(m, r);
    nodes[is] = now;
    update(is);
    return is;
}

int change(int pos, int l, int r, int q, int x) {
    if (r-l == 1) {
        Node now = Node(x);
        int is = cnt++;
        if (cnt > C) {
            exit(179);
        }
        nodes[is] = now;
        return is;
    }
    Node now = Node(), &tree = nodes[pos];
    int is = cnt++;
    if (cnt > C) {
        exit(179);
    }
    int m = (l+r)/2;
    if (q < m) {
        now.l = change(tree.l, l, m, q, x), now.r = tree.r;
    } else {
        now.l = tree.l, now.r = change(tree.r, m, r, q, x);
    }
    nodes[is] = now;
    update(is);
    return is;
}

int ans(int pos, int l, int r, int l1, int r1) {
    Node &tree = nodes[pos];
    if (l1 >= r || l >= r1) {
        return 0;
    }
    if (l1 <= l && r <= r1) {
        return tree.x;
    }
    int m = (l+r)/2;
    return ans(tree.l, l, m, l1, r1)+ans(tree.r, m, r, l1, r1);
}

