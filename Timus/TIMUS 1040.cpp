/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - For every positive integer x, gcd(x, x + 1) = 1.
 *          - Use DFS and assign consecutive flight numbers to the airports. If an airport has at least 2 flights
 *            departing from it, its gcd will be one.
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
typedef long long ll;
using namespace std;

const int N = 55, M = 2222;
int from[M], to[M];
int ans[N][N];
vector<int> graph[N];
bool visited[N];
int n, m, k;

void dfs(int u) {
    if(visited[u]) return;
    visited[u] = true;
    rall(v, graph[u]) {
        int x = min(u, v), y = max(u, v);
        if(ans[x][y]) continue;
        ans[x][y] = ++k;
        dfs(v);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    rep(i, 1, m) {
        cin >> from[i] >> to[i];
        if(from[i] > to[i]) swap(from[i], to[i]);
        graph[from[i]].push_back(to[i]);
        graph[to[i]].push_back(from[i]);
    }
    rep(i, 1, n) {
        if(!visited[i]) {
            dfs(i);
        }
    }
    cout << "YES" << endl;
    rep(i, 1, m) {
        cout << ans[from[i]][to[i]] << " ";
    }
    cout << endl;
    return 0;
}
