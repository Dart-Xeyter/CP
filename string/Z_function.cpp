vector<int> z_func(const string& s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    int ind_max = 0, right_max = 1;
    for (int q = 1; q < n; q++) {
        if (q+z[q-ind_max] < right_max) {
            z[q] = z[q-ind_max];
            continue;
        }
        while (right_max < n && s[right_max-q] == s[right_max]) {
            right_max++;
        }
        z[q] = right_max-q;
        ind_max = q, right_max += (z[q] == 0);
    }
    return z;
}

