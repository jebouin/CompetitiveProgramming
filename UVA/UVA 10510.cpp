/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Count the number of strongly connected components, the answer is NO if there is more than one.
 *          - Classify the edges into tree, forward, cross and back edges.
 *          - If there is at least one forward or cross edge, the answer is NO.
 *          - If there are at least two back edges from any node, the answer is NO.
 *          - Else, the answer is YES.
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
#define end   oxxx
#define start xooo
#define forward basdjladfh
#endif
#define rng(a) a.begin(), a.end()
#define PI 3.14159265358979323846
#define MOD 1000000007
#define endl "\n"
typedef long long ll;
using namespace std;


const int N = 11111;
vector<int> graph[N];
set<int> graph2[N];
vector<vector<int> > sccs;
stack<int> st;
set<pair<int, int> > forward, cross, tree, back;
bool inst[N];
int mini[N], ti, start[N], end[N], par[N];
int nb[N];
int n, m;

int tarjan(int u) {
    int cur = ++ti;
    st.push(u);
    inst[u] = true;
    mini[u] = cur;
    rall(v, graph[u]) {
        if(!mini[v]) {
            mini[u] = min(mini[u], tarjan(v));
        } else if(inst[v]) {
            mini[u] = min(mini[u], mini[v]);
        }
    }
    if(mini[u] == cur) {
        vector<int> scc;
        while(1) {
            int x = st.top();
            st.pop();
            inst[x] = false;
            scc.pb(x);
            if(x == u) {
                break;
            }
        }
        sccs.pb(scc);
    }
    return mini[u];
}

void dfs(int u, int p = 0) {
    par[u] = p;
    start[u] = ++ti;
    rall(v, graph[u]) {
        if(!start[v]) {
            dfs(v, u);
        }
    }
    end[u] = ++ti;
}

void solve() {
    cin >> n >> m;
    fill(mini + 1, mini + n + 1, 0);
    fill(start + 1, start + n + 1, 0);
    fill(end + 1, end + n + 1, 0);
    fill(nb + 1, nb + n + 1, 0);
    ti = 0;
    sccs.clear();
    forward.clear();
    cross.clear();
    tree.clear();
    back.clear();
    rep(i, 1, n) {
        graph[i].clear();
    }
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        u++; v++;
        graph[u].pb(v);
    }
    rep(u, 1, n) {
        if(!mini[u]) {
            tarjan(u);
        }
    }
    if(sz(sccs) > 1) {
        cout << "NO" << endl;
        return;
    }
    ti = 0;
    dfs(1);
    rep(u, 1, n) {
        rall(v, graph[u]) {
            pair<int, int> ed(u, v);
            if(par[v] == u) {
                tree.insert(ed);
            } else if(start[u] < start[v] && end[u] > end[v]) {
                forward.insert(ed);
            } else if(start[u] > start[v] && end[u] < end[v]) {
                back.insert(ed);
                nb[u]++;
            } else {
                cross.insert(ed);
            }
        }
    }
    bool ok = true;
    if(sz(forward) || sz(cross)) {
        ok = false;
    }
    rep(u, 1, n) {
        if(nb[u] > 1) {
            ok = false;
        }
    }
    cout << (ok ? "YES" : "NO") << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
