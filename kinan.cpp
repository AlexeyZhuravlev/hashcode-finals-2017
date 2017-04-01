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

const int MAX_N = 1005;
const int DX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

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

bool valid_coords(pii p) {
    return p.fi >= 0 && p.fi < h && p.se >= 0 && p.se < w;
}

void validate() {
    int n = backbone_ans.size();
    int m = router_ans.size();
    set<pii> uniq_b(backbone_ans.begin(), backbone_ans.end());
    set<pii> uniq_r(router_ans.begin(), router_ans.end());
    assert(n == uniq_b.size() && "backbones should be unique");
    assert(m == uniq_r.size() && "routers should be unique");
    assert(uniq_b.find(initial_backbone) == uniq_b.end() && "backbones shouldn't contain initial cell");
    for (auto p : backbone_ans) {
        assert(valid_coords(p) && "backbone coords must be in range");
    }
    for (auto p : router_ans) {
        assert(valid_coords(p) && "router coords must be in range");
    }
    bool backbone[MAX_N][MAX_N] = {false};
    backbone[initial_backbone.fi][initial_backbone.se] = true;
    for (auto p : backbone_ans) {
        int x = p.fi;
        int y = p.se;
        bool good = false;
        for (int d = 0; d < 8; d++) {
            int nx = x + DX[d];
            int ny = y + DY[d];
            if (!valid_coords(mp(nx, ny))) {
                continue;
            }
            if (backbone[nx][ny]) {
                good = true;
                break;
            }
        }
        assert(good && "backbones must be connected");
    }
    int cost = backbone_ans.size() * price_b + router_ans.size() * price_r;
    assert(cost <= budet && "must not exceed budget");
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
