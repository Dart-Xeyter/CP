int pow1(int x, int y, int z) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % z, y/2, z);
    }
    return pow1(x, y-1, z)*x % z;
}

int find_log(int a, int b, int C) {
    if (a == 0) {
        return (b == 1 ? 0 : b == 0 ? 1 : -1);
    }
    int sqrt1 = sqrt(C);
    unordered_map<int, int> degs;
    degs.reserve(sqrt1);
    int deg = 1;
    for (int q = 0; q < sqrt1; q++) {
        if (degs.find(deg) == degs.end()) {
            degs[deg] = q;
        }
        deg = deg*a % C;
    }
    int rev_deg = pow1(deg, C-2, C), rev_now = 1;
    for (int q = 0; q < C; q += sqrt1) {
        int need = b*rev_now % C;
        if (degs.find(need) != degs.end()) {
            return q+degs[need];
        }
        rev_now = rev_now*rev_deg % C;
    }
    return -1;
}
