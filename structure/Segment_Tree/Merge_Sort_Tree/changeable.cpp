#include<bits/extc++.h>
#define int long long
#define p pair<int, int>
#define endl '\n'
const int INF = 1000000001;

using namespace __gnu_pbds;
using namespace std;

typedef tree<p, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct Merge_Sort_Tree{
    vector<ordered_set> do_arr;
    int len;

    Merge_Sort_Tree(vector<int> &a) {
        len = 1;
        while (len < a.size()) {
            len <<= 1;
        }
        do_arr.assign(len << 1, {});
        for (int q = len; q < len+a.size(); q++) {
            do_arr[q].insert({a[q-len], q-len});
        }
        for (int q = len-1; q > 0; q--) {
            for (p q1 : do_arr[2*q]) {
                do_arr[q].insert(q1);
            }
            for (p q1 : do_arr[2*q+1]) {
                do_arr[q].insert(q1);
            }
        }
    }

    void change(int q, int x) {
        int q1 = q+len, value = do_arr[q1].begin()->first;
        while (q1 > 0) {
            do_arr[q1].erase({value, q});
            do_arr[q1].insert({x, q});
            q1 /= 2;
        }
    }

    int ans(int l, int r, int l1, int r1, int q, int x) {
        if (l1 >= r || l >= r1) {
            return 0;
        }
        if (l1 <= l && r <= r1) {
            return do_arr[q].order_of_key({x, INF});
        }
        int m = ((l+r) >> 1);
        return ans(l, m, l1, r1, 2*q, x)+ans(m, r, l1, r1, 2*q+1, x);
    }
};

