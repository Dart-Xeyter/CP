#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

template <typename T>
struct Implicit_Treap {
    struct Node {
        static mt19937 randint;

        T x;
        Node* l;
        Node* r;
        Node* p;
        unsigned y;
        int size;
        int sum, mod_set, mod_add;
        bool rev;
        Implicit_Treap<T>* treap;

        Node(T x): x(std::move(x)), l(nullptr), r(nullptr), p(nullptr), y(randint()), size(1),
                   sum(x), mod_set(-INF), mod_add(0), rev(false), treap(nullptr) {}

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
            update();
        }

        void split_right() {
            if (r == nullptr) {
                return;
            }
            r->p = nullptr, r = nullptr;
            update();
        }

        void merge_left(Node* tree) {
            if (tree == nullptr) {
                return;
            }
            tree->p = this, l = tree;
            update();
        }

        void merge_right(Node* tree) {
            if (tree == nullptr) {
                return;
            }
            tree->p = this, r = tree;
            update();
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

        Implicit_Treap<T>* get_tree() {
            Node* tree = this;
            while (tree->p != nullptr) {
                tree = tree->p;
            }
            return tree->treap;
        }
    };

    static Node* merge(Node* tree1, Node* tree2) {
        if (tree1 == nullptr || tree2 == nullptr) {
            return (tree1 == nullptr ? tree2 : tree1);
        }
        tree1->push(), tree2->push();
        if (tree1->y < tree2->y) {
            Node* right_son = tree1->r;
            tree1->split_right();
            Node* merged = merge(right_son, tree2);
            tree1->merge_right(merged);
            return tree1;
        } else {
            Node* left_son = tree2->l;
            tree2->split_left();
            Node* merged = merge(tree1, left_son);
            tree2->merge_left(merged);
            return tree2;
        }
    }

    static pair<Node*, Node*> split(Node* tree, int k) {
        if (tree == nullptr) {
            return {nullptr, nullptr};
        }
        tree->push();
        if (tree->size_left() < k) {
            k -= tree->size_left()+1;
            Node* right_son = tree->r;
            tree->split_right();
            auto trees = split(right_son, k);
            tree->merge_right(trees.first);
            return {tree, trees.second};
        } else {
            Node* left_son = tree->l;
            tree->split_left();
            auto trees = split(left_son, k);
            tree->merge_left(trees.second);
            return {trees.first, tree};
        }
    }

    struct iterator {
        Implicit_Treap<T>* treap;
        Node* me;

        iterator(Implicit_Treap* treap, Node* vertex): treap(treap), me(vertex) {}

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
            me = treap->get_vertex(index()+n).me;
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
            return (me == nullptr ? treap->size() : me->get_position());
        }
    };

    Node* root;

    void update_root() {
        if (root != nullptr) {
            root->treap = this;
        }
    }

    Implicit_Treap(Node* root = nullptr): root(root) {
        update_root();
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

    static Implicit_Treap* merge(Implicit_Treap* tree1, Implicit_Treap* tree2) {
        auto tree = merge(tree1->root, tree2->root);
        return new Implicit_Treap(tree);
    }

    static pair<Implicit_Treap*, Implicit_Treap*> split(Implicit_Treap* tree, int k) {
        pair<Node*, Node*> trees = split(tree->root, k);
        return {new Implicit_Treap(trees.first), new Implicit_Treap(trees.second)};
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
        Implicit_Treap* tree = trees_left.second;
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

template <typename T>
//mt19937 Implicit_Treap<T>::Node::randint(179);
mt19937 Implicit_Treap<T>::Node::randint(chrono::steady_clock::now().time_since_epoch().count());
