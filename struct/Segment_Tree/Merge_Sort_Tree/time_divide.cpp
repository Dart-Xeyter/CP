template <typename T>
struct MST {
    vector<vector<T>> a;
    vector<int> answers;
    int len = 1;

    explicit MST(int n) {
        while (len < n) {
            len <<= 1;
        }
        a.assign(2*len, {});
        answers.assign(len, -1);
    }

    void insert(int l, int r, int l1, int r1, int q, T x) {
        if (l >= r1 || l1 >= r) {
            return;
        }
        if (l1 <= l && r <= r1) {
            a[q].push_back(x);
            return;
        }
        int m = (l+r) >> 1;
        insert(l, m, l1, r1, 2*q, x);
        insert(m, r, l1, r1, 2*q+1, x);
    }

    void DFS(int q, Flow flow, int x, int y) {
        for (T q1 : a[q]) {
            flow.add_edge(q1.x, q1.y, q1.c);
        }
        int ans = flow.max_flow(x, y);
        if (q >= len) {
            answers[q-len] = ans;
            return;
        }
        DFS(2*q, flow, x, y);
        DFS(2*q+1, flow, x, y);
    }
};

