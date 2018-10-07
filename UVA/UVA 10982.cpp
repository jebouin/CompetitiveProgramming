/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - This problem is an approximation of the max cut problem where we only need to find a cut with at
 *            least m / 2 edges.
 *          - Add or remove a vertex from the cut as long as it increases the number of edges between the set and
 *            the complementary set.
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

const int N = 111;
vector<int> graph[N];
bool st[N];
int n, m;

int rem(int u) {
    int ans = 0;
    rall(v, graph[u]) {
        ans += st[u] != st[v];
    }
    return ans;
}

void solve(int cas) {
    cin >> n >> m;
    rep(i, 1, n) {
        graph[i].clear();
        st[i] = false;
    }
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    bool ch = true;
    while(ch) {
        ch = false;
        rep(u, 1, n) {
            int prev = rem(u);
            st[u] = !st[u];
            int cur = rem(u);
            if(cur <= prev) {
                st[u] = !st[u];
            } else {
                ch = true;
            }
        }
    }
    vector<int> ans;
    rep(u, 1, n) {
        if(st[u]) {
            ans.pb(u);
        }
    }
    cout << "Case #" << cas << ": ";
    cout << sz(ans) << endl;
    rall(x, ans) {
        cout << x << " ";
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
