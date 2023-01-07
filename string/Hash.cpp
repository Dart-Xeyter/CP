struct Hash {
    vector<int> hashs = {0}, deg = {1};
    const int C = 1791179179, C1 = 17957179;

    Hash(string &s) {
        for (int q : s) {
            hashs.push_back((hashs.back()*C1+q) % C);
            deg.push_back(deg.back()*C1 % C);
        }
    }

    int hash(int l, int r) {
        return ((hashs[r]-hashs[l]*deg[r-l]) % C+C) % C;
    }
};

struct Hash1 {
    vector<int> hashs = {0}, deg = {1};
    const int C = 1791791791, C1 = 179;

    Hash1(string &s) {
        for (int q : s) {
            hashs.push_back((hashs.back()*C1+q) % C);
            deg.push_back(deg.back()*C1 % C);
        }
    }

    int hash(int l, int r) {
        return ((hashs[r]-hashs[l]*deg[r-l]) % C+C) % C;
    }
};

