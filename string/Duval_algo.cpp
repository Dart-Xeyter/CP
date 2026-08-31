vector<int> Lyndon(string s) {
    int n = s.size();
    s += '#';
    vector<int> a = {0};
    int ind = 0, q = 1, q1 = 0;
    while (ind < n) {
        if (s[q] == s[q1]) {
            q++, q1++;
        } else if (s[q] > s[q1]) {
            q++, q1 = ind;
        } else {
            int len = q-q1;
            while (ind+len <= q) {
                ind += len;
                a.push_back(ind);
            }
            q = ind+1, q1 = ind;
        }
    }
    return a;
}

