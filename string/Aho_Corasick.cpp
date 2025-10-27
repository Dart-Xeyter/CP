const int E = 26;
const char FIRST = 'a';
vector<vector<int>> d = {vector<int>(E, -1)};
vector<int> term = {0};

int go_create(int vertex, char w) {
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
        vertex = go_create(vertex, q);
    }
    term[vertex]++;
    return vertex;
}

vector<vector<int>> go;
vector<int> suf;

int step(int vertex, int q) {
    if (vertex == -1) {
        return 0;
    }
    int x = d[vertex][q], par = suf[vertex];
    int y = (par == -1 ? 0 : go[par][q]);
    return x == -1 ? y : x;
}

void build_suflinks() {
    int m = (int)d.size();
    go = d, suf.assign(m, -1);
    queue<int> a;
    a.push(0);
    while (!a.empty()) {
        int x = a.front();
        a.pop();
        int num = (suf[x] == -1 ? 0 : term[suf[x]]);
        term[x] += num;
        for (int q = 0; q < E; q++) {
            go[x][q] = step(x, q);
            if (d[x][q] != -1) {
                suf[d[x][q]] = step(suf[x], q);
                a.push(d[x][q]);
            }
        }
    }
}

