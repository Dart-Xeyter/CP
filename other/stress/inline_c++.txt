vector<int> easy() {

}

vector<int> hard() {

}

mt19937 randint(179);

vector<int> gen(int n, int m) {

}

void debug() {
    int q2 = 0;
    while (true) {
        cout << q2++ << endl;
        int n = randint() % 10+1, m = randint() % 10+1;
        auto test = gen(n, m);
        auto ans1 = easy(test), ans2 = hard(test);
        if (ans1 != ans2) {
            cout << endl << endl << endl;
            cout << n << ' ' << m << endl;
            for (int q : test) {
                cout << q << ' ';
            }
            cout << endl;
            exit(179);
        }
    }
}

void solve() {

}
