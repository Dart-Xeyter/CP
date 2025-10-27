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
    while (B0.size() <= n) {
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
    B0.resize(n+1, 0);
    return B0;
}

vector<int> divide(vector<int> A, vector<int> B) {
    int n = A.size(), m = B.size();
    if (n < m) {
        return {0};
    }
    int k = n-m+1;
    reverse(A.begin(), A.end());
    A.resize(k);
    reverse(B.begin(), B.end());
    auto Q = multiply(A, inverse(B, k));
    Q.resize(k, 0);
    reverse(Q.begin(), Q.end());
    return Q;
}

vector<int> remainder(vector<int> A, vector<int> B) {
    int n = A.size(), m = B.size();
    if (n < m) {
        return A;
    }
    auto Q = divide(A, B);
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
    if (y == 0) {
        return {1};
    }
    if (y % 2 == 0) {
        auto res = remainder(multiply(A, A), MOD);
        return pow1(res, y/2, MOD);
    }
    auto res = multiply(pow1(A, y-1, MOD), A);
    return remainder(res, MOD);
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

