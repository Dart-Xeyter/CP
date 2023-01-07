long double PI = 3.14159265358979323846;

struct Complex {
    long double x, y;

    Complex(long double x1 = 0, long double y1 = 0): x(x1), y(y1) {}

    Complex operator+(Complex z) {
        return Complex(x+z.x, y+z.y);
    }

    Complex operator-(Complex z) {
        return Complex(x-z.x, y-z.y);
    }

    Complex operator*(Complex z) {
        return Complex(x*z.x-y*z.y, x*z.y+y*z.x);
    }
};

vector<Complex> w;
vector<int> pos;
int len;

void make_FFT(int n) {
    len = 1, w = {Complex(), Complex(1)};
    int q2 = 0;
    while (len < n) {
        len *= 2, q2++;
        for (int q1 = 0; q1 < len; q1++) {
            w.push_back(Complex(cosl(2*PI*q1/len), sinl(2*PI*q1/len)));
        }
    }
    pos.assign(len, -1);
    for (int q = 0; q < len; q++) {
        int k = 0;
        for (int q1 = 0; q1 < q2; q1++) {
            k |= (((q >> q1) & 1) << (q2-q1-1));
        }
        pos[q] = k;
    }
}

vector<Complex> FFT(vector<Complex> a) {
    int n = a.size();
    vector<Complex> ans(n);
    for (int q = 0; q < n; q++) {
        ans[pos[q]] = a[q];
    }
    for (int q = 1; q < n; q <<= 1) {
        int q_ = (q << 1);
        for (int q1 = 0; q1 < n; q1 += q_) {
            for (int q2 = q1; q2 < q1+q; q2++) {
                Complex x = ans[q2], y = ans[q2+q];
                ans[q2] = x+w[q_+q2-q1]*y, ans[q2+q] = x-w[q_+q2-q1]*y;
            }
        }
    }
    return ans;
}

vector<int> rev_FFT(vector<Complex> a) {
    int n = a.size();
    vector<Complex> ans1 = FFT(a);
    vector<int> ans;
    for (Complex &q : ans1) {
        ans.push_back(llround(q.x/n));
    }
    reverse(ans.begin()+1, ans.end());
    return ans;
}

vector<int> mul(vector<int> &a, vector<int> &b) {
    int len1 = 1;
    while (len1 < a.size()+b.size()) {
        len1 *= 2;
    }
    vector<Complex> a1, b1;
    for (int q : a) {
        a1.push_back(Complex(q));
    }
    for (int q = a1.size(); q < len1; q++) {
        a1.push_back(Complex());
    }
    for (int q : b) {
        b1.push_back(Complex(q));
    }
    for (int q = b1.size(); q < len1; q++) {
        b1.push_back(Complex());
    }
    make_FFT(len1);
    vector<Complex> val1 = FFT(a1), val2 = FFT(b1), c1;
    for (int q = 0; q < val1.size(); q++) {
        c1.push_back(val1[q]*val2[q]);
    }
    vector<int> c = rev_FFT(c1);
    return c;
}

