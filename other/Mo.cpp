const int sqrt1 = 511;

struct SQRT {
    vector<int> a, s;

    SQRT(int C) {
        a.assign(C, 0), s.assign(C/sqrt1+1, 0);
    }

    void change(int q, int x) {
        a[q] += x, s[q/sqrt1] += x;
    }

    int find(int k) {
        int q1 = 0, sum1 = 0;
        while (sum1+s[q1] <= k) {
            sum1 += s[q1++];
        }
        q1 *= sqrt1;
        while (sum1+a[q1] <= k) {
            sum1 += a[q1++];
        }
        return q1;
    }
};

vector<vector<int>> d;
vector<int> xors;

struct Mo {
    SQRT a;
    int l = 0, r = 0;

    Mo(int C): a(C) {}

    void update(int q, int x) {
        int xor1 = 0;
        for (int q1 : d[q]) {
            if (q1 < l || r <= q1) {
                continue;
            }
            a.change(xors[q1], -1);
            xors[q1] ^= q;
            a.change(xors[q1], 1);
            xor1 ^= q1;
        }
        a.change(xor1, x);
        xors[q] = (x == 1 ? xor1 : 0);
    }

    void go(int x, int y) {
        while (x < l) {
            update(--l, 1);
        }
        while (r < y) {
            update(r++, 1);
        }
        while (l < x) {
            update(l++, -1);
        }
        while (y < r) {
            update(--r, -1);
        }
    }
};

