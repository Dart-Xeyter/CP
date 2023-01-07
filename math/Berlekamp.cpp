const int C = 1000000007;

int pow1(int x, int y, int z=C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % z, y/2, z);
    }
    return pow1(x, y-1, z)*x % z;
}

vector<int> Berlekamp(vector<int> &a) {
    vector<int> R_n = {1}, R_m;
    int L_n = 0, L_m = -1, dm = 0, q1 = 0, n = a.size();
    for (int q = 0; q < n; q++) {
        int dn = 0;
        for (int q2 = 0; q2 <= L_n; q2++) {
            dn += R_n[q2]*a[q-q2] % C;
        }
        dn %= C;
        if (dn != 0) {
            vector<int> R_new;
            int L_new;
            if (dm == 0) {
                R_new = vector<int>(q+2, 0), R_new[0] = 1, L_new = q+1;
            } else {
                R_new = R_n, L_new = max(L_n, L_m+q-q1);
                for (int q2 = L_n; q2 < L_m+q-q1; q2++) {
                    R_new.push_back(0);
                }
                for (int q2 = q-q1; q2 <= L_m+q-q1; q2++) {
                    R_new[q2] -= R_m[q2-(q-q1)]*dn % C*pow1(dm, C-2) % C;
                    R_new[q2] %= C;
                }
            }
            if (L_n < L_new) {
                R_m = R_n, L_m = L_n, dm = dn, q1 = q;
            }
            R_n = R_new, L_n = L_new;
        }
    }
    vector<int> rec;
    for (int q = 1; q < R_n.size(); q++) {
        rec.push_back((C-R_n[q]) % C);
        if (rec.back() > C/2){
            rec.back() -= C;
        }
    }
    return rec;
}

