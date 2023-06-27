#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

template <typename T>
struct Implicit_AVL {
    struct Node {
        T x;
        int h;
        Node* l;
        Node* r;
        Node* p;
        int size;
        int sum, mod_set, mod_add;
        bool rev;
        Implicit_AVL<T>* avl;

        Node(T x): x(std::move(x)), h(1), l(nullptr), r(nullptr), p(nullptr), size(1),
                   sum(x), mod_set(-INF), mod_add(0), rev(false), avl(nullptr) {}

        static void push_set(Node* tree, int x) {
            if (tree == nullptr || x == -INF) {
                return;
            }
            tree->x = tree->mod_set = x;
            tree->sum = tree->size*x, tree->mod_add = 0;
        }

        static void push_add(Node* tree, int x) {
            if (tree == nullptr) {
                return;
            }
            tree->x += x, tree->sum += tree->size*x, tree->mod_add += x;
        }

        static void push_rev(Node* tree) {
            if (tree == nullptr) {
                return;
            }
            tree->rev ^= 1;
        }

        void push() {
            if (rev) {
                ::swap(l, r);
                push_rev(l), push_rev(r);
            }
            push_set(l, mod_set), push_set(r, mod_set);
            push_add(l, mod_add), push_add(r, mod_add);
            rev = false, mod_set = -INF, mod_add = 0;
        }

        int size_left() {
            return (l == nullptr ? 0 : l->size);
        }

        int size_right() {
            return (r == nullptr ? 0 : r->size);
        }

        int height_left() {
            return (l == nullptr ? 0 : l->h);
        }

        int height_right() {
            return (r == nullptr ? 0 : r->h);
        }

        void update() {
            h = max(height_left(), height_right())+1;
            size = 1+size_left()+size_right();
            sum = x+(l == nullptr ? 0 : l->sum)+(r == nullptr ? 0 : r->sum);
        }

        void split_left() {
            if (l == nullptr) {
                return;
            }
            l->p = nullptr, l = nullptr;
        }

        void split_right() {
            if (r == nullptr) {
                return;
            }
            r->p = nullptr, r = nullptr;
        }

        void merge_left(Node* tree) {
            if (tree == nullptr) {
                return;
            }
            tree->p = this, l = tree;
        }

        void merge_right(Node* tree) {
            if (tree == nullptr) {
                return;
            }
            tree->p = this, r = tree;
        }

        int get_position() {
            Node* tree = this;
            int pos = (tree->rev ? tree->size_right() : tree->size_left());
            while (tree->p != nullptr) {
                if (tree->p->rev) {
                    pos = tree->size-pos-1;
                }
                if (tree->p->rev ^ (tree == tree->p->r)) {
                    pos += tree->p->size-tree->size;
                }
                tree = tree->p;
            }
            return pos;
        }

        Implicit_AVL<T>* get_tree() {
            Node* tree = this;
            while (tree->p != nullptr) {
                tree = tree->p;
            }
            return tree->avl;
        }
    };

    static void change_son(Node* tree, Node* was, Node* will) {
        if (tree == nullptr) {
            return;
        }
        if (tree->l == was) {
            tree->split_left();
            tree->merge_left(will);
        } else {
            tree->split_right();
            tree->merge_right(will);
        }
    }

    static void swap(Node* tree1, Node* tree2) {
        Node* p1 = tree1->p;
        Node* p2 = tree2->p;
        Node* fictional = new Node(tree1->x);
        change_son(p1, tree1, fictional);
        change_son(p2, tree2, tree1);
        change_son(p1, fictional, tree2);
        Node* l1 = tree1->l;
        Node* l2 = tree2->l;
        tree1->split_left();
        tree2->split_left();
        tree1->merge_left(l2);
        tree2->merge_left(l1);
        Node* r1 = tree1->r;
        Node* r2 = tree2->r;
        tree1->split_right();
        tree2->split_right();
        tree1->merge_right(r2);
        tree2->merge_right(r1);
    }

    static Node* rotate_left(Node* tree) {
        Node* x = tree;
        Node* y = tree->r;
        Node* beta = y->l;
        y->split_left();
        x->split_right();
        change_son(x->p, x, y);
        y->merge_left(x);
        x->merge_right(beta);
        x->update();
        y->update();
        return y;
    }

    static Node* rotate_right(Node* tree) {
        Node* x = tree->l;
        Node* y = tree;
        Node* beta = x->r;
        x->split_right();
        y->split_left();
        change_son(y->p, y, x);
        x->merge_right(y);
        y->merge_left(beta);
        y->update();
        x->update();
        return x;
    }

