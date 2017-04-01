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

const int inf = (int)1e9; //add this
bool used[(int)1e6]; //add this
int d[(int)1e6]; //add this
int p[(int)1e6]; //add this
const int MAX_ADDITIONAL_ROUTERS = 100;

const int MAX_N = 1005;
const int DX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int h, w, r;
int price_b, price_r, budget;
pii initial_backbone;
string layout[MAX_N];

int dist_to_backbone[MAX_N][MAX_N];

bool backbone_map[MAX_N][MAX_N]; // DIMA

vector<pii> backbone_ans, router_ans;

int sum[MAX_N][MAX_N];





// -------------- FORWARD DECLARATIONS ------------------
int calc_cost();
vector <pii> get_all_covered(const vector <pii> & routers);
void build_backbones(bool optimize);
bool val_coor(int x, int y);
// ----------------------------------------------




void calc_all_dist() {
    queue <pii> Q;
    forn(i, h)
        forn(j, w)
            if (backbone_map[i][j]) {
                Q.push(mp(i, j));
                dist_to_backbone[i][j] = 0;
            } else dist_to_backbone[i][j] = inf;
    while(!Q.empty()) {
        pii cur = Q.front();
        Q.pop();
        forn(move, 8) {
            int x = cur.fi + DX[move];
            int y = cur.se + DY[move];
            if (!val_coor(x, y) || dist_to_backbone[x][y] != inf)
                continue;
            dist_to_backbone[x][y] = dist_to_backbone[cur.fi][cur.se] + 1;
            Q.push(mp(x, y));
        }
    }
}



void recalc_dist() {
    build_backbones(false);
    calc_all_dist();
}



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
    recalc_dist();
}

bool valid_coords(pii p) {
    return p.fi >= 0 && p.fi < h && p.se >= 0 && p.se < w;
}

void validate() {
    int n = (int)backbone_ans.size();
    int m = (int)router_ans.size();
    set<pii> uniq_b(backbone_ans.begin(), backbone_ans.end());
    set<pii> uniq_r(router_ans.begin(), router_ans.end());
    assert(n == (int)uniq_b.size() && "backbones should be unique");
    assert(m == (int)uniq_r.size() && "routers should be unique");
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
        backbone[x][y] = true;
        assert(good && "backbones must be connected");
    }
    assert(calc_cost() <= budget && "must not exceed budget");
}


bool val_coor( int r, int c ) {
    return r >= 0 && r < h && c >= 0 && c < w;
}

int calc_cost() {
    return (int)backbone_ans.size() * price_b + (int)router_ans.size() * price_r;
}

int calc_result()
{
    return 1000 * (int)get_all_covered(router_ans).size() + (budget - calc_cost());
}

void print_vpii(const vector<pii>& v) {
    cout << v.size() << endl;
    for (const auto& p : v) {
        cout << p.fi << " " << p.se << endl;
    }
}

