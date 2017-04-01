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

int h, w, r;
int price_b, price_r, budget;
pii initial_backbone;
string layout[MAX_N];

vector<pii> backbone_ans, router_ans;
int sum[MAX_N][MAX_N];

void precalc() {
    forn(i, h)
        forn(j, w)
            sum[i][j] = (layout[i][j] == '#') + (i == 0 ? 0 : sum[i - 1][j])
                    + (j == 0 ? 0 : sum[i][j - 1]) - (i == 0 || j == 0 ? 0 : sum[i - 1][j - 1]);
}

void read_input()
{
    cin >> h >> w >> r;
    cin >> price_b >> price_r >> budget;
    cin >> initial_backbone.fi >> initial_backbone.se;
    for (int i = 0; i < h; i++) {
        cin >> layout[i];
    }
    precalc();
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

bool no_walls(pii corner1, pii corner2) {
    int x_max = max(corner1.fi, corner2.fi);
    int x_min = min(corner1.fi, corner2.fi);
    int y_max = max(corner1.se, corner2.se);
    int y_min = min(corner1.se, corner2.se);
    return sum[x_max][y_max] - (y_min == 0 ? 0 : sum[x_max][y_min - 1])
        - (x_min == 0 ? 0 : sum[x_min - 1][y_max]) + (y_min == 0 || x_min == 0 ? 0 : sum[x_min - 1][y_min - 1]) == 0;
}

vector <pii> get_covered(pii router) {
    vector <pii> result;
    fore(x, max(router.fi - r, 0), min(router.fi + r, h - 1))
        fore(y, max(router.se - r, 0), min(router.se + r, w - 1)) {
            if (layout[x][y] == '.' && no_walls(mp(x, y), router))
                result.pb(mp(x, y));
        }
    return result;
}

vector <pii> get_all_covered(const vector <pii> & routers) {
    vector <vector<bool> > covered(h);
    forn(j, w)
        covered[j].resize(w);
    for (pii router : routers) {
        auto newly_covered = get_covered(router);
        for (pii cell : newly_covered)
            covered[cell.fi][cell.se] = true;
    }
    vector <pii> result;
    forn(i, h)
        forn(j, w)
            if (covered[i][j])
                result.pb(mp(i, j));
    return result;
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
