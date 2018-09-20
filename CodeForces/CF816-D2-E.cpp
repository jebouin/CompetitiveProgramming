/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The problem can be seen as a rooted tree, where v is a child of u if you must use the u-th coupon
 *            after using the v-th coupon. For any u, if you buy the u-th coupon, you must buy every coupon on
 *            the path from the root to u.
 *          - Calculate the minimum cost to buy j objects in the subtree of i for every i and j. The answer is 
 *            the maximum i for j = 1 that has a cost no greater than b.
 *          - The states can be naively calculated in O(n³). By ordering the children by subtree size, we can
 *            skip the greatest one and the total complexity will be O(n²).
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

const int N = 5555, INF = 1e15;
vector<int> tree[N];
int c[N], d[N], p[N], ft[N], f[N][N], g[N][N], cnt[N];
int n, b;

vector<int> dfs(int u = 1, int p = 0) {
    vector<int> ans(1, c[u]);
    vector<pair<int, int> > children;
    f[u][1] = c[u] - d[u];
    cnt[u] = 1;
    rall(v, tree[u]) {
        if(v != p) {
            vector<int> other = dfs(v, u);
            cnt[u] += cnt[v];
            ans.insert(ans.end(), rng(other));
            children.pb(make_pair(cnt[v], v));
        }
    }
    sort(rng(ans));
    if(sz(children)) {
        sort(rng(children), std::greater<pair<int, int> >());
        int v1 = children[0].se;
        rep(j, 2, n) {
            f[u][j] = c[u] - d[u] + f[v1][j - 1];
        }
        rep(ch, 1, sz(children) - 1) {
            int v = children[ch].se;
            copy(f[u], f[u] + n + 1, ft);
            rep(j, 2, n) {
                rep(k, 1, min(j - 1, cnt[v])) {
                    ft[j] = min(ft[j], f[u][j - k] + f[v][k]);
                }
            }
            copy(ft, ft + n + 1, f[u]);
        }
    }
    rep(j, 1, n) {
        if(j <= sz(ans)) {
            g[u][j] = g[u][j - 1] + ans[j - 1];
        }
        f[u][j] = min(f[u][j], g[u][j]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> b;
    rep(i, 1, n) {
        cin >> c[i] >> d[i];
        if(i > 1) {
            cin >> p[i];
            tree[i].pb(p[i]);
            tree[p[i]].pb(i);
        }
        fill(f[i] + 1, f[i] + n + 1, INF);
        fill(g[i] + 1, g[i] + n + 1, INF);
    }
    dfs();
    int ans = 0;
    rep(j, 1, n) {
        if(f[1][j] <= b) {
            ans = j;
            continue;
        }
    }
    cout << ans << endl;
    return 0;
}