void write_result()
{
    print_vpii(backbone_ans);
    print_vpii(router_ans);
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
    forn(j, h)
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


void place_router(vector <vector<bool> > & covered, pii router) {
    auto newly_covered = get_covered(router);
    for (pii cell : newly_covered)
        covered[cell.fi][cell.se] = true;
    recalc_dist();
}


int get_dist(const pii &a, const pii &b) { //add this
    return max(abs(a.fi - b.fi), abs(a.se - b.se));
}

void build_dist(pii a, const pii &b) { // DIMA
    int x = abs(a.fi - b.fi);
    int y = abs(a.se - b.se);
    while (x != y) {
        if (x > y) {
            a.fi += (b.fi - a.fi) / x--;
        } else {
            a.se += (b.se - a.se) / y--;
        }
        if (!backbone_map[a.fi][a.se]) {
            backbone_ans.push_back(a);
            backbone_map[a.fi][a.se] = true;
        }
    }
    while (x != 0) {
        a.fi += (b.fi - a.fi) / x;
        a.se += (b.se - a.se) / x;
        if (!backbone_map[a.fi][a.se]) {
            backbone_ans.push_back(a);
            backbone_map[a.fi][a.se] = true;
        }
        x--;
    }
}



int get_tree_size(const vector<pii> &additional, int mx, bool build = false) { // HERE YOBA
    if (build) {
        backbone_ans.clear();
        memset(backbone_map, 0, sizeof(backbone_map));
    }
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
        
        if (build && i > 0) {
            pii last;
            if (p[mni] < (int)router_ans.size()) {
                last = router_ans[p[mni]];
            } else {
                last = additional[p[mni] - router_ans.size()];
            }
            build_dist(last, mnpoint);
        }
        
        
        for(int j = 0; j < (int)router_ans.size(); j++) {
            if (!used[j] && d[j] > get_dist(mnpoint, router_ans[j])) {
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




void build_backbones(bool optimize = false) { // HERE YOBA
    router_ans.push_back(initial_backbone);
    
    vector<pii> additional;
    int cur_ans = get_tree_size(additional, inf);
    
    if (optimize) {
        priority_queue<pair<int, pii> > potentional;
        
        additional.push_back(mp(0, 0));
        forn(i, h) {
            if (i > 0 && (i+1) % 10 == 0) {
                cerr << i+1 << "/" << h << " rows done" << endl;
            }
            forn(j, w) {
                additional[0] = mp(i, j);
                int cur = get_tree_size(additional, cur_ans);
                if (cur_ans > cur) {
                    potentional.push({cur, {i, j}});
                }
            }
        }
        additional.pop_back();
        
        
        for(int k = 0; k < MAX_ADDITIONAL_ROUTERS && additional.size() > 0;) {
            additional.push_back(potentional.top().se);
            potentional.pop();
            int cur = get_tree_size(additional, cur_ans);
            if (cur_ans > cur) {
                cur_ans = cur;
                k++;
            } else {
                additional.pop_back();
            }
        }
    }
    get_tree_size(additional, inf, true);
    router_ans.pop_back();
}
vector <pii> get_covered(pii router, const vector <vector<bool> >& covered ) {
    vector <pii> result;
    fore(x, max(router.fi - r, 0), min(router.fi + r, h - 1))
    fore(y, max(router.se - r, 0), min(router.se + r, w - 1)) {
        if (layout[x][y] == '.' && no_walls(mp(x, y), router) && !covered[x][y])
            result.pb(mp(x, y));
    }
    return result;
}

double calc_pot(int covered, int dist) {
    return covered * log(1 + dist);
}


double calc_poten( pii place, const vector<vector<bool> >& covered )
{
    int covered1 = get_covered( place, covered ).size();
    int backbone_dist = dist_to_backbone[place.fi][place.se];
    return -calc_pot( covered1, backbone_dist );
}

int get_cur_budget() {
    return price_r * router_ans.size() + price_b * backbone_ans.size(); 
}

void solve()
{
    vector<vector<bool>> covered(h);
    vector<vector<double>> pots_v(h);
    forn(i, h) {
        covered[i].resize(w);
        pots_v[i].resize(w);
    }
    
    set< pair< double, pii> > pots;
    for( int i = 0; i < h; i++ ) {
        for ( int j = 0; j < w; j++ ) {
            if( layout[i][j] != '#' ) {
                double cost = calc_poten( make_pair(i,j), covered );
                pots.insert( make_pair( cost, make_pair( i, j) ) );
                pots_v[i][j] = cost;
            }
        }
    }
    
    while(get_cur_budget() < budget - 2 * price_r ) {
        pair<double, pii> best = *pots.begin();
        pots.erase( pots.begin() );
        pii coors = best.second;
        
        if( abs(best.first - pots_v[coors.first][coors.second] ) > 1e-9 ) {
            continue;
        }
        
        place_router( covered, coors );
        // cerr << "Current poten: " << poten << endl;
        router_ans.push_back( coors );
        
        for( int dx = -r; dx <= r; dx++) {
            for( int dy = -r; dy <= r; dy++ ) {
                pii coor = make_pair( coors.first + dx, coors.second + dy );
                if( !val_coor( coor.first, coor.second ) ) {
                    continue;
                }
                double cost = calc_poten( coor, covered );
                pots.insert( make_pair(cost, coor ) );
                pots_v[coor.first][coor.second] = cost;
            }
        }
    }
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
    cerr << h << " " << w << endl;
    /*
     cerr <<router_ans.size() << endl;
     for (pii router : router_ans)
     fprintf(stderr, "router %d %d\n", router.fi, router.se);
     */
    build_backbones(true);
    write_result();
    validate();
    int result = calc_result();
    
    cerr << result << std::endl;
    
    return 0;
}
