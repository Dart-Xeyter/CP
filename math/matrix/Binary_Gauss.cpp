const int MAX_N = 301, MAX_M = 300;

struct Gauss {
    vector<bitset<MAX_M>> a;
    vector<bitset<MAX_N>> s;
    vector<bool> was;
    int n, C;

    Gauss(vector<string> &a1) {
        n = a1.size(), C = a1[0].size();
        a.assign(n, 0), s.assign(n, 0), was.assign(n, false);
        for (int q = 0; q < n; q++) {
            s[q][q] = true;
            for (int q1 = 0; q1 < C; q1++) {
                a[q][q1] = (a1[q][q1] == '1');
            }
        }
    }

    void subtract(int q, int q1) {
        for (int q2 = 0; q2 < n; q2++) {
            if (q != q2 && a[q2][q1]) {
                a[q2] ^= a[q], s[q2] ^= s[q];
            }
        }
    }

    void gauss() {
        int cnt = 0, q1 = 0;
        while (cnt < n && q1 < C) {
            int ind = -1;
            for (int q2 = 0; q2 < n; q2++) {
                if (!was[q2] && a[q2][q1]) {
                    ind = q2;
                    break;
                }
            }
            if (ind == -1) {
                q1++;
                continue;
            }
            subtract(ind, q1++);
            was[ind] = true, cnt++;
        }
    }
};

