#include <tr2/dynamic_bitset>
typedef tr2::dynamic_bitset<> Bitset;
Bitset a(3);





#include <bits/extc++.h>
#define int long long
#define ld long double
#define p pair<int, int>
#define endl '\n'
const int INF = (int)1e9+1;

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct my_hash {
    const int seed = chrono::steady_clock::now().time_since_epoch().count();

    static int hash(int x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    int operator()(int x) const {
        return hash(x+seed);
    }
};

gp_hash_table<int, null_type, my_hash> s;

