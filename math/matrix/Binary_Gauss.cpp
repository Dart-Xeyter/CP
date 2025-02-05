#include <tr2/dynamic_bitset>
using Bitset = tr2::dynamic_bitset<>;

struct Gauss {
    vector<Bitset> a;
    int n, m;

    explicit Gauss(auto& a_): n(a_.size()), m(a_[0].size()) {
        for (int q = 0; q < n; q++) {
            a.emplace_back(m);
            for (int q1 = 0; q1 < m; q1++) {
                a[q][q1] = a_[q][q1];
            }
        }
    }

    void subtract(int q, int q1) {
        for (int q2 = 0; q2 < n; q2++) {
            if (q != q2 && a[q2][q1]) {
                a[q2] ^= a[q];
            }
        }
    }

    void gauss() {
        for (int q = 0; q < n; q++) {
            int q1 = (int)a[q].find_first();
            if (q1 != m) {
                subtract(q, q1);
            }
        }
    }

    auto annihilator() const {
        vector<int> leader(n);
        for (int q = 0; q < n; q++) {
            leader[q] = (int)a[q].find_first();
        }
        vector<Bitset> ans;
        for (int q1 = 0; q1 < m; q1++) {
            if (ranges::find(leader, q1) != leader.end()) {
                continue;
            }
            ans.emplace_back(m+1);
            for (int q = 0; q < n; q++) {
                ans.back()[leader[q]] = a[q][q1];
            }
            ans.back().resize(m);
            ans.back()[q1] = true;
        }
        return ans;
    }
};

