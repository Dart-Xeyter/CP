struct Merge_Sort_Tree {
    vector<vector<int>> do_arr;
    int len;

    Merge_Sort_Tree(vector<int> &a) {
        len = 1;
        while (len < a.size()) {
            len <<= 1;
        }
        do_arr.assign(len << 1, {});
        for (int q = len; q < len+a.size(); q++) {
            do_arr[q] = {a[q-len]};
        }
        for (int q = len-1; q > 0; q--) {
            merge(do_arr[2*q].begin(), do_arr[2*q].end(), do_arr[2*q+1].begin(), do_arr[2*q+1].end(), back_inserter(do_arr[q]));
        }
    }

    int ans(int l, int r, int l1, int r1, int q, int x) {
        if (l1 >= r || l >= r1) {
            return 0;
        }
        if (l1 <= l && r <= r1) {
            return upper_bound(do_arr[q].begin(), do_arr[q].end(), x)-do_arr[q].begin()-1;
        }
        int m = ((l+r) >> 1);
        return ans(l, m, l1, r1, 2*q, x)+ans(m, r, l1, r1, 2*q+1, x);
    }
};
