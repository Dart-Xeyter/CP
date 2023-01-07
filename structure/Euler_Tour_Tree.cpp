mt19937 randint(179);

struct Node {
    int u, v, plus, y, size, sum, pref;
    Node *l, *r, *parent;

    Node(int u1, int v1, int plus1) : u(u1), v(v1), plus(plus1), y(randint()), size(1), sum(plus),
    pref(min(0LL, plus)), l(nullptr), r(nullptr), parent(nullptr) {}
};

void make_parent(Node* tree, Node* parent) {
    if (tree != nullptr) {
        tree->parent = parent;
    }
}

void update(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    tree->size = 1, tree->sum = tree->plus;
    tree->pref = (tree->l != nullptr ? min(tree->l->pref, tree->l->sum+tree->plus) : min(0LL, tree->plus));
    if (tree->l != nullptr) {
        tree->size += tree->l->size, tree->sum += tree->l->sum;
    }
    if (tree->r != nullptr) {
        tree->size += tree->r->size, tree->sum += tree->r->sum;
        tree->pref = min(tree->pref, (tree->l != nullptr ? tree->l->sum : 0)+tree->plus+tree->r->pref);
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
        make_parent(tree1->r, tree1);
        update(tree1);
        return tree1;
    }
    tree2->l = merge(tree1, tree2->l);
    make_parent(tree2->l, tree2);
    update(tree2);
    return tree2;
}

pair<Node*, Node*> split(Node* tree, int k) {
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    int len = (tree->l != nullptr ? tree->l->size : 0);
    if (len < k) {
        pair<Node*, Node*> trees = split(tree->r, k-len-1);
        tree->r = trees.first;
        make_parent(trees.first, tree);
        make_parent(trees.second, nullptr);
        update(tree);
        return {tree, trees.second};
    }
    pair<Node*, Node*> trees = split(tree->l, k);
    tree->l = trees.second;
    make_parent(trees.first, nullptr);
    make_parent(trees.second, tree);
    update(tree);
    return {trees.first, tree};
}

vector<pair<Node*, Node*>> for_vertex;

bool is_left(Node* tree) {
    if (tree == nullptr || tree->parent == nullptr) {
        return false;
    }
    return tree->parent->l == tree;
}

int find_pos(Node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    int cnt = (tree->l != nullptr ? tree->l->size : 0);
    while (tree->parent != nullptr) {
        bool flag = is_left(tree);
        tree = tree->parent;
        if (!flag) {
            cnt += (tree->l != nullptr ? tree->l->size : 0)+1;
        }
    }
    return cnt;
}

Node* link_left(int x, int y, Node* tree, Node* tree1) {
    Node* now = for_vertex[x].first;
    int k = find_pos(now);
    pair<Node*, Node*> trees = split(tree, k+1);
    Node *down = new Node(x, y, 1), *up = new Node(y, x, -1);
    for_vertex[y] = {down, up};
    return merge(merge(trees.first, merge(merge(down, tree1), up)), trees.second);
}

Node* link_right(int x, int y, Node* tree, Node* tree1) {
    Node* now = for_vertex[x].second;
    int k = find_pos(now);
    pair<Node*, Node*> trees = split(tree, k);
    Node *down = new Node(x, y, 1), *up = new Node(y, x, -1);
    for_vertex[y] = {down, up};
    return merge(merge(trees.first, merge(merge(down, tree1), up)), trees.second);
}

pair<Node*, Node*> cut(int x, Node* tree) {
    Node *now1 = for_vertex[x].first, *now2 = for_vertex[x].second;
    int k1 = find_pos(now1), k2 = find_pos(now2);
    pair<Node*, Node*> trees = split(tree, k2+1);
    pair<Node*, Node*> trees1 = split(trees.first, k1);
    for_vertex[x] = {nullptr, nullptr};
    return {merge(trees1.first, trees.second), trees1.second};
}
