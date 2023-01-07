vector<int> z_func(string &a) {
    vector<int> z = {0};
    int ind = 0;
    for (int q1 = 1; q1 < a.size(); q1++) {
        if (ind+z[ind] >= q1 && q1+z[q1-ind] < ind+z[ind]) {
            z.push_back(z[q1-ind]);
        } else {
            int q2 = max(q1, ind+z[ind]);
            while (q2 < a.size() && a[q2] == a[q2-q1]) {
                q2++;
            }
            z.push_back(q2-q1);
            ind = q1;
        }
    }
    return z;
}

