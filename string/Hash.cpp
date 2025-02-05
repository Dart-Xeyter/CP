static constexpr int mods[] = {
        1791179179, 1791791791,
        1057057179057179057
};

static constexpr int muls[] = {
        17957179, 179,
        179179057,
};

template <typename T>
struct Hash {
    const int C, D;
    vector<int> degs, hashs;

    Hash(const T& s, int type = 0): C(mods[type]), D(muls[type]) {
        degs = {1}, hashs = {0};
        for (auto q : s) {
            degs.push_back(degs.back()*D % C);
            hashs.push_back((hashs.back()*D+q) % C);
        }
    }

    int hash(int l, int r) const {
        int ans = (hashs[r]-hashs[l]*degs[r-l]) % C;
        return ans+(ans < 0)*C;
    }
};

