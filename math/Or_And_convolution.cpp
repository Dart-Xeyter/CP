template <bool Rev = false>
vector<int> SOS(vector<int> a) {
    int n = (int)a.size();
    for (int q1 = 1; q1 < n; q1 <<= 1) {
        for (int q2 = q1; q2 < n; q2 += (q1 << 1)) {
            for (int q = q2; q < q2+q1; q++) {
                if constexpr (!Rev) {
                    a[q] += a[q ^ q1];
                } else {
                    a[q] -= a[q ^ q1];
                }
            }
        }
    }
    for (int& q : a) {
        q = (q % C+C) % C;
    }
    return a;
}

vector<int> num_ones;

void make_num_ones(int n) {
    num_ones.assign(1 << n, 0);
    for (int q = 0; q < n; q++) {
        num_ones[1 << q] = 1;
    }
    for (int q = 1; q < (1 << n); q++) {
        int last_bit = q-(q & (q-1));
        num_ones[q] = num_ones[q ^ last_bit]+num_ones[last_bit];
    }
}

int SOS_value(int q, const vector<int> &a) {
    int ans = (1-((num_ones[q] & 1) << 1))*a[0];
    for (int q1 = q; q1 > 0; q1 = ((q1-1) & q)) {
        ans += (1-((num_ones[q ^ q1] & 1) << 1))*a[q1];
    }
    return (ans % C+C) % C;
}

auto or_convolution_SOS(const vector<int> &a, const vector<int> &b) {
    int n = (int)a.size();
    vector<int> c(n);
    for (int q = 0; q < n; q++) {
        c[q] = a[q]*b[q] % C;
    }
    return c;
}

vector<int> or_convolution(const vector<int>& a, const vector<int>& b) {
    return SOS<true>(or_convolution_SOS(SOS(a), SOS(b)));
}

vector<int> and_convolution(vector<int> a, vector<int> b) {
    int n = (int)a.size(), ALL = n-1;
    for (int q = 0; q < (n >> 1); q++) {
        swap(a[q], a[q ^ ALL]);
        swap(b[q], b[q ^ ALL]);
    }
    vector<int> c = or_convolution(a, b);
    for (int q = 0; q < (n >> 1); q++) {
        swap(c[q], c[q ^ ALL]);
    }
    return c;
}

