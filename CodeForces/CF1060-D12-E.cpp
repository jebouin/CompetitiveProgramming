/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The goal is to find the sum of ⌈l / 2⌉ for every path of length l.
 *          - For a path of length l, we add (l + f(l)) / 2 where f(l) = 0 if l is even and f(l) = 1 if
 *            l is odd.
 *          - Compute the sum of l and the sum of f(l) separately. The first one is a classical problem. The sum
 *            of f(l) is equal to the number of nodes that have an even distance from the root, times the number
 *            of nodes that have an odd distance from the root.
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
#define int long long
typedef long long ll;
using namespace std;

const int N = 222222;
vector<int> tree[N];
int cnt[N], n, odd;

void dfs(int u = 1, int p = 0, int dep = 0) {
    odd += dep & 1;
    cnt[u] = 1;
    rall(v, tree[u]) {
        if(v != p) {
            dfs(v, u, dep + 1);
            cnt[u] += cnt[v];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        tree[u].pb(v);
        tree[v].pb(u);
    }
    dfs();
    int ans = 0;
    rep(u, 1, n) {
        ans += cnt[u] * (n - cnt[u]);
    }
    ans += odd * (n - odd);
    ans >>= 1;
    cout << ans << endl;
    return 0;
}
