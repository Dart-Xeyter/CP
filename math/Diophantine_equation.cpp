pair<int, p> get_gcd(int a, int b) {
    if (a == 0) {
        return {b, {0, 1}};
    }
    pair<int, p> k = get_gcd(b % a, a);
    k.second.second -= b/a*k.second.first;
    swap(k.second.first, k.second.second);
    return k;
}

p ax_by_c(int a, int b, int c) {
    pair<int, p> k = get_gcd(a, b);
    if (c % k.first != 0) {
        return {-1, -1};
    }
    int x = k.second.first*(c/k.first), y = k.second.second*(c/k.first);
    int need = (x % (b/k.first)+b/k.first) % (b/k.first);
    y -= (need-x)/(b/k.first)*(a/k.first), x = need;
    return {x, y};
}

int KTO(int x1, int x2, int mod1, int mod2) {
    p k = ax_by_c(mod1, mod2, x2-x1);
    if (k.first == -1) {
        return -1;
    }
    int lcp = mod1*mod2/__gcd(mod1, mod2), x = k.first*mod1+x1;
    return (x % lcp+lcp) % lcp;
}
