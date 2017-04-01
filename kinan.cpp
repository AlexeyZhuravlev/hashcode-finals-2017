#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>
#include <cassert>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define i64 long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const int MAX_N = 10005;

int h, w, r;
int price_b, price_r, budget;
pii initial_backbone;
string layout[MAX_N];

vector<pii> backbone_ans, router_ans;

void read_input()
{
    cin >> h >> w >> r;
    cin >> price_b >> price_r >> budget;
    cin >> initial_backbone.fi >> initial_backbone.se;
    for (int i = 0; i < h; i++) {
        cin >> layout[i];
    }
}

void validate() {
    int n = backbone_ans.size();
    int m = router_ans.size();
    set<pii> uniq_b(backbone_ans.begin(), backbone_ans.end());
    set<pii> uniq_r(router_ans.begin(), router_ans.end());
    assert(n == uniq_b.size() && "backbones should be unique");
    assert(m == uniq_r.size() && "routers should be unique");
    for (auto p : backbone_ans) {
        assert(p.fi >= 0 && p.fi < h && "backbones coords must be in range");
        assert(p.se >= 0 && p.se < w && "backbones coords must be in range");
    }
    for (auto p : router_ans) {
        assert(p.fi >= 0 && p.fi < h && "router coords must be in range");
        assert(p.se >= 0 && p.se < w && "router coords must be in range");
    }
}

void write_result()
{
    cout << c;
}

void solve()
{
    c = a + b;
}

double calc_result()
{
    return a + b;
}

int main(int argc, const char * argv[]) {
    // this is my comment
    if( argc < 2 ) {
        cout << "Specify filename";
        return -1;
    }
    string name = argv[1];
    
    freopen( (name + ".in").c_str(), "r", stdin );
    freopen( (name + ".out").c_str(), "w", stdout );
    
    read_input();
    solve();
    double result = calc_result();
    write_result();
    
    cerr << result << std::endl;
    
    return 0;
}
