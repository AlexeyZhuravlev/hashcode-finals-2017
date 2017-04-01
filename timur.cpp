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

const int inf = (int)1e9; //add this
bool used[(int)1e6]; //add this
int d[(int)1e6]; //add this
int p[(int)1e6]; //add this
const int MAX_ADDITIONAL_ROUTERS = 100;

int h, w, r;
int price_b, price_r, budget;
pii initial_backbone;
string layout[MAX_N];

vector<pii> backbone_ans, router_ans;

int get_dist(const pii &a, const pii &b) { //add this
    return max(abs(a.fi - b.fi), abs(a.se - b.se));
}

void build_dist(pii a, const pii &b) {
    int x = abs(a.fi - b.fi);
    int y = abs(a.se - b.se);
    while (x != y) {
        if (x > y) {
            a.fi += (b.fi - a.fi) / x--;
        } else {
            a.se += (b.se - a.se) / y--;
        }
        backbone_ans.push_back(a);
    }
    while (x != 0) {
        a.fi += (b.fi - a.fi) / x;
        a.se += (b.se - a.se) / x;
        backbone_ans.push_back(a);
        x--;
    }
}

int get_tree_size(const vector<pii> &additional, int mx, bool build = false) { //add this
    int n = (int)router_ans.size() + (int)additional.size();
    int ans = 0;
    memset(d, 0x3f, n * sizeof(int));
    memset(used, 0, n * sizeof(bool));
    d[router_ans.size()-1] = 0;
    for(int i = 0; i < n; i++) {
        int mn = inf;
        int mni = -1;
        for(int j = 0; j < n; j++) {
            if (!used[j] && d[j] < mn) {
                mni = j;
                mn = d[j];
            }
        }
        ans += d[mni];
        if (ans >= mx) {
            return ans;
        }
        used[mni] = true;
        pii mnpoint;
        if (mni < (int)router_ans.size()) {
            mnpoint = router_ans[mni];
        } else {
            mnpoint = additional[mni - router_ans.size()];
        }
        
        if (build) {
            pii last;
            if (p[mni] < (int)router_ans.size()) {
                last = router_ans[p[mni]];
            } else {
                last = additional[p[mni] - router_ans.size()];
            }
            build_dist(last, mnpoint);
        }
        
        
        for(int j = 0; j < (int)router_ans.size(); j++) {
            if (!used[j] && d[j+router_ans.size()] > get_dist(mnpoint, router_ans[j])) {
                d[j] = get_dist(mnpoint, router_ans[j]);
                p[j] = mni;
            }
        }
        for(int j = 0; j < (int)additional.size(); j++) {
            if (!used[j+router_ans.size()] && d[j+router_ans.size()] > get_dist(mnpoint, additional[j])) {
                d[j+router_ans.size()] = get_dist(mnpoint, additional[j]);
                p[j+router_ans.size()] = mni;
            }
        }
    }
    return ans;
}

void build_backbones() { //add this
    router_ans.push_back(initial_backbone);
    
    vector<pii> additional;
    int cur_ans = get_tree_size(additional, inf);
    backbone_ans.clear();
    cerr << "0. Current backbones price = " <<cur_ans << endl;
    
    bool update = true;
    for(int k = 0; k < MAX_ADDITIONAL_ROUTERS && update; k++) {
        update = false;
        int mxi, mxj;
        additional.push_back(mp(0, 0));
        forn(i, h) {
            forn(j, w) {
                additional[k] = mp(i, j);
                int cur = get_tree_size(additional, cur_ans);
                if (cur_ans > cur) {
                    update = true;
                    mxi = i;
                    mxj = j;
                    cur_ans = cur;
                }
            }
        }
        additional[k] = mp(mxi, mxj);
        cerr << k+1 << ". Current backbones price = " << cur_ans << endl;
        if (!update) {
            cerr << "Break" << endl;
        }
    }
    
    get_tree_size(additional, inf, true);
    router_ans.pop_back();
}

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
    int n = (int)backbone_ans.size();
    int m = (int)router_ans.size();
    set<pii> uniq_b(backbone_ans.begin(), backbone_ans.end());
    set<pii> uniq_r(router_ans.begin(), router_ans.end());
    assert(n == (int)uniq_b.size() && "backbones should be unique");
    assert(m == (int)uniq_r.size() && "routers should be unique");
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
}

void solve()
{
}

double calc_result()
{
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
