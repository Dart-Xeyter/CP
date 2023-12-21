vector<int> pref_func(const string& s) {
    int n = (int)s.size();
    vector<int> pref(n, 0);
    for (int q = 1; q < n; q++) {
        pref[q] = pref[q-1];
        while (pref[q] > 0 && s[pref[q]] != s[q]) {
            pref[q] = pref[pref[q]-1];
        }
        pref[q] += (s[pref[q]] == s[q]);
    }
    return pref;
}

