vector<vector<int>> trie;
vector<int> parent, cost;
int C = 26;

int add(string &s, int x) {
    int vertex = 0;
    for (char q : s) {
        if (trie[vertex][q-'a'] == -1) {
            trie[vertex][q-'a'] = trie.size();
            trie.push_back(vector<int>(C, -1));
            parent.push_back(vertex);
            cost.push_back(0);
        }
        vertex = trie[vertex][q-'a'];
    }
    cost[vertex] += x;
    return vertex;
}
