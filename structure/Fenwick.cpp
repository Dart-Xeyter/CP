struct Fen {
    vector<int> fen;
    int n;

    Fen(int n1) {
        n = n1+1;
        fen.assign(n, 0);
    }

    void plus(int q, int x) {
        q++;
        for (; q < n; q += (q & (-q))) {
            fen[q] += x;
        }
    }

    int sum(int q) {
        int ans = 0;
        for (; q > 0; q -= (q & (-q))) {
            ans += fen[q];
        }
        return ans;
    }
};
