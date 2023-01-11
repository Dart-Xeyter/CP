const int INF = 1e18, log_INF = 18;

struct Num {
    vector<int> a;

    Num(int x = 0): a({x}) {}

    explicit operator int() {
        return a[0];
    }

    bool operator==(const Num& num) const = default;

    auto operator<=>(const Num& num) const {
        if (a.size() != num.a.size()) {
            return a.size() <=> num.a.size();
        }
        for (int q = (int)a.size()-1; q > -1; q--) {
            if (a[q] != num.a[q]) {
                return a[q] <=> num.a[q];
            }
        }
        return 0 <=> 0;
    }

    Num& operator+=(const Num& num) {
        vector<int> ans;
        int is = 0;
        for (int q = 0; q < max(a.size(), num.a.size()) || is > 0; q++) {
            is += (q < a.size() ? a[q] : 0)+(q < num.a.size() ? num.a[q] : 0);
            ans.push_back(is % INF);
            is /= INF;
        }
        a = ans;
        return *this;
    }

    Num operator+(Num num) {
        return num += *this;
    }

    Num operator-=(Num num) {
        vector<int> ans;
        int is = 0;
        for (int q = 0; q < max(a.size(), num.a.size()) || is > 0; q++) {
            is += (q < a.size() ? a[q] : 0)-(q < num.a.size() ? num.a[q] : 0)-is;
            ans.push_back((is+INF) % INF);
            is = (is < 0);
        }
        a = ans;
        return *this;
    }

    Num operator-(const Num& num) {
        Num copy = *this;
        return copy -= num;
    }

    Num& operator*=(int x) {
        vector<int> ans;
        __int128 is = 0;
        for (__int128 q : a) {
            is += q*x;
            ans.push_back(is % INF);
            is /= INF;
        }
        if (is > 0) {
            ans.push_back(is);
        }
        a = ans;
        return *this;
    }

    Num operator*(int x) {
        Num copy = *this;
        return copy *= x;
    }

    Num& operator*=(const Num& num) {
        if (num == 0 || *this == 0) {
            *this = 0;
            return *this;
        }
        Num ans;
        for (int q = 0; q < num.a.size(); q++) {
            Num is = *this;
            is *= num.a[q];
            for (int q1 = 0; q1 < q; q1++) {
                is.a.insert(is.a.begin(), 0);
            }
            ans += is;
        }
        *this = ans;
        return *this;
    }

    Num operator*(Num num) {
        return num *= *this;
    }

    Num operator/(int x) {
        vector<Num> difs = {1};
        while (difs.back() < *this) {
            difs.push_back(difs.back()*2);
        }
        Num l = 0;
        for (int q = (int)difs.size()-1; q > -1; q--) {
            Num m = l+difs[q];
            if (m*x <= *this) {
                l = m;
            }
        }
        return l;
    }

    Num pow(int n) {
        if (n == 0) {
            return 1;
        }
        if (n % 2 == 0) {
            return (*this**this).pow(n/2);
        }
        return pow(n-1)**this;
    }
};

istream& operator>>(istream& in, Num& x) {
    int x1;
    cin >> x1;
    x = x1;
    return in;
}

string zfill(const string &s, int n) {
    string ans(n-(int)s.size(), '0');
    return ans+s;
}

ostream& operator<<(ostream& out, const Num& x) {
    string ans;
    for (int q = (int)x.a.size()-1; q > -1; q--) {
        ans += zfill(to_string(x.a[q]), log_INF);
    }
    int q1 = 0;
    while (ans[q1] == '0' && q1 < (int)ans.size()-1) {
        q1++;
    }
    out << ans.substr(q1, (int)ans.size()-q1);
    return out;
}

