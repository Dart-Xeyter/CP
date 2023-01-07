vector<int> Manacher(vector<int> &a1) {
    int n = a1.size();
    vector<int> a = {a1[0]};
    for (int q = 1; q < n; q++) {
        a.push_back(INF);
        a.push_back(a1[q]);
    }
    n = a.size();
    vector<int> man = {1};
    int ind = 0;
    for (int q = 1; q < n; q++) {
        int k = q;
        if (ind+man[ind] > q) {
            k = min(man[ind]+ind, q+man[2*ind-q]);
        }
        while (k < n && 2*q-k > -1 && a[k] == a[2*q-k]) {
            k++;
        }
        man.push_back(k-q);
        if (k > man[ind]+ind) {
            ind = q;
        }
    }
    for (int q = 0; q < n; q++) {
        if (a[q] == INF) {
            man[q] -= man[q] % 2;
        } else {
            man[q] -= 1-man[q] % 2;
        }
    }
    return man;
}

