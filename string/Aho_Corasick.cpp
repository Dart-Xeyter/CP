int C = 26;
vector<vector<int>> d, term;
vector<int> suf_link, num_term, term_link;

void make_trie(vector<string> &a) {
    int n = a.size();
    d = {vector<int>(C, 1), vector<int>(C, -1)}, term = {{}, {}};
    for (int q = 0; q < n; q++) {
        string s = a[q];
        int vertex = 1;
        for (char q2 : s) {
            if (d[vertex][q2-'a'] == -1) {
                d[vertex][q2-'a'] = d.size();
                d.push_back(vector<int>(C, -1));
                term.emplace_back();
            }
            vertex = d[vertex][q2-'a'];
        }
        term[vertex].push_back(q);
    }
}

void Aho_Corasick() {
    int n = d.size();
    suf_link.assign(n, -1), num_term.assign(n, -1), term_link.assign(n, -1);
    suf_link[0] = suf_link[1] = 0, num_term[0] = 0;
    queue<int> a;
    a.push(1);
    while (!a.empty()) {
        int x = a.front();
        a.pop();
        for (int q = 0; q < C; q++) {
            if (d[x][q] != -1) {
                int q1 = suf_link[x];
                while (d[q1][q] == -1) {
                    q1 = suf_link[q1];
                }
                suf_link[d[x][q]] = d[q1][q];
                a.push(d[x][q]);
            }
        }
        if (!term[suf_link[x]].empty()) {
            term_link[x] = suf_link[x];
        } else {
            term_link[x] = term_link[suf_link[x]];
        }
        num_term[x] = num_term[suf_link[x]]+term[x].size();
    }
}

