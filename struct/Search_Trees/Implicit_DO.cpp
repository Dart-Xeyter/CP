#include <bits/stdc++.h>
#define int long long
//#define endl '\n'
const int INF = 1e9+1;

using namespace std;
using p = pair<int, int>;

struct Implicit_DO {
    struct Node {
        Node* l = nullptr;
        Node* r = nullptr;
        int num = 0, sum = 0;
    };

    static void make_left_son(Node* tree) {
        tree->l = (tree->l == nullptr ? new Node() : tree->l);
    }

    static void make_right_son(Node* tree) {
        tree->r = (tree->r == nullptr ? new Node() : tree->r);
    }

    static void do_add(Node* tree, int q, int num) {
        tree->num += num, tree->sum += q*num;
    }

    static void update(Node* tree) {
        tree->num = tree->sum = 0;
        if (tree->l != nullptr) {
            tree->num += tree->l->num, tree->sum += tree->l->sum;
        }
        if (tree->r != nullptr) {
            tree->num += tree->r->num, tree->sum += tree->r->sum;
        }
    }

    static pair<Node*, p> get_k(Node* tree, int l, int r, int k) {
        if (k == tree->num) {
            return {nullptr, {INF, 0}};
        }
        while (r-l > 1) {
            int left_size = (tree->l == nullptr ? 0 : tree->l->num);
            int m = (l+r)/2;
            if (left_size > k) {
                r = m, tree = tree->l;
            } else {
                k -= left_size;
                l = m, tree = tree->r;
            }
        }
        return {tree, {l, k}};
    }

    Node* root;
    int n;

    Implicit_DO(int n): root(new Node()), n(n) {}

    int size() {
        return root->num;
    }

    static void add(Node* tree, int l, int r, int q, int num) {
        vector<Node*> parents;
        while (r-l > 1) {
            parents.push_back(tree);
            int m = (l+r)/2;
            if (q < m) {
                make_left_son(tree);
                r = m, tree = tree->l;
            } else {
                make_right_son(tree);
                l = m, tree = tree->r;
            }
        }
        do_add(tree, l, num);
        while (!parents.empty()) {
            update(parents.back());
            parents.pop_back();
        }
    }

    void insert(int q, int num = 1) {
        add(root, 0, n, q, num);
    }

    void erase(int q, int num = 1) {
        add(root, 0, n, q, -num);
    }

    static int func(Node* tree, int l, int r, int l1, int r1, int type) {
        if (l1 >= r || l >= r1 || tree == nullptr) {
            return 0;
        }
        if (l1 <= l && r <= r1) {
            return (type == 0 ? tree->num : tree->sum);
        }
        int m = (l+r)/2;
        return func(tree->l, l, m, l1, r1, type)+func(tree->r, m, r, l1, r1, type);
    }

    int num_segment(int l, int r) {
        return func(root, 0, n, l, r, 0);
    }

    int sum_value(int l, int r) {
        return func(root, 0, n, l, r+1, 1);
    }

    int sum_index(int l, int r) {
        auto elem_l = get_k(root, 0, n, l);
        auto elem_r = get_k(root, 0, n, r);
        int sum_all = sum_value(elem_l.second.first, elem_r.second.first);
        sum_all -= elem_l.second.second*elem_l.second.first;
        int elem_num = (elem_r.first == nullptr ? 0 : elem_r.first->num);
        sum_all -= (elem_num-elem_r.second.second)*elem_r.second.first;
        return sum_all;
    }

    int get_element(int k) {
        return get_k(root, 0, n, k).second.first;
    }
};
