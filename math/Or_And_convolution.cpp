vector<int> SOS(vector<int> a, bool rev = false) {
    int n = a.size();
    for (int q1 = 0; (1 << q1) < n; q1++) {
        for (int q = 0; q < n; q++) {
            if ((q >> q1) & 1) {
                if (!rev) {
                    a[q] += a[q ^ (1 << q1)];
                    a[q] -= C*(a[q] >= C);
                } else {
                    a[q] -= a[q ^ (1 << q1)];
                    a[q] += C*(a[q] < 0);
                }
            }
        }
    }
    return a;
}

vector<int> or_convolution(vector<int> a, vector<int> b) {
    int n = a.size();
    a = SOS(a), b = SOS(b);
    vector<int> c(n);
    for (int q = 0; q < n; q++) {
        c[q] = a[q]*b[q] % C;
    }
    return SOS(c, true);
}

vector<int> and_convolution(vector<int> a, vector<int> b) {
    int n = a.size(), ALL = n-1;
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

