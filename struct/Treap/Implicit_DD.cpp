mt19937 randint(17957179);

struct Node {
    static Node* null;

    int x, y;
    Node *l, *r;
    Node* parent;
    int size;

    Node(int x): x(x), y(randint()), size(1) {
        if (null == nullptr) {
            null = this, size = 0;
        }
        l = r = parent = null;
    }
};

Node* Node::null = nullptr;
Node* null = new Node(0);

void update(Node* tree) {
    tree->l->parent = tree->r->parent = tree;
    tree->size = 1;
    tree->size += tree->l->size+tree->r->size;
}

Node* merge(Node* tree1, Node* tree2) {
    tree1->parent = tree2->parent = null;
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

pair<Node*, Node*> split(Node* tree, int k) {
    tree->parent = null;
    if (tree == null) {
        return {null, null};
    }
    if (tree->l->size < k) {
        auto [left, right] = split(tree->r, k-tree->l->size-1);
        tree->r = left;
        update(tree);
        return {tree, right};
    }
    auto [left, right] = split(tree->l, k);
    tree->l = right;
    update(tree);
    return {left, tree};
}

Node* add(Node* tree, int k, int x) {
    Node* node = new Node(x);
    auto [left, right] = split(tree, k);
    return merge(merge(left, node), right);
}

Node* del(Node* tree, int k) {
    auto [left, mid] = split(tree, k);
    auto [node, right] = split(mid, 1);
    return merge(left, right);
}

Node* find_elem(Node* tree, int ind) {
    while (tree != null && tree->l->size != ind) {
        if (tree->l->size < ind) {
            ind -= tree->l->size+1;
            tree = tree->r;
        } else {
            tree = tree->l;
        }
    }
    return tree;
}

int find_pos(Node* node) {
    if (node == null) {
        return -1;
    }
    int pos = node->l->size;
    while (node->parent != null) {
        Node* parent = node->parent;
        if (parent->r == node) {
            pos += parent->l->size+1;
        }
        node = parent;
    }
    return pos;
}

