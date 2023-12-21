static constexpr int modules[] = {
        1791179179,
        1791791791,
        570057179,
        179179057,
        57057179,
        17957179, // 5
        5700179,
        2057179,
        571799,
        179057,
        44179,
        571794442013,
        1057057179057179057,
};

static constexpr int multiplier_size = 2;
static constexpr int multiplier[] = {
        17957179, 179
};

template <typename T>
struct Hash {
    const int C = 0, D;
    vector<int> degs, hashs;

    static int get_D(int type) {
        return multiplier[min(multiplier_size-1, type)];
    }

    explicit Hash(const T& s, int type = 0): C(modules[type]), D(get_D(type)){
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

