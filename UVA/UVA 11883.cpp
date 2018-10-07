/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Before crossing a road, it is sometimes better to wait to repare it longer. If we arrive to the
 *            city on time t and wait δ units of time, the total time to the next city will be
 *            f(δ) = δ + va^-(t+δ)
 *          - This function is decreasing then increasing, we take its minimum if it doesn't occur before t.
 *          - Iterate over every road, and find the smallest time from city 1 to n by repairing this road.
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
    int dest;
    double w, a;
} E;

const int N = 111;
vector<E> graph[N];
double dist[N];
int n, m;

double bfs(const int& repv, const E& repe) {
    fill(dist + 1, dist + n + 1, 1e9);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while(sz(q)) {
        int u = q.front();
        q.pop();
        rall(e, graph[u]) {
            double w = e.w;
            if(u == repv && e.dest == repe.dest) {
                double t = dist[u];
                double wait = log(e.w * log(e.a)) / log(e.a) - t;
                wait = max(0., wait);
                w = wait + e.w * pow(e.a, -t - wait);
            }
            if(dist[u] + w < dist[e.dest]) {
                dist[e.dest] = dist[u] + w;
                q.push(e.dest);
            }
        }
    }
    return dist[n];
}

void solve() {
    rep(u, 1, n) {
        graph[u].clear();
    }
    rep(i, 1, m) {
        int u, v;
        double w, a;
        cin >> u >> v >> w >> a;
        graph[u].pb({v, w, a});
        graph[v].pb({u, w, a});
    }
    double ans = 1e9;
    rep(u, 1, n) {
        rall(e, graph[u]) {
            ans = min(ans, bfs(u, e));
        }
    }
    cout << setprecision(3) << fixed << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    while(n) {
        solve();
        cin >> n >> m;
    }
    return 0;
}