    static Node* big_left(Node* tree) {
        rotate_right(tree->r);
        return rotate_left(tree);
    }

    static Node* big_right(Node* tree) {
        rotate_left(tree->l);
        return rotate_right(tree);
    }

    static Node* repair(Node* tree) {
        if (tree->l != nullptr) {
            tree->l->push();
        }
        if (tree->r != nullptr) {
            tree->r->push();
        }
        int d = tree->height_left()-tree->height_right();
        if (d == 2 && tree->l->height_left() >= tree->l->height_right()) {
            tree = rotate_right(tree);
        } else if (d == 2) {
            tree->l->r->push();
            tree = big_right(tree);
        } else if (d == -2 && tree->r->height_right() >= tree->r->height_left()) {
            tree = rotate_left(tree);
        } else if (d == -2) {
            tree->r->l->push();
            tree = big_left(tree);
        } else {
            tree->update();
        }
        return (tree->p == nullptr ? tree : repair(tree->p));
    }

    struct iterator {
        Implicit_AVL<T>* avl;
        Node* me;

        iterator(Implicit_AVL* avl, Node* vertex): avl(avl), me(vertex) {}

        bool operator==(const iterator& another) const {
            return me == another.me;
        }

        auto operator<=>(const iterator& another) const {
            return (*this-another) <=> 0;
        }

        T& operator*() const {
            return me->x;
        }

        T* operator->() const {
            return &**this;
        }

        iterator& operator++() {
            return *this += 1;
        }

        iterator operator++(signed) {
            iterator copy(*this);
            ++*this;
            return copy;
        }

        iterator& operator--() {
            return *this -= 1;
        }

        iterator operator--(signed) {
            iterator copy(*this);
            --*this;
            return copy;
        }

        iterator& operator+=(int n) {
            me = avl->get_vertex(index()+n).me;
            return *this;
        }

        iterator operator+(int n) const {
            iterator copy(*this);
            copy += n;
            return copy;
        }

        iterator& operator-=(int n) {
            *this += -n;
            return *this;
        }

        iterator operator-(int n) const {
            iterator copy(*this);
            copy -= n;
            return copy;
        }

        int operator-(const iterator& another) const {
            return index()-another.index();
        }

        int index() {
            return (me == nullptr ? avl->size() : me->get_position());
        }
    };

    Node* root;
    bool cycle = false;

    Implicit_AVL(Node* root = nullptr): root(root) {
        if (root != nullptr) {
            root->avl = this;
        }
    }

    int size() {
        return (root == nullptr ? 0 : root->size);
    }

    iterator get_vertex(int k) {
        assert(0 <= k && k <= size());
        if (k == size()) {
            return end();
        }
        Node* tree = root;
        tree->push();
        while (k != tree->size_left()) {
            if (tree->size_left() < k) {
                k -= tree->size_left()+1;
                tree = tree->r;
            } else {
                tree = tree->l;
            }
            tree->push();
        }
        return iterator(this, tree);
    }

    iterator begin() {
        return iterator(this, get_vertex(0).me);
    }

    iterator end() {
        return iterator(this, nullptr);
    }

    void insert_node(int k, Node* node) {
        if (root == nullptr) {
            root = node;
            root->avl = this;
            return;
        }
        auto w = begin()+k;
        Node* vertex;
        if (w != end() && w.me->l == nullptr) {
            vertex = node;
            w.me->merge_left(vertex);
        } else {
            vertex = node;
            (--w).me->merge_right(vertex);
        }
        root = repair(vertex);
        root->avl = this;
    }

    void insert(int k, const T& x) {
        insert_node(k, new Node(x));
    }

    void erase(int k) {
        auto w = begin()+k;
        Node* vertex;
        if (w.me->p == nullptr && (w.me->l == nullptr || w.me->r == nullptr)) {
            root = (w.me->l == nullptr ? w.me->r : w.me->l);
            if (root != nullptr) {
                root->avl = this;
            }
            w.me->split_left(), w.me->split_right();
            w.me->update();
            return;
        } else if (w.me->l == nullptr) {
            vertex = w.me->p;
            Node* replace = w.me->r;
            w.me->split_right();
            w.me->update();
            change_son(w.me->p, w.me, replace);
        } else {
            auto w_left = (--w)++;
            swap(w_left.me, w.me);
            vertex = w.me->p;
            Node* replace = w.me->l;
            w.me->split_left();
            w.me->update();
            change_son(w.me->p, w.me, replace);
        }
        root = repair(vertex);
        root->avl = this;
    }

