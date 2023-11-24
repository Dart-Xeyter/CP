vector<int> add(vector<int> a, const vector<int>& b) {
    a.resize(max(a.size(), b.size()), 0);
    for (int q = 0; q < b.size(); q++) {
        a[q] += b[q];
    }
    return a;
}

vector<int> mul(vector<int> a, int x) {
    for (int& q : a) {
        q *= x;
    }
    return a;
}

auto split_in_half(const vector<int>& a, int m) {
    int n = (int)a.size();
    vector<int> a1, a2;
    for (int q = 0; q < n; q++) {
        (q < m ? a1 : a2).push_back(a[q]);
    }
    return pair{a1, a2};
}

vector<int> shift(vector<int> a, int t) {
    reverse(a.begin(), a.end());
    a.resize(a.size()+t, 0);
    reverse(a.begin(), a.end());
    return a;
}

vector<int> Karatsuba(const vector<int>& a, const vector<int>& b) {
    int m = (int)a.size()/2;
    if (m <= 57) {
        m = (int)a.size();
        vector<int> ans(2*m-1, 0);
        for (int q = 0; q < m; q++) {
            for (int q1 = 0; q1 < m; q1++) {
                ans[q+q1] += a[q]*b[q1];
            }
        }
        return ans;
    }
    auto [a1, a2] = split_in_half(a, m);
    auto [b1, b2] = split_in_half(b, m);
    vector<int> a1_b1 = Karatsuba(a1, b1), a2_b2 = Karatsuba(a2, b2);
    vector<int> a1_a2_b1_b2 = Karatsuba(add(a1, a2), add(b1, b2));
    vector<int> a1_b2_a2_b1 = add(a1_a2_b1_b2, mul(add(a1_b1, a2_b2), -1));
    return add(a1_b1, shift(add(a1_b2_a2_b1, shift(a2_b2, m)), m));
}

int degree_more(int n) {
    int deg = 1;
    while (deg < n) {
        deg *= 2;
    }
    return deg;
}

vector<int> mul(vector<int> a, vector<int> b) {
    int n = (int)max(a.size(), b.size());
    n = degree_more(n);
    a.resize(n, 0);
    b.resize(n, 0);
    return Karatsuba(a, b);
}

