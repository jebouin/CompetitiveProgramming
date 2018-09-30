/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Generate a quartic graph by shuffling the list 1 1 1 1 2 2 2 2 ... n n n n and
 *            check the restrictions.
 *          - To make sure we can identify every vertex even when their id are permuted, we need to find
 *            a way to label them based on the link topology.
 *          - A possible labelling for u is a multiset of four values, one for each neighbor v. The value
 *            is the number of neighbors of v that are also neighbors of u. Four values is not enough to
 *            tell the vertices apart so we add to every label u the label of its neighbors. Repeat until the
 *            labels have enough values, 3 times is enough for a graph of size 50.
 *          - To find the permutation, generate the labels of the input graph and compare them to the labels of
 *            the chosen graph.
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

typedef struct Label {
    multiset<Label> st;
    int val;
} Label;

bool operator < (const Label& a, const Label& b) {
    if(a.st.size() < b.st.size()) return true;
    if(b.st.size() < a.st.size()) return false;
    if(a.st.size()) {
        return a.st < b.st;
    }
    return a.val < b.val;
}

bool operator == (const Label& a, const Label& b) {
    return !(a < b) && !(b < a);
}

ostream& operator << (ostream& os, const Label& a) {
    if(sz(a.st)) {
        os << "{";
        for(multiset<Label>::iterator it = a.st.begin(); it != a.st.end(); ++it) {
            os << *it;
            if(++it != a.st.end()) {
                os << ", ";
            }
            --it;
        }
        os << "}";
    } else {
        os << a.val;
    }
    return os;
}

const int N = 55;
set<int> graph[N];
set<pair<int, int> > ed;
Label la[N], la2[N], la3[N];
int ans[N];
bool vis[N];
int n, tries;

void dfs(int u) {
    if(vis[u]) return;
    vis[u] = true;
    rall(v, graph[u]) {
        dfs(v);
    }
}

bool isConnected() {
    fill(vis + 1, vis + n + 1, false);
    int cnt = 0;
    rep(u, 1, n) {
        if(!vis[u]) {
            cnt++;
            dfs(u);
        }
    }
    return cnt == 1;
}

void clearGraph() {
    rep(i, 1, n) {
        graph[i].clear();
        la[i].st.clear();
        la[i].val = 0;
    }
    ed.clear();
}

void generateGraph() {
    tries++;
    bool ok = false;
    while(!ok) {
        ok = true;
        clearGraph();
        vector<int> ep;
        rep(i, 1, n) {
            rep(j, 1, 4) {
                ep.pb(i);
            }
        }
        random_shuffle(rng(ep));
        rep(i, 0, sz(ep) / 2 - 1) {
            int u = ep[i * 2], v = ep[i * 2 + 1];
            if(u == v) {
                ok = false;
                break;
            }
            graph[u].insert(v);
            graph[v].insert(u);
            ed.insert(make_pair(min(u, v), max(u, v)));
        }
        rep(i, 1, n) {
            if(sz(graph[i]) != 4) {
                ok = false;
                break;
            }
        }
        ok &= isConnected();
    }
}

bool generateLabels() {
    rep(u, 1, n) {
        rall(v, graph[u]) {
            int cnt = 0;
            rall(w, graph[v]) {
                if(graph[u].find(w) != graph[u].end()) {
                    cnt++;
                }
            }
            Label l;
            l.val = cnt;
            la[u].st.insert(l);
        }
    }
    bool ok = false;
    rep(i, 1, 3) {
        ok = true;
        rep(u, 1, n) {
            rall(v, graph[u]) {
                la2[u].st.insert(la[v]);
            }
        }
        copy(la2 + 1, la2 + n + 1, la + 1);
        rep(u, 1, n) {
            la2[u].st.clear();
            la2[u].val = 0;
            rep(v, 1, n) {
                if(u != v && la[u] == la[v]) {
                    ok = false;
                    break;
                }
            }
        }
    }
    return ok;
}

void solve() {
    int _;
    cin >> n >> _;
    bool ok = false;
    while(!ok) {
        ok = true;
        generateGraph();
        ok = generateLabels();
    }
    copy(la + 1, la + n + 1, la3 + 1);
    cout << n << endl;
    rall(p, ed) {
        cout << p.fi << " " << p.se << endl;
    }
    cin >> n;
    clearGraph();
    rep(i, 1, 2 * n) {
        int u, v;
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
    }
    generateLabels();
    rep(u, 1, n) {
        rep(v, 1, n) {
            if(la[u] == la3[v]) {
                ans[v] = u;
            }
        }
    }
    rep(i, 1, n) {
        cout << ans[i] << " ";
    }
    cout << endl;
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
