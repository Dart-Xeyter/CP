#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

template <typename T>
struct AVL {
    struct Node {
        T x;
        int h;
        int num, value;
        Node* l;
        Node* r;
        Node* p;
        int size, sum;

        Node(T x, int num=1): x(std::move(x)), h(1), num(num), value(x), l(nullptr), r(nullptr), p(nullptr), size(num), sum(value*num) {}

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
            size = num+size_left()+size_right();
            sum = value*num+(l == nullptr ? 0 : l->sum)+(r == nullptr ? 0 : r->sum);
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

        int get_position() {
            Node* tree = this;
            int pos = tree->size_left();
            while (tree->p != nullptr) {
                if (tree == tree->p->r) {
                    pos += tree->p->size_left()+tree->p->num;
                }
                tree = tree->p;
            }
            return pos;
        }
    };

    void change_son(Node* tree, Node* was, Node* will) {
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

    void swap(Node* tree1, Node* tree2) {
        ::swap(tree1->x, tree2->x);
        ::swap(tree1->num, tree2->num);
        ::swap(tree1->value, tree2->value);
    }

    Node* rotate_left(Node* tree) {
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

    Node* rotate_right(Node* tree) {
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

    Node* big_left(Node* tree) {
        rotate_right(tree->r);
        return rotate_left(tree);
    }

    Node* big_right(Node* tree) {
        rotate_left(tree->l);
        return rotate_right(tree);
    }

    void repair(Node* tree) {
        if (tree == nullptr) {
            return;
        }
        int d = tree->height_left()-tree->height_right();
        if (d == 2 && tree->l->height_left() >= tree->l->height_right()) {
            tree = rotate_right(tree);
        } else if (d == 2) {
            tree = big_right(tree);
        } else if (d == -2 && tree->r->height_right() >= tree->r->height_left()) {
            tree = rotate_left(tree);
        } else if (d == -2) {
            tree = big_left(tree);
        } else {
            tree->update();
        }
        root = tree;
        repair(tree->p);
    }

    struct iterator {
        AVL<T>* avl;
        Node* me;
        int ind;

        iterator(AVL* avl, Node* vertex, int ind=0): avl(avl), me(vertex), ind(ind) {}

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
            *this = avl->get_vertex(index()+n);
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
            if (me == nullptr) {
                return avl->size();
            }
            return me->get_position()+ind;
        }
    };

    Node* root;

    AVL(Node* root=nullptr): root(root) {}

    int size() {
        return (root == nullptr ? 0 : root->size);
    }

    iterator get_vertex(int k) {
        if (k == size()) {
            return end();
        }
        Node* tree = root;
        while (true) {
            if (k < tree->size_left()) {
                tree = tree->l;
            } else {
                k -= tree->size_left();
                if (k < tree->num) {
                    break;
                }
                k -= tree->num, tree = tree->r;
            }
        }
        return iterator(this, tree, k);
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
        while (tree != nullptr && tree->x != x) {
            if (tree->x < x) {
                tree = tree->r;
            } else {
                parent = tree, tree = tree->l;
            }
        }
        return iterator(this, tree != nullptr ? tree : parent);
    }

    bool exists(const T& x) {
        auto now = lower_bound(x);
        return now != end() && *now == x;
    }

    void insert(const T& x, int num=1) {
        if (root == nullptr) {
            root = new Node(x, num);
            return;
        }
        auto w = lower_bound(x);
        Node* vertex;
        if (w != end() && *w == x) {
            vertex = w.me;
            vertex->num += num;
        } else if (w != end() && w.me->l == nullptr) {
            vertex = new Node(x, num);
            w.me->merge_left(vertex);
        } else {
            vertex = new Node(x, num);
            (--w).me->merge_right(vertex);
        }
        repair(vertex);
    }

    void erase(const T& x, int num=1) {
        auto w = lower_bound(x);
        if (w == end() || *w != x) {
            return;
        }
        Node* vertex;
        if (w.me->num > num) {
            vertex = w.me;
            vertex->num -= num;
        } else if (w.me->p == nullptr && (w.me->l == nullptr || w.me->r == nullptr)) {
            root = (w.me->l == nullptr ? w.me->r : w.me->l);
            w.me->split_left(), w.me->split_right();
            return;
        } else if (w.me->l == nullptr) {
            vertex = w.me->p;
            Node* replace = w.me->r;
            w.me->split_right();
            change_son(w.me->p, w.me, replace);
        } else {
            auto w_was = w--;
            swap(w_was.me, w.me);
            vertex = w.me->p;
            Node* replace = w.me->l;
            w.me->split_left();
            change_son(w.me->p, w.me, replace);
        }
        repair(vertex);
    }

    int sum_segment(int l, int r, int l1, int r1, Node* tree) {
        if (l >= r1 || l1 >= r || tree == nullptr) {
            return 0;
        }
        if (l1 <= l && r <= r1) {
            return tree->sum;
        }
        int m1 = l+tree->size_left(), m2 = m1+tree->num;
        if (m1 <= l1 && r1 <= m2) {
            return (r1-l1)*tree->value;
        }
        int ans = max(0LL, min(r1, m2)-max(l1, m1))*tree->value;
        ans += sum_segment(l, m1, l1, r1, tree->l);
        ans += sum_segment(m2, r, l1, r1, tree->r);
        return ans;
    }

    int sum_segment(int l, int r) {
        return sum_segment(0, size(), l, r, root);
    }
};
