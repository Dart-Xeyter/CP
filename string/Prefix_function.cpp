vector<int> pref_func(string &a) {
    vector<int> pref = {0};
    for (int q1 = 1; q1 < a.size(); q1++) {
        char q = a[q1];
        int now = pref.back();
        while (now > 0 && q != a[now]) {
            now = pref[now-1];
        }
        if (q == a[now]) {
            pref.push_back(now+1);
        } else {
            pref.push_back(0);
        }
    }
    return pref;
}

