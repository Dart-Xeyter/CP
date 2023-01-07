int C = 26, L;

struct Node {
    vector<int> a;
    int suf, len, right, parent;
    char symbol;

    Node(int parent1 = -1, char symbol1 = '#', int len1 = 0, vector<int> a1 = {}) {
        a = (a1.empty() ? vector<int>(C, -1) : a1);
        parent = parent1, symbol = symbol1, len = len1+1, suf = -1, right = 0;
    }
};

vector<Node> trie;
vector<int> last;

int make_moves(int &vertex, char q) {
    if (trie[vertex].a[q-'a'] != -1) {
        return trie[vertex].a[q-'a'];
    }
    int b = trie.size();
    trie.push_back(Node(vertex, q, trie[vertex].len));
    while (vertex != -1 && trie[vertex].a[q-'a'] == -1) {
        trie[vertex].a[q-'a'] = b;
        vertex = trie[vertex].suf;
    }
    trie[b].suf = (vertex == -1 ? 0 : trie[vertex].a[q-'a']);
    return b;
}

int add(int vertex, char q) {
    int b = make_moves(vertex, q);
    if (vertex == -1 || trie[trie[vertex].a[q-'a']].parent == vertex) {
        return b;
    }
    int c = trie[vertex].a[q-'a'], d = trie.size();
    trie.push_back(Node(vertex, q, trie[vertex].len, trie[c].a));
    while (vertex != -1 && trie[vertex].a[q-'a'] == c) {
        trie[vertex].a[q-'a'] = d;
        vertex = trie[vertex].suf;
    }
    trie[d].suf = trie[c].suf, trie[c].suf = trie[b].suf = d;
    return (b == c ? d : b);
}

vector<bool> was;

void build_other(int vertex) {
    was[vertex] = true;
    for (int q = 0; q < C; q++) {
        if (trie[vertex].a[q] == -1) {
            continue;
        }
        if (!was[trie[vertex].a[q]]) {
            build_other(trie[vertex].a[q]);
        }
        trie[vertex].right += trie[trie[vertex].a[q]].right;
    }
}

void build_automation(vector<string> &a) {
    trie = {Node()};
    for (string &s : a) {
        int vertex = 0;
        for (char &q : s) {
            vertex = add(vertex, q);
        }
        last.push_back(vertex);
    }
    L = trie.size();
    for (int q = 0; q < (int)a.size(); q++) {
        int vertex = last[q];
        while (vertex != -1) {
            trie[vertex].right++;
            vertex = trie[vertex].suf;
        }
    }
    was.assign(L, false);
    build_other(0);
}
