const int E = 26;
vector<vector<int>> d = {vector<int>(E, -1)};
vector<int> term = {0}, suflink, num_term;
const char FIRST = 'a';

int add_symbol(int vertex, char w) {
    w -= FIRST;
    if (d[vertex][w] == -1) {
        d[vertex][w] = (int)d.size();
        d.emplace_back(E, -1);
        term.push_back(0);
    }
    return d[vertex][w];
}

int add_string(const string& s) {
    int vertex = 0;
    for (char q : s) {
        vertex = add_symbol(vertex, q);
    }
    term[vertex]++;
    return vertex;
}

int build_suflink(int vertex, int q) {
    int q1 = suflink[vertex];
    while (q1 != -1 && d[q1][q] == -1) {
        q1 = suflink[q1];
    }
    return q1 == -1 ? 0 : d[q1][q];
}

void make_suflinks() {
    suflink.assign(d.size(), -1), num_term.assign(d.size(), 0);
    queue<int> a;
    a.push(0);
    num_term[0] = term[0];
    while (!a.empty()) {
        int vertex = a.front();
        a.pop();
        for (int q_ = 0; q_ < E; q_++) {
            int q = d[vertex][q_];
            if (q != -1) {
                suflink[q] = build_suflink(vertex, q_);
                num_term[q] = term[q]+num_term[suflink[q]];
                a.push(q);
            }
        }
    }
}

