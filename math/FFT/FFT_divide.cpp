vector<int> operator*(vector<int> a, int x) {
    x = (x % C+C) % C;
    for (int& q : a) {
        q *= x, q %= C;
    }
    return a;
}

vector<int> inverse(vector<int>& A, int n) {
    assert(A[0] != 0);
    vector<int> B0 = {pow1(A[0], C-2)};
    int N = A.size();
    while (B0.size() < n) {
        int k = B0.size(), len = min(2*k, N);
        vector<int> A_k(A.begin(), A.begin()+len);
        auto A_B0 = multiply(A_k, B0);
        A_B0.erase(A_B0.begin(), A_B0.begin()+k);
        if (A_B0.empty()) {
            break;
        }
        auto B1 = multiply(A_B0*(-1), B0);
        B0.insert(B0.end(), B1.begin(), B1.begin()+k);
    }
    B0.resize(n, 0);
    return B0;
}

vector<int> divide_inv(vector<int> A, vector<int> inv_rev, int m) {
    int k = (int)A.size()-m+1;
    if (k <= 0) {
        return {0};
    }
    reverse(A.begin(), A.end());
    A.resize(k), inv_rev.resize(k);
    auto Q = multiply(A, inv_rev);
    Q.resize(k, 0);
    reverse(Q.begin(), Q.end());
    return Q;
}

vector<int> divide(vector<int> A, vector<int> B) {
    int n = A.size(), m = B.size(), k = n-m+1;
    if (k <= 0) {
        return {0};
    }
    reverse(B.begin(), B.end());
    return divide_inv(A, inverse(B, k), m);
}

vector<int> remainder(vector<int> A, vector<int>& B, vector<int>& Q) {
    int n = A.size(), m = B.size();
    if (n < m) {
        return A;
    }
    Q.resize(min(m, n-m+1));
    auto QB = multiply(Q, B);
    for (int q = 0; q < m; q++) {
        A[q] -= QB[q];
        A[q] += C*(A[q] < 0);
    }
    int ind = m-1;
    while (ind > 0 && A[ind] == 0) {
        ind--;
    }
    return {A.begin(), A.begin()+ind+1};
}

vector<int> pow1(vector<int> A, int y, vector<int>& MOD) {
    int m = MOD.size();
    vector<int> ans = {1};
    ranges::reverse(MOD);
    auto inv_rev = inverse(MOD, m);
    ranges::reverse(MOD);
    while (y != 0) {
        if (y & 1) {
            ans = multiply(ans, A);
            auto Q = divide_inv(ans, inv_rev, m);
            ans = remainder(ans, MOD, Q);
        }
        A = multiply(A, A);
        auto Q = divide_inv(A, inv_rev, m);
        A = remainder(A, MOD, Q);
        y >>= 1;
    }
    return ans;
}

int get_rec_coef(vector<int>& rec, vector<int>& a, int N) {
    vector<int> Q = rec*(-1);
    Q.push_back(1);
    auto coefs = pow1({0, 1}, N, Q);
    int ans = 0;
    for (int q = 0; q < coefs.size(); q++) {
        ans += coefs[q]*a[q] % C;
    }
    return ans % C;
}

