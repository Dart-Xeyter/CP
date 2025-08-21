struct Node {
    int sum = 0;
    int l = 0, r = 0;
};

vector<Node> nodes = {Node()};

int create_node(int ind = 0) {
    nodes.push_back(nodes[ind]);
    return (int)nodes.size()-1;
}

void update_DO(int ind) {
    Node& node = nodes[ind];
    node.sum = nodes[node.l].sum+nodes[node.r].sum;
}

int build_DO(int n) {
    int ind = create_node();
    if (n != 1) {
        nodes[ind].l = build_DO(n/2);
        nodes[ind].r = build_DO(n-n/2);
    }
    return ind;
}

int change_DO(int ind, int l, int r, int q, int x) {
    int new_ind = create_node(ind);
    if (r-l == 1) {
        nodes[new_ind].sum = x;
        return new_ind;
    }
    int m = (l+r) >> 1;
    if (q < m) {
        nodes[new_ind].l = change_DO(nodes[ind].l, l, m, q, x);
    } else {
        nodes[new_ind].r = change_DO(nodes[ind].r, m, r, q, x);
    }
    update_DO(new_ind);
    return new_ind;
}

int ans_DO(int ind, int l, int r, int L, int R) {
    if (l >= R || L >= r) {
        return 0;
    }
    if (L <= l && r <= R) {
        return nodes[ind].sum;
    }
    int m = (l+r) >> 1;
    int ans_l = ans_DO(nodes[ind].l, l, m, L, R);
    int ans_r = ans_DO(nodes[ind].r, m, r, L, R);
    return ans_l+ans_r;
}

struct DO {
    int n, root;

    DO(int n, int ind): n(n), root(ind) {}

    DO change(int q, int x) {
        int new_root = change_DO(root, 0, n, q, x);
        return {n, new_root};
    }

    int ans(int l, int r) {
        return ans_DO(root, 0, n, l, r);
    }
};

