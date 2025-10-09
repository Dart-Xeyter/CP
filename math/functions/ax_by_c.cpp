p build_gcd_coefs(int a, int b) {
    if (b == 0) {
        return {1, 0};
    }
    int m = a/b;
    auto [y, x] = build_gcd_coefs(b, a-m*b);
    return {x, y-m*x};
}

p gcd_coef(int a, int b) {
    int mx = max(a, b), mn = min(a, b);
    auto [x, y] = build_gcd_coefs(mx, mn);
    if (a < b) {
        swap(x, y);
    }
    return {x, y};
}

p ax_by_c(int a, int b, int c) {
    auto [x, y] = gcd_coef(a, b);
    int g = a*x+b*y;
    if (c % g != 0) {
        return {-1, -1};
    }
    a /= g, b /= g, c /= g;
    x *= c, y *= c;
    int t = x/b;
    x -= b*t, y += a*t;
    if (x < 0) {
        x += b, y -= a;
    }
    return {x, y};
}

