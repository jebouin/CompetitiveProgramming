/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - We can check if a cycle of mean x exists in the graph by subtracting x from every weight and
 *            searching for a cycle of negative weight with Bellman-Ford.
 *          - Use binary search on the answer.
 */

#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define rrep(i,a,b) for(int i = (b); i >= (a); i--)
#ifdef LOCAL
#define rall(x,a) for(x : a)
#define LL "%lld"
#else
#define rall(x,a) for(auto x : a)
#define LL "%I64d"
#define y0    oooo
#define y1    ooox
#define yn    ooxo
#define prev  ooxx
#define next  oxoo
#define read  oxox
#define tm    oxxo
#endif
#define rng(a) a.begin(), a.end()
#define PI 3.14159265358979323846
#define MOD 1000000007
//#define endl "\n"
typedef long long ll;
using namespace std;

const int N = 55, INF = 1e9;
vector<pair<int, double> > graph[N];
double wei[N];
int n, m;

bool hasNegativeCycle(double x) {
    fill(wei + 1, wei + n + 1, INF);
    wei[1] = 0;
    bool changed;
    rep(i, 1, n) {
        changed = false;
        rep(u, 1, n) {
            rall(p, graph[u]) {
                int v = p.fi;
                double w = p.se - x;
                if(wei[u] + w < wei[v]) {
                    wei[v] = wei[u] + w;
                    changed = true;
                }
            }
        }
    }
    return changed;
}

void solve(int t) {
    cin >> n >> m;
    rep(i, 1, n) {
        graph[i].clear();
    }
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].pb(make_pair(v, w));
    }
    double l = 0, r = 1e8, ans;
    bool has = false;
    rep(i, 1, 100) {
        ans = (l + r) * .5;
        if(hasNegativeCycle(ans)) {
            has = true;
            r = ans;
        } else {
            l = ans;
        }
    }
    cout << "Case #" << t << ": ";
    if(!has) {
        cout << "No cycle found.";
    } else {
        cout << setprecision(2) << fixed << ans;
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    rep(i, 1, t) {
        solve(i);
    }
    return 0;
}
