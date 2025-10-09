int pow1(int x, int y, int C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2, C);
    }
    return pow1(x, y-1, C)*x % C;
}

mt19937 randint(17957179);

struct Poly {
    int a, b;
};

Poly mul(Poly x, Poly y, int A, int C) {
    int a = x.a*y.b+x.b*y.a;
    int b = x.b*y.b+x.a*y.a % C*A;
    return {a % C, b % C};
}

int find_sqrt(int a, int C) {
    while (true) {
        int t = randint() % (C-1)+1;
        Poly x_t(1, t);
        int deg = (C-1)/2;
        Poly poly(0, 1);
        while (deg > 0) {
            if (deg & 1) {
                poly = mul(poly, x_t, a, C);
            }
            x_t = mul(x_t, x_t, a, C);
            deg >>= 1;
        }
        auto [A, B] = poly;
        B = (B+C-1) % C;
        int val = A*A % C*a % C-B*B % C;
        if (A == 0 || val != 0) {
            continue;
        }
        int rev_a = pow1(A, C-2, C);
        return B*rev_a % C;
    }
}

int square_root(int a, int C) {
    if (a == 0 || C == 2) {
        return a;
    }
    int sign = pow1(a, (C-1)/2, C);
    if (sign != 1) {
        return -1;
    }
    if (C % 4 == 3) {
        return pow1(a, (C+1)/4, C);
    }
    return find_sqrt(a, C);
}

