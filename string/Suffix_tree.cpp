struct Edge {
    int x, y;
    int l, r;
};

struct Pos {
    Edge e;
    int pos = -1;
};

struct Suf_Tree {
    const int E = 26, F = 'a', INF;
    vector<vector<Edge*>> d;
    vector<int> term, suf;
    string s;

    Suf_Tree(string s_): INF(s_.size()) {
        add_vertex();
        for (char q : s_) {
            s += q;
            FNL = add_symbol(q);
        }
        FNL = {{split_edge(FNL.e, FNL.pos)}};
        while (FNL.e.x != 0) {
            term[FNL.e.x]++, FNL = {{suf[FNL.e.x]}};
        }
        term[0]++;
    }

    int add_vertex() {
        d.emplace_back(E, nullptr);
        term.push_back(0);
        suf.push_back(0);
        return (int)d.size()-1;
    }

    int create(int x, char w) {
        int L = s.size();
        int v = add_vertex();
        Edge* e = new Edge{x, v, L-1, INF};
        d[x][w-F] = e;
        return v;
    }

    Pos go(Pos x, char w) {
        if (x.pos == -1 && d[x.e.x][w-F] != nullptr) {
            x = {*d[x.e.x][w-F]};
            x.pos = x.e.l;
        }
        if (x.pos == -1 || s[x.pos] != w) {
            return {{-1}};
        }
        if (++x.pos == x.e.r) {
            return {{x.e.y}};
        }
        return x;
    }

    Pos find_suf(Edge e) {
        Pos link = {{suf[e.x]}};
        for (int q = e.l+(e.x == 0); q < e.r; q++) {
            link = go(link, s[q]);
            if (link.pos == -1) {
                continue;
            }
            int len = link.e.r-link.e.l;
            if (q+len > e.r) {
                link.pos += e.r-q-1;
                break;
            }
            link = {{link.e.y}}, q += len-1;
        }
        return link;
    }

    int split_edge(Edge e, int pos) {
        if (pos == -1) {
            return e.x;
        }
        int v = add_vertex();
        Edge* up = new Edge{e.x, v, e.l, pos};
        Edge* down = new Edge{v, e.y, pos, e.r};
        d[e.x][s[e.l]-F] = up;
        d[v][s[pos]-F] = down;
        Pos link = find_suf(*up);
        suf[v] = split_edge(link.e, link.pos);
        return v;
    }

    Pos FNL = {{0}};

    Pos add_symbol(char w) {
        Pos will = go(FNL, w);
        if (will.e.x != -1) {
            return will;
        }
        FNL = {{split_edge(FNL.e, FNL.pos)}};
        while (go(FNL, w).e.x == -1) {
            term[create(FNL.e.x, w)]++;
            if (FNL.e.x == 0) {
                return FNL;
            }
            FNL = {{suf[FNL.e.x]}};
        }
        return go(FNL, w);
    }
};

