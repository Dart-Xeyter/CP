#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

template <typename T>
struct Splay {
    struct Node {
        T x;
        int num, value;
        Node* l;
        Node* r;
        Node* p;
        int size, sum;
        Splay<T>* spl;

        Node(T x, int num=1): x(std::move(x)), num(num), value(x), l(nullptr), r(nullptr), p(nullptr), size(num), sum(value*num), spl(nullptr) {}

        int size_left() {
            return (l == nullptr ? 0 : l->size);
        }

        int size_right() {
            return (r == nullptr ? 0 : r->size);
        }

        void update() {
            size = num+size_left()+size_right();
            sum = value*num+(l == nullptr ? 0 : l->sum)+(r == nullptr ? 0 : r->sum);
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
            splay(this);
            if (spl != nullptr) {
                spl->root = this;
            }
            return size_left();
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

    static void splay(Node* tree) {
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
        splay(tree);
    }

    struct iterator {
        Splay<T>* spl;
        Node* me;
        int ind;

        iterator(Splay* spl, Node* vertex, int ind=0): spl(spl), me(vertex), ind(ind) {}

        bool operator==(const iterator& another) const {
            return me == another.me && ind == another.ind;
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
            *this = spl->get_vertex(index()+n);
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
            return (me == nullptr ? spl->size() : me->get_position()+ind);
        }
    };

    Node* root;

    void update_root() {
        if (root != nullptr) {
            root->spl = this;
        }
    }

    Splay(Node* root=nullptr): root(root) {
        update_root();
    }

    int size() {
        return (root == nullptr ? 0 : root->size);
    }

    iterator get_vertex(int k) {
        if (k == size()) {
            return end();
        }
        while (true) {
            if (k < root->size_left()) {
                root = root->l;
            } else {
                k -= root->size_left();
                if (k < root->num) {
                    break;
                }
                k -= root->num, root = root->r;
            }
        }
        splay(root);
        return iterator(this, root, k);
    }

    iterator begin() {
        return iterator(this, get_vertex(0).me);
    }

    iterator end() {
        return iterator(this, nullptr);
    }

    iterator lower_bound(const T& x) {
        Node* tree = root;
        Node* parent = nullptr;
        Node* previous = nullptr;
        while (tree != nullptr && tree->x != x) {
            previous = tree;
            if (tree->x < x) {
                tree = tree->r;
            } else {
                parent = tree, tree = tree->l;
            }
        }
        if (previous != nullptr) {
            splay(previous);
            root = previous;
        }
        if (tree == nullptr && parent == nullptr) {
            return end();
        }
        root = (tree != nullptr ? tree : parent);
        splay(root);
        return iterator(this, root);
    }

    bool exists(const T& x) {
        auto now = lower_bound(x);
        return now != end() && *now == x;
    }

    static Node* merge(Node* tree1, Node* tree2) {
        if (tree1 == nullptr) {
            return tree2;
        }
        if (tree2 == nullptr) {
            return tree1;
        }
        Node* max_left = (--Splay(tree1).end()).me;
        Node* min_right = Splay(tree2).begin().me;
        if (max_left->x < min_right->x) {
            max_left->merge_right(min_right);
        } else {
            Node* right_right = min_right->r;
            min_right->split_right();
            max_left->num += min_right->num;
            max_left->merge_right(right_right);
        }
        max_left->update();
        return max_left;
    }

    static pair<Node*, Node*> split(iterator w) {
        if (w == w.spl->end()) {
            return {w.spl->root, nullptr};
        }
        Node* left = w.me->l;
        w.me->split_left();
        if (w.ind == 0) {
            w.me->update();
            return {left, w.me};
        }
        Node* me_left = new Node(*w, w.ind);
        w.me->num -= w.ind;
        me_left->merge_left(left);
        me_left->update();
        w.me->update();
        return {me_left, w.me};
    }

    static pair<Node*, Node*> split(Node* tree, const T& x) {
        Splay now(tree);
        auto w = now.lower_bound(x);
        return split(w != now.end() && *w == x ? w+w.me->num : w);
    }

    static pair<Node*, Node*> implicit_split(Node* tree, int k) {
        Splay now(tree);
        return split(now.get_vertex(k));
    }

    void insert(const T& x, int num=1) {
        int num_split = 0;
        if (exists(x)) {
            num_split = lower_bound(x).me->num;
        }
        auto trees_right = split(root, x);
        int left_size = (trees_right.first != nullptr ? trees_right.first->size : 0);
        auto trees_left = implicit_split(trees_right.first, left_size-num_split);
        Node* node = (num_split+num > 0 ? new Node(x, num_split+num) : nullptr);
        root = merge(merge(trees_left.first, node), trees_right.second);
        update_root();
    }

    void erase(const T& x, int num=1) {
        insert(x, -num);
    }

    int sum_segment(int l, int r) {
        auto trees_right = implicit_split(root, r);
        auto trees_left = implicit_split(trees_right.first, l);
        int ans = (trees_left.second == nullptr ? 0 : trees_left.second->sum);
        root = merge(merge(trees_left.first, trees_left.second), trees_right.second);
        update_root();
        return ans;
    }

    void print() {
        for (auto &q : *this) {
            cout << q << ' ';
        }
        cout << endl;
    }
};
