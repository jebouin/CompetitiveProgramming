/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let x_i = true if the ith wife is on the bride's side of the table.
 *          - For an adulterous pair (iw, jw), both wives can't be on the same side of the table so we have
 *            not(x_i) => x_j and 3 similar cases with the other type of pairs.
 *          - Use 2-sat and be sure to add the condition x_0 = true.
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
int n, m, k;
set<int> graph[N];
vector<vector<int> > sccs;
stack<int> st;
bool inst[N], ok;
int mini[N], comp[N], ans[N], ti;

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
        k++;
        while(1) {
            int x = st.top();
            st.pop();
            inst[x] = false;
            comp[x] = k;
            if(comp[x] == comp[x ^ 1]) {
                ok = false;
            }
            scc.pb(x);
            if(x == u) {
                break;
            }
        }
        sccs.pb(scc);
    }
    return mini[u];
}

void solve() {
    rep(i, 0, 2 * n - 1) {
        graph[i].clear();
    }
    sccs.clear();
    fill(mini, mini + 2 * n, 0);
    fill(comp, comp + 2 * n + 1, 0);
    fill(inst, inst + 2 * n + 1, false);
    fill(ans, ans + 2 * n, -1);
    k = 0;
    ti = 0;
    ok = true;
    rep(i, 1, m) {
        int u, v;
        char uc, vc;
        scanf("%d%c %d%c", &u, &uc, &v, &vc);
        u <<= 1, v <<= 1;
        if(uc == 'h') {
            u++;
        }
        if(vc == 'w') {
            v++;
        }
        graph[u].insert(v);
        graph[v ^ 1].insert(u ^ 1);
    }
    graph[0].insert(1);
    rep(u, 0, 2 * n - 1) {
        if(!mini[u]) {
            tarjan(u);
            if(!ok) {
                printf("bad luck\n");
                return;
            }
        }
    }
    rall(scc, sccs) {
        rall(u, scc) {
            if(ans[u] == -1) {
                ans[u] = true;
                ans[u ^ 1] = false;
            }
        }
    }
    rep(i, 1, n - 1) {
        printf("%d%c ", i, ans[i * 2 + 1] ? 'w' : 'h');
    }
    printf("\n");
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d %d", &n, &m);
    while(n) {
        solve();
        scanf("%d %d", &n, &m);
    }
    return 0;
}
