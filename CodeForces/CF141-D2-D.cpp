/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Treat a ramp (x, d, t, p) as a ramp from x - p to x + d that takes t + p seconds.
 *          - Compress the coordinates and use Dijsktra to find the shortest path.
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
#define endl "\n"
typedef long long ll;
using namespace std;

typedef struct E {
    int v, w, r;
} E;

const int N = 111111;
set<int> cst;
map<int, int> ctn;
pair<pair<int, int>, int> ramps[N];
vector<E> graph[N << 1];
int dist[N << 1];
set<pair<int, int> > q;
pair<int, int> pr[N << 1];
int n, nn, l;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d %d", &n, &l);
    rep(i, 1, n) {
        int x, d, t, p;
        scanf("%d %d %d %d", &x, &d, &t, &p);
        int s = x - p;
        if(s < 0) continue;
        d += p;
        int e = s + d;
        t += p;
        ramps[i] = make_pair(make_pair(s, e), t);
        cst.insert(s);
        cst.insert(e);
    }
    cst.insert(0);
    cst.insert(l);
    int p = -1;
    rall(x, cst) {
        ctn[x] = ++nn;
        if(p >= 0) {
            int d = x - p;
            int u = ctn[p], v = ctn[x];
            graph[u].pb({v, d, 0});
            graph[v].pb({u, d, 0});
        }
        p = x;
    }
    rep(i, 1, n) {
        int x = ramps[i].fi.fi;
        if(x < 0) continue;
        int u = ctn[ramps[i].fi.fi], v = ctn[ramps[i].fi.se], w = ramps[i].se;
        graph[u].pb({v, w, i});
    }
    fill(dist, dist + nn + 1, 2e9);
    dist[1] = 0;
    q.insert(make_pair(0, 1));
    while(sz(q)) {
        pair<int, int> p = *(q.begin());
        q.erase(q.begin());
        int u = p.se;
        rall(e, graph[u]) {
            int nd = dist[u] + e.w;
            if(dist[e.v] > nd) {
                pr[e.v] = make_pair(u, e.r);
                dist[e.v] = nd;
                q.insert(make_pair(dist[e.v], e.v));
            }
        }
    }
    vector<int> ans;
    int u = nn;
    while(u != 1) {
        pair<int, int> p = pr[u];
        u = p.fi;
        if(p.se) {
            ans.pb(p.se);
        }
    }
    reverse(rng(ans));
    printf("%d\n", dist[nn]);
    printf("%d\n", sz(ans));
    rall(x, ans) {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}
