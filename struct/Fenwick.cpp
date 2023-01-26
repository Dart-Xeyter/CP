struct Fen {
    vector<int> fen;
    int n;

    Fen(int n1) {
        n = n1+1;
        fen.assign(n, 0);
    }

    void plus(int q, int x) {
        for (++q; q < n; q += (q & -q)) {
            fen[q] += x;
        }
    }

    int sum(int q) {
        int res = 0;
        for (; q > 0; q -= (q & -q)) {
            res += fen[q];
        }
        return res;
    }

    int sum(int l, int r) {
        return sum(r)-sum(l);
    }
};

