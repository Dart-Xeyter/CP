vector<int> Euler;
vector<set<int>> copy_d;

void make_bypass(int vertex) {
    while (!copy_d[vertex].empty()) {
        int q = *copy_d[vertex].begin();
        copy_d[vertex].erase(q);
        copy_d[q].erase(vertex);
        make_bypass(q);
    }
    Euler.push_back(vertex);
}
