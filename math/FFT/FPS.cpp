vector<int> Newton_method(vector<int> f0, auto& P, auto& dP, int n) {
    while (f0.size() <= n) {
        int k = f0.size();
        auto num = P(f0), den = dP(f0);
        den = inverse(den, 2*k);
        auto f1 = multiply(num*(-1), den);
        for (int q = 0; q < k; q++) {
            f1[q] += f0[q];
            f1[q] -= C*(f1[q] >= C);
        }
        f0 = {f1.begin(), f1.begin()+2*k};
    }
    return {f0.begin(), f0.begin()+n+1};
}

vector<int> square_root(vector<int>& A, int n) {
    assert(A[0] == 1);
    auto P = [&A](vector<int>& f) {
        auto f_2 = multiply(f, f);
        int len = max(A.size(), f_2.size());
        f_2.resize(len, 0);
        for (int q = 0; q < A.size(); q++) {
            f_2[q] -= A[q];
            f_2[q] += C*(f_2[q] < 0);
        }
        return f_2;
    };
    auto dP = [](vector<int>& f) {
        return f*2;
    };
    vector<int> f0 = {1};
    return Newton_method(f0, P, dP, n);
}

