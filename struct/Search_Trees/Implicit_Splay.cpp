#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

template <typename T>
struct Implicit_Splay {
    struct Node {
        T x;
        Node* l;
        Node* r;
        Node* p;
        int size;
        int sum, mod_set, mod_add;
        bool rev;
        Implicit_Splay<T>* spl;

        Node(T x): x(std::move(x)), l(nullptr), r(nullptr), p(nullptr), size(1),
                   sum(x), mod_set(-INF), mod_add(0), rev(false), spl(nullptr) {}

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
                swap(l, r);
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

        void update() {
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

        void splay_me() {
            splay(this);
            if (spl != nullptr) {
                spl->root = this;
            }
        }

        int get_position() {
            splay_me();
            return size_left();
        }

        Implicit_Splay<T>* get_tree() {
            splay_me();
            return spl;
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

    static void rotate_left(Node* tree) {
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
    }

    static void rotate_right(Node* tree) {
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
    }

    static void zig(Node* tree) {
        tree->spl = tree->p->spl;
        if (tree == tree->p->l) {
            rotate_right(tree->p);
        } else {
            rotate_left(tree->p);
        }
    }

    static void zig_zig(Node* tree) {
        zig(tree->p);
        zig(tree);
    }

    static void zig_zag(Node* tree) {
        zig(tree);
        zig(tree);
    }

    static void make_splay(Node* tree) {
        if (tree->p == nullptr) {
            return;
        }
        if (tree->p->p == nullptr) {
            zig(tree);
            return;
        }
        if ((tree == tree->p->l) == (tree->p == tree->p->p->l)) {
            zig_zig(tree);
        } else {
            zig_zag(tree);
        }
        make_splay(tree);
    }

    static void splay(Node* tree) {
        vector<Node*> parents = {tree};
        while (parents.back()->p != nullptr) {
            parents.push_back(parents.back()->p);
        }
        ::reverse(parents.begin(), parents.end());
        for (Node* parent : parents) {
            parent->push();
        }
        make_splay(tree);
    }

    struct iterator {
        Implicit_Splay<T>* spl;
        Node* me;

        iterator(Implicit_Splay* spl, Node* vertex): spl(spl), me(vertex) {}

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
            me = spl->get_vertex(index()+n).me;
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

        int index() const {
            return (me == nullptr ? spl->size() : me->get_position());
        }
    };

    Node* root;
    bool cycle = false;

    void update_root() {
        if (root != nullptr) {
            root->spl = this;
        }
    }

    Implicit_Splay(Node* root=nullptr): root(root) {
        update_root();
    }

    int size() {
        return (root == nullptr ? 0 : root->size);
    }

    iterator get_vertex(int k) {
        if (k == size()) {
            return end();
        }
        root->push();
        while (k != root->size_left()) {
            if (k < root->size_left()) {
                root = root->l;
            } else {
                k -= root->size_left()+1;
                root = root->r;
            }
            root->push();
        }
        splay(root);
        return iterator(this, root);
    }

    iterator begin() {
        return iterator(this, get_vertex(0).me);
    }

    iterator end() {
        return iterator(this, nullptr);
    }

    static Node* merge(Node* tree1, Node* tree2) {
        if (tree1 == nullptr) {
            return tree2;
        }
        Node* max_left = (--Implicit_Splay(tree1).end()).me;
        max_left->merge_right(tree2);
        max_left->update();
        return max_left;
    }

    static pair<Node*, Node*> split(Node* tree, int k) {
        Implicit_Splay now(tree);
        auto w = now.get_vertex(k);
        if (w == now.end()) {
            return {now.root, nullptr};
        }
        Node* left = w.me->l;
        w.me->split_left();
        w.me->update();
        return {left, w.me};
    }

    void insert(int k, const T& x) {
        auto trees_right = split(root, k);
        root = merge(merge(trees_right.first, new Node(x)), trees_right.second);
        update_root();
    }

    void erase(int k) {
        auto trees_right = split(root, k+1);
        auto trees_left = split(trees_right.first, k);
        root = merge(trees_left.first, trees_right.second);
        update_root();
    }

    static Implicit_Splay* merge(Implicit_Splay* tree1, Implicit_Splay* tree2) {
        auto tree = merge(tree1->root, tree2->root);
        return new Implicit_Splay(tree);
    }

    static pair<Implicit_Splay*, Implicit_Splay*> split(Implicit_Splay* tree, int k) {
        pair<Node*, Node*> trees = split(tree->root, k);
        return {new Implicit_Splay(trees.first), new Implicit_Splay(trees.second)};
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
        Implicit_Splay* tree = trees_left.second;
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
