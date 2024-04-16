int floor_sum(int a, int b, int k) { // [a/b]+...+[k*a/b]
    if (a >= b) {
        int t = a/b, r = a % b;
        return k*(k+1)/2*t+floor_sum(r, b, k);
    }
    if (a == 0) {
        return 0;
    }
    int m = k*a/b, total = k*m;
    int complement = floor_sum(b, a, m);
    int on_diag = k*gcd(a, b)/b;
    return total+on_diag-complement;
}

int floor_sum(int a, int b, int l, int r) {
    return floor_sum(a, b, max(0LL, r-1))-floor_sum(a, b, max(0LL, l-1));
}

int sum_mod(int a, int b, int l, int r) {
    int amount = r*(r-1)/2-l*(l-1)/2;
    return a*amount-b*floor_sum(a, b, l, r);
}

