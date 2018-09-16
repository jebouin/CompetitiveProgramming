/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Build a graph with edges between every couple of friends, and edges between vertex 2i - 1 and 2i.
 *          - This graph is composed of non-intersecting cycles of even length, we can color it with the 2 colors.
 *          - If we take 3 consecutive vertices, two of them have an edge between them so they are not of the
 *            same color.
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

const int N = 111111;
int a[N], b[N], c[N << 1];
vector<int> graph[N << 1];
int n, nn;

void dfs(int u, int col = 1) {
    if(c[u]) return;
    c[u] = col;
    rall(v, graph[u]) {
        dfs(v, 3 - col);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    nn = n << 1;
    rep(i, 1, n) {
        cin >> a[i] >> b[i];
        graph[a[i]].pb(b[i]);
        graph[b[i]].pb(a[i]);
    }
    rep(i, 1, n) {
        int u = i * 2 - 1, v = i * 2;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    rep(i, 1, nn) {
        if(!c[i]) {
            dfs(i);
        }
    }
    rep(i, 1, n) {
        cout << c[a[i]] << " " << c[b[i]] << endl;
    }
    return 0;
}