    static Node* merge(Node* tree1, Node* vertex, Node* tree2) {
        int h1 = (tree1 == nullptr ? 0 : tree1->h);
        int h2 = (tree2 == nullptr ? 0 : tree2->h);
        if (h1 == h2) {
            vertex->merge_left(tree1);
            vertex->merge_right(tree2);
        } else if (h1 > h2) {
            tree1->push();
            while (tree1->height_right() > h2) {
                tree1 = tree1->r;
                tree1->push();
            }
            Node* right = tree1->r;
            tree1->split_right();
            vertex->merge_left(right);
            vertex->merge_right(tree2);
            tree1->merge_right(vertex);
        } else {
            tree2->push();
            while (tree2->height_left() > h1) {
                tree2 = tree2->l;
                tree2->push();
            }
            Node* left = tree2->l;
            tree2->split_left();
            vertex->merge_left(tree1);
            vertex->merge_right(left);
            tree2->merge_left(vertex);
        }
        return repair(vertex);
    }

    static Implicit_AVL* merge(Implicit_AVL* tree1, Implicit_AVL* tree2) {
        if (tree1->size() == 0) {
            return tree2;
        }
        Node* vertex = (--tree1->end()).me;
        tree1->erase(tree1->size()-1);
        return new Implicit_AVL(merge(tree1->root, vertex, tree2->root));
    }

    static void add_tree(Node* add, vector<Node*> &trees, vector<Node*> &vertexes, bool left, bool collapse) {
        trees.push_back(add);
        int m = (int)trees.size();
        while (m >= 2 && (collapse || (trees[m-1] == nullptr ? 0 : trees[m-1]->h) == (trees[m-2] == nullptr ? 0 : trees[m-2]->h))) {
            Node* merged = merge(trees[left ? m-2 : m-1], vertexes.back(), trees[left ? m-1 : m-2]);
            trees.pop_back(), trees.pop_back();
            trees.push_back(merged);
            vertexes.pop_back(), m--;
        }
    }

    static pair<Node*, pair<Node*, Node*>> split(Node* tree, int k) {
        vector<Node*> left_trees, left_vertexes, right_trees, right_vertexes;
        tree->push();
        while (true) {
            int left_size = tree->size_left();
            Node* left = tree->l;
            Node* right = tree->r;
            tree->split_left();
            tree->split_right();
            tree->update();
            if (k <= left_size) {
                add_tree(right, right_trees, right_vertexes, false, false);
                right_vertexes.push_back(tree);
                tree = left;
            } else if (k > left_size+1) {
                k -= left_size+1;
                add_tree(left, left_trees, left_vertexes, true, false);
                left_vertexes.push_back(tree);
                tree = right;
            } else {
                add_tree(left, left_trees, left_vertexes, true, true);
                add_tree(right, right_trees, right_vertexes, false, true);
                break;
            }
            tree->push();
        }
        return {tree, {left_trees[0], right_trees[0]}};
    }

    static pair<Implicit_AVL*, Implicit_AVL*> split(Implicit_AVL* tree, int k) {
        if (k == 0) {
            return {new Implicit_AVL(), tree};
        }
        auto [vertex, trees] = split(tree->root, k);
        auto* tree1 = new Implicit_AVL(trees.first);
        auto* tree2 = new Implicit_AVL(trees.second);
        tree1->insert_node(tree1->size(), vertex);
        return {tree1, tree2};
    }

    int get_sum() {
        return (root == nullptr ? 0 : root->sum);
    }

    void set_value(int x) {
        Node::push_set(root, x);
    }

    void add_value(int x) {
        Node::push_add(root, x);
    }

    void reverse() {
        Node::push_rev(root);
    }

    template <int N>
    void function_on_segment(int l, int r, int &x) {
        auto trees_right = split(this, r);
        auto trees_left = split(trees_right.first, l);
        Implicit_AVL* tree = trees_left.second;
        if constexpr (N == 0) {
            tree->set_value(x);
        } else if constexpr (N == 1) {
            tree->add_value(x);
        } else {
            x = tree->get_sum();
        }
        *this = *merge(merge(trees_left.first, tree), trees_right.second);
    }

    void print() {
        for (auto &q : *this) {
            cout << q << ' ';
        }
        cout << endl;
    }
};
