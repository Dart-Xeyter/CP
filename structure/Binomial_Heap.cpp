struct Binomial_Heap;

struct Node {
    int x, rank, ind;
    vector<Node*> son;
    Node *parent;

    Node(int x1, int ind1 = -1) : x(x1), rank(0), ind(ind1), son({}), parent(nullptr) {}
};

vector<Node*> elem = {nullptr};

Node* merge(Node* tree1, Node* tree2) {
    if (tree1->x > tree2->x) {
        return merge(tree2, tree1);
    }
    tree1->son.push_back(tree2);
    tree2->parent = tree1;
    tree1->rank++;
    return tree1;
}

bool sieve(Node* tree) {
    if (tree->parent == nullptr) {
        return false;
    }
    Node* parent = tree->parent;
    if (tree->x > parent->x || (tree->x == parent->x && tree->ind > parent->ind)) {
        return false;
    }
    swap(tree->x, parent->x);
    swap(elem[tree->ind], elem[parent->ind]);
    swap(tree->ind, parent->ind);
    return true;
}

Node* sieve_up(Node* tree) {
    while (sieve(tree)) {
        tree = tree->parent;
    }
    return tree;
}

Node* get_root(Node* tree) {
    while (tree->parent != nullptr) {
        tree = tree->parent;
    }
    return tree;
}

struct Binomial_Heap {
    vector<Node*> heap;
    int log1;

    Binomial_Heap(int n) {
        log1 = 0;
        int q2 = 1;
        while (q2 < n) {
            q2 *= 2, log1++;
        }
        heap.assign(log1, nullptr);
    }

    void add_heap(Node* tree) {
        if (tree == nullptr) {
            return;
        }
        while (heap[tree->rank] != nullptr) {
            tree = merge(tree, heap[tree->rank]);
            heap[tree->rank-1] = nullptr;
        }
        heap[tree->rank] = tree;
    }

    void add(int x) {
        add_heap(new Node(x));
    }

    int get_min() {
        int min1 = INF;
        for (Node* q : heap) {
            if (q != nullptr) {
                min1 = min(min1, q->x);
            }
        }
        return min1;
    }

    void del_min(int ind) {
        vector<Node*> will;
        for (Node* q : heap[ind]->son) {
            will.push_back(q);
            q->parent = nullptr;
        }
        heap[ind] = nullptr;
        for (Node* q : will) {
            add_heap(q);
        }
    }

    void del_min() {
        pair<p, int> min1 = {{INF, INF}, -1};
        for (int q = 0; q < log1; q++) {
            if (heap[q] != nullptr) {
                min1 = min(min1, {{heap[q]->x, heap[q]->ind}, q});
            }
        }
        del_min(min1.second);
    }

    void del(Node* tree) {
        tree->x = -INF;
        tree = sieve_up(tree);
        for (int q = 0; q < log1; q++) {
            if (heap[q] == tree) {
                del_min(q);
            }
        }
    }
};

Binomial_Heap* merge(Binomial_Heap* &tree1, Binomial_Heap* &tree2) {
    for (Node* q : tree1->heap) {
        tree2->add_heap(q);
    }
    return tree2;
}
