struct Gauss {
    vector<int> a;
    int n, C;

    Gauss(vector<int> &a1) {
        a = a1, n = a.size(), C = 0;
        unsigned long long q2 = 1;
        int max1 = *max_element(a.begin(), a.end());
        while (q2 <= max1) {
            q2 *= 2, C++;
        }
    }

    void subtract(int q, int q1) {
        for (int q2 = 0; q2 < n; q2++) {
            if (q != q2 && ((a[q2] >> q1) & 1)) {
                a[q2] ^= a[q];
            }
        }
    }

    void gauss() {
        int q = 0, q1 = C-1;
        while (q < n && q1 > -1) {
            bool flag = false;
            for (int q2 = q; q2 < n; q2++) {
                if ((a[q2] >> q1) & 1) {
                    swap(a[q], a[q2]);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                q1--;
                continue;
            }
            subtract(q++, q1--);
        }
    }
};
