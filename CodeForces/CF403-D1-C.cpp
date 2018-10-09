/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The matrix can be seen as an adjacency matrix of an oriented graph. The value of Aᵏ at (i, j) gives
 *            the number of paths from the vertex i to the vertex j.
 *          - The goal is to find if every vertex is reachable from every other vertex. The answer is yes iff
 *            there is only one strongly connected component.
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

const int N = 2222;
vector<int> graph[N];
vector<vector<int> > sccs;
stack<int> st;
bool inst[N];
int mini[N], ti;
int n;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d", &n);
    rep(i, 1, n) {
        rep(j, 1, n) {
            int x;
            scanf("%d", &x);
            if(x && i != j) {
                graph[i].pb(j);
            }
        }
    }
    rep(i, 1, n) {
        if(!mini[i]) {
            tarjan(i);
        }
    }
    if(sz(sccs) == 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
