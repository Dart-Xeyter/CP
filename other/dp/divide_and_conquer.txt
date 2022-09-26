vector<vector<int>> d;

int cost(int q2, int q1) {
    return 0;//code
}

void make_ans(int q, int l, int r, int l1, int r1) {
    if (r-l == 0) {
        return;
    }
    int q1 = (l+r)/2, opt = -1;
    for (int q2 = l1; q2 <= min(q1-1, r1); q2++) {
        int w = d[q-1][q2]+cost(q2, q1);
        if (w < d[q][q1]) {
            d[q][q1] = w, opt = q2;
        }
    }
    make_ans(q, l, q1, l1, opt);
    make_ans(q, q1+1, r, opt, r1);
}
