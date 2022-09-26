unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 randint(seed);

void gen() {
    ofstream out("test.txt");
}

void debug() {
    int q2 = 0;
    while (true) {
        cout << q2++ << endl;
        gen();
        system("easy.exe < test.txt > easy.txt");
        system("hard.exe < test.txt > hard.txt");
        ifstream in_easy("easy.txt");
        ifstream in_hard("hard.txt");
        char w;
        vector<char> easy, hard;
        while (in_easy >> w) {
            easy.push_back(w);
        }
        while (in_hard >> w) {
            hard.push_back(w);
        }
        if (easy != hard) {
            exit(179);
        }
    }
}
