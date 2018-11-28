/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Iterate over the competitor's edges and add them greedily to our forest of edges until we have a
 *            spanning tree. Use dsu to speed up the process.
 *          - Iterate over the competitor's edges again, each edge (u, v, w) has a corresponding path in the 
 *            spanning tree from u to v. For every owned edge in this path, we can set its price to at most w.
 *            Collapse this path into a single node using dsu and keeping track of the highest node in each set.
 *          - The answer is -1 iff some nodes remained uncollapsed.
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

class DSU {
    public:
        DSU(int n) : dsu(n + 1), rank(n + 1) {
            for(int i = 1; i <= n; i++) {
                dsu[i] = i;
            }
        }

        int find(int u) {
            if(dsu[u] == u) return u;
            dsu[u] = find(dsu[u]);
            return dsu[u];
        }

        bool merge(int u, int v) {
            u = find(u), v = find(v);
            if(u == v) return false;
            if(rank[u] > rank[v]) {
                dsu[v] = u;
            } else {
                dsu[u] = v;
                if(rank[u] == rank[v]) {
                    rank[v]++;
                }
            }
            return true;
        }
    
    private:
        vector<int> dsu, rank;
};

const int N = 555555;
vector<pair<int, bool> > tree[N];
int ga[N], gb[N], fa[N], fb[N], fw[N], par[N], dep[N], add[N];
int dsu2[N], rank2[N], highest[N];
int n, m, k;

void dfs(int u = 1, int p = 0) {
    if(p) {
        par[u] = p;
        dep[u] = dep[p] + 1;
    }
    rall(e, tree[u]) {
        int v = e.fi;
        if(v != p) {
            if(e.se) {
                add[v] = true;
            }
            dfs(v, u);
        }
    }
}

int find(int u) {
    if(dsu2[u] == u) return u;
    dsu2[u] = find(dsu2[u]);
    return dsu2[u];
}

bool merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return false;
    if(rank2[u] > rank2[v]) {
        dsu2[v] = u;
    } else {
        dsu2[u] = v;
        if(rank2[u] == rank2[v]) {
            rank2[v]++;
        }
    }
    int nh = dep[highest[u]] < dep[highest[v]] ? highest[u] : highest[v];
    highest[u] = nh, highest[v] = nh;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d%d%d", &n, &k, &m);
    DSU dsu(n);
    rep(i, 1, k) {
        scanf("%d%d", ga + i, gb + i);
        tree[ga[i]].push_back(make_pair(gb[i], true));
        tree[gb[i]].push_back(make_pair(ga[i], true));
        dsu.merge(ga[i], gb[i]);
    }
    rep(i, 1, m) {
        scanf("%d%d%d", fa + i, fb + i, fw + i);
        if(dsu.merge(fa[i], fb[i])) {
            tree[fa[i]].push_back(make_pair(fb[i], false));
            tree[fb[i]].push_back(make_pair(fa[i], false));
        }
    }
    dfs();
    rep(i, 1, n) {
        dsu2[i] = i;
        highest[i] = i;
    }
    ll ans = 0;
    int cnt = 0;
    rep(i, 1, m) {
        int u = highest[find(fa[i])], v = highest[find(fb[i])];
        while(u != v) {
            if(dep[u] < dep[v]) {
                swap(u, v);
            }
            if(add[u]) {
                ans += fw[i];
                cnt++;
            }
            merge(u, par[u]);
            u = highest[find(u)];
        }
    }
    if(cnt == k) {
        printf(LL, ans);
        printf("\n");
    } else {
        printf("-1\n");
    }
    return 0;
}
