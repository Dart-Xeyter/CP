struct Node {
    int suf = -1, len = 0;
    int term = 0, num = -1;
};

struct Automaton {
    const int E = 10, FIRST = '0';
    vector<vector<int>> d;
    vector<Node> a;
    int end;

    void build_num(int vertex) {
        a[vertex].num = (a[vertex].term > 0);
        for (int q : d[vertex]) {
            if (q != -1 && a[q].num == -1) {
                build_num(q);
            }
            if (q != -1) {
                a[vertex].num += a[q].num;
            }
        }
    }

    void build_other() {
        while (end != 0) {
            a[end].term = a[end].len-a[a[end].suf].len;
            end = a[end].suf;
        }
        a[0].term = 1;
        build_num(0);
    }

    Automaton() {
        end = add_node();
    }

    explicit Automaton(const string& s): Automaton() {
        for (char q : s) {
            add(q);
        }
        build_other();
    }

    int add_node() {
        d.emplace_back(E, -1);
        a.emplace_back();
        return (int)a.size()-1;
    }

    int clone_node(int q) {
        d.push_back(d[q]);
        a.push_back(a[q]);
        return (int)a.size()-1;
    }

    void add(char w) {
        w -= FIRST;
        int vertex = end;
        end = add_node();
        a[end].len = a[vertex].len+1;
        while (vertex != -1 && d[vertex][w] == -1) {
            d[vertex][w] = end;
            vertex = a[vertex].suf;
        }
        int Q = (vertex == -1 ? 0 : d[vertex][w]);
        if (vertex == -1 || a[Q].len == a[vertex].len+1) {
            a[end].suf = Q;
            return;
        }
        int new_Q = clone_node(Q);
        a[new_Q].len = a[vertex].len+1;
        while (vertex != -1 && d[vertex][w] == Q) {
            d[vertex][w] = new_Q;
            vertex = a[vertex].suf;
        }
        a[Q].suf = a[end].suf = new_Q;
    }

    int go(const string& t) const {
        int vertex = 0;
        for (char q : t) {
            q -= FIRST;
            vertex = d[vertex][q];
            if (vertex == -1) {
                return -1;
            }
        }
        return vertex;
    }
};

