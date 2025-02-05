int C, big_C;
vector<int> zeros;

vector<int> mul(const vector<int>& a, const vector<int>& s) {
    int n = (int)a.size(), m = (int)s.size();
    vector<int> ans(n+m-1);
    for (int q = 0; q < n; q++) {
        for (int q1 = 0; q1 < m; q1++) {
            ans[q+q1] += a[q]*s[q1];
            ans[q+q1] -= (ans[q+q1] >= big_C)*big_C;
        }
    }
    for (int& q : ans) {
        q %= C;
    }
    return ans;
}

auto split_halves(const vector<int>& a, int len) {
    vector<int> Q(a.begin(), a.begin()+len);
    vector<int> P(a.begin()+len, a.end());
    return pair{P, Q};
}

vector<int> operator+(const vector<int>& a, const vector<int>& s) {
    int n = (int)a.size(), m = (int)s.size();
    vector<int> ans(max(n, m));
    for (int q = 0; q < max(n, m); q++) {
        ans[q] = (q < n ? a[q] : 0)+(q < m ? s[q] : 0);
        ans[q] -= (ans[q] >= C)*C;
    }
    return ans;
}

vector<int> operator-(vector<int> a) {
    for (int& q : a) {
        q = C-q-(q == 0)*C;
    }
    return a;
}

vector<int> Karatsuba(const vector<int>& a, const vector<int>& s) {
    int n = (int)a.size(), m = (int)s.size();
    if (min(n, m) < 57) {
        return mul(a, s);
    }
    int len = min(n/2, m/2);
    auto [P1, Q1] = split_halves(a, len);
    auto [P2, Q2] = split_halves(s, len);
    vector<int> P1P2 = Karatsuba(P1, P2);
    vector<int> Q1Q2 = Karatsuba(Q1, Q2);
    vector<int> mid = Karatsuba(P1+Q1, P2+Q2);
    mid = mid+(-P1P2)+(-Q1Q2);
    mid.insert(mid.begin(), zeros.begin(), zeros.begin()+len);
    P1P2.insert(P1P2.begin(), zeros.begin(), zeros.begin()+2*len);
    return P1P2+mid+Q1Q2;
}

vector<int> multiply(vector<int>& a, vector<int>& s) {
    big_C = C*C*8;
    zeros.assign(a.size()+s.size(), 0);
    return Karatsuba(a, s);
}

