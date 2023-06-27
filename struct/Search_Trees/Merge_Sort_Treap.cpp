#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

template <typename T>
struct Treap {
    struct Node {
        static mt19937 randint;

        T x;
        int num, value;
        Node* l;
        Node* r;
        Node* p;
        unsigned y;
        int size, sum;

        Node(T x, int num=0): x(std::move(x)), num(num), value(x), l(nullptr), r(nullptr), p(nullptr), y(randint()), size(num), sum(value*num) {}

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
            int pos = tree->size_left();
            while (tree->p != nullptr) {
                if (tree == tree->p->r) {
                    pos += tree->p->size_left()+tree->num;
                }
                tree = tree->p;
            }
            return pos;
        }
    };

    Node* merge_less(Node* tree1, Node* tree2) {
        if (tree1 == nullptr || tree2 == nullptr) {
            return (tree1 == nullptr ? tree2 : tree1);
        }
        if (tree1->y < tree2->y) {
            Node* right_son = tree1->r;
            tree1->split_right();
            Node* merged = merge_less(right_son, tree2);
            tree1->merge_right(merged);
            return tree1;
        } else {
            Node* left_son = tree2->l;
            tree2->split_left();
            Node* merged = merge_less(tree1, left_son);
            tree2->merge_left(merged);
            return tree2;
        }
    }

    Node* merge(Node* tree1, Node* tree2) {
        if (tree2 == nullptr) {
            return tree1;
        }
        Treap<int> first(tree1), second(tree2);
        if (first.exists(*second.begin())) {
            auto last = --first.end();
            second.insert(*last, last.me->num);
            first.erase(*last, last.me->num);
        }
        return merge_less(first.root, second.root);
    }

    pair<Node*, Node*> split(Node* tree, const T& x) {
        if (tree == nullptr) {
            return {nullptr, nullptr};
        }
        if (tree->x <= x) {
            Node* right_son = tree->r;
            tree->split_right();
            auto trees = split(right_son, x);
            tree->merge_right(trees.first);
            return {tree, trees.second};
        } else {
            Node* left_son = tree->l;
            tree->split_left();
            auto trees = split(left_son, x);
            tree->merge_left(trees.second);
            return {trees.first, tree};
        }
    }

    pair<Node*, Node*> implicit_split(Node* tree, int k) {
        if (tree == nullptr) {
            return {nullptr, nullptr};
        }
        if (tree->size_left() < k && k < tree->size_left()+tree->num) {
            k -= tree->size_left();
            Node* left_son = tree->l;
            Node* right_son = tree->r;
            tree->split_left();
            tree->split_right();
            Node* left_vertex = new Node(tree->x, k);
            Node* right_vertex = new Node(tree->x, tree->num-k);
            left_vertex->merge_left(left_son);
            right_vertex->merge_right(right_son);
            return {left_vertex, right_vertex};
        } else if (tree->size_left() < k) {
            k -= tree->size_left()+tree->num;
            Node* right_son = tree->r;
            tree->split_right();
            auto trees = implicit_split(right_son, k);
            tree->merge_right(trees.first);
            return {tree, trees.second};
        } else {
            Node* left_son = tree->l;
            tree->split_left();
            auto trees = implicit_split(left_son, k);
            tree->merge_left(trees.second);
            return {trees.first, tree};
        }
    }

    struct iterator {
        Treap<T>* treap;
        Node* me;
        int ind;

        iterator(Treap* treap, Node* vertex, int ind=0): treap(treap), me(vertex), ind(ind) {}

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
            *this = treap->get_vertex(index()+n);
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
                return treap->size();
            }
            return me->get_position()+ind;
        }
    };

    Node* root;

    Treap(Node* root=nullptr): root(root) {}

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
        int num_split = 0;
        if (exists(x)) {
            num_split = lower_bound(x).me->num;
        }
        auto trees_right = split(root, x);
        int left_size = (trees_right.first != nullptr ? trees_right.first->size : 0);
        auto trees_left = implicit_split(trees_right.first, left_size-num_split);
        Node* node = (num_split+num > 0 ? new Node(x, num_split+num) : nullptr);
        root = merge(merge(trees_left.first, node), trees_right.second);
    }

    void erase(const T& x, int num=1) {
        insert(x, -num);
    }

    int sum_segment(int l, int r) {
        auto trees_right = implicit_split(root, r);
        auto trees_left = implicit_split(trees_right.first, l);
        int ans = (trees_left.second == nullptr ? 0 : trees_left.second->sum);
        root = merge(merge(trees_left.first, trees_left.second), trees_right.second);
        return ans;
    }
};

template <typename T>
//mt19937 Treap<T>::Node::randint(179);
mt19937 Treap<T>::Node::randint(chrono::steady_clock::now().time_since_epoch().count());

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
        Implicit_Treap<T>* treap;

        Node(T x): x(std::move(x)), l(nullptr), r(nullptr), p(nullptr), y(randint()), size(1),
                   treap(nullptr) {}

        int size_left() {
            return (l == nullptr ? 0 : l->size);
        }

        int size_right() {
            return (r == nullptr ? 0 : r->size);
        }

        void update() {
            size = 1+size_left()+size_right();
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
            int pos = tree->size_left();
            while (tree->p != nullptr) {
                if (tree == tree->p->r) {
                    pos += tree->p->size-tree->size;
                }
                tree = tree->p;
            }
            return pos;
        }
    };

    static Node* merge(Node* tree1, Node* tree2) {
        if (tree1 == nullptr || tree2 == nullptr) {
            return (tree1 == nullptr ? tree2 : tree1);
        }
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

        int index() {
            return (me == nullptr ? treap->size() : me->get_position());
        }
    };

    Node* root;

    void update_root() {
        if (root != nullptr) {
            root->spl = this;
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
        while (k != tree->size_left()) {
            if (tree->size_left() < k) {
                k -= tree->size_left()+1;
                tree = tree->r;
            } else {
                tree = tree->l;
            }
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

    void print() {
        for (auto &q : *this) {
            cout << q << ' ';
        }
        cout << endl;
    }

    static void build(Node* tree) {
        if (tree == nullptr) {
            return;
        }
        build(tree->l);
        build(tree->r);
        tree->x.second->insert(tree->x.first);
        if (tree->l != nullptr) {
            for (int q : *(tree->l->x.second)) {
                tree->x.second->insert(q);
            }
        }
        if (tree->r != nullptr) {
            for (int q : *(tree->r->x.second)) {
                tree->x.second->insert(q);
            }
        }
    }

    int num_less(int k, int x) {
        Node* tree = root;
        int ans = 0;
        while (tree != nullptr) {
            if (k <= tree->size_left()) {
                tree = tree->l;
                continue;
            }
            if (tree->l != nullptr) {
                auto w = tree->l->x.second->lower_bound(x);
                ans += w-tree->l->x.second->begin();
            }
            ans += (tree->x.first < x);
            k -= tree->size_left()+1, tree = tree->r;
        }
        return ans;
    }

    void change_value(int k, int x) {
        Node* tree = (begin()+k).me;
        int was = tree->x.first;
        tree->x.first = x;
        while (tree != nullptr) {
            tree->x.second->erase(was);
            tree->x.second->insert(x);
            tree = tree->p;
        }
    }
};

template <typename T>
//mt19937 Implicit_Treap<T>::Node::randint(179);
mt19937 Implicit_Treap<T>::Node::randint(chrono::steady_clock::now().time_since_epoch().count());
