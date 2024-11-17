unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 randint(seed);

int rand_int(int l, int r) {
    int x = randint() % (r-l+1);
    return x+l;
}

string rand_string(int n, int C) {
    string s;
    for (int q = 0; q < n; q++) {
        char w = 'a'+randint() % C;
        s += w;
    }
    return s;
}

void gen(int n, int C) {
    ofstream out("../stress/test.txt");
    out << n << endl;
    //to do
}

void debug() {
    int q2 = 0, w;
    while (true) {
        cout << q2++ << endl;
        int n = rand_int(1, 100), k = rand_int(1, 10);
        gen(n, k);
        int code1 = system("./easy < ../stress/test.txt > ../stress/easy.txt");
        int code2 = system("./hard < ../stress/test.txt > ../stress/hard.txt");
        if (code1 != 0 || code2 != 0) {
            exit(57);
        }
        ifstream in1("../stress/easy.txt");
        ifstream in2("../stress/hard.txt");
        vector<int> ans1, ans2;
        while (in1 >> w) {
            ans1.push_back(w);
        }
        while (in2 >> w) {
            ans2.push_back(w);
        }
        if (ans1 != ans2) {
            exit(179);
        }
    }
}

