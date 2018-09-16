/*  Author: Jeremy Bouin
 *
 *  Idea:   
 *          - Build a starlike tree where the center vertex has the greatest value and the leaves have values that
 *            appear in the input.
 *          - For each remaining value x, try to assign it to a vertex between the center and a leaf that has the 
 *            smallest value greater than x.
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

const int N = 1111;

typedef struct V {
    int maxi = N, val = 0;
} V;

int pa[N][N];
V vs[N];
vector<int> tree[N];
int ord[N];
int n, mx;

bool comp(const int& i, const int& j) {
    return vs[i].maxi < vs[j].maxi;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    set<int> need;
    rep(i, 1, n) {
        need.insert(i);
        ord[i] = i;
    }
    rep(i, 2, n) {
        int x, y;
        cin >> x >> y;
        if(x < y) swap(x, y);
        pa[x][y]++;
        mx = max(mx, x);
    }
    vs[1].val = mx;
    vs[1].maxi = 0;
    int cn = 1;
    need.erase(mx);
    rep(x, 1, n) {
        rep(y, 1, x - 1) {
            if(pa[x][y]) {
                if(x != mx) {
                    cout << "NO" << endl;
                    return 0;
                }
                int len = pa[x][y];
                int v = 1;
                rep(i, 1, len) {
                    int u = cn + i;
                    tree[u].pb(v);
                    tree[v].pb(u);
                    vs[u].maxi = y - 1;
                    v = u;
                }
                vs[cn + len].val = y;
                vs[cn + len].maxi = 0;
                cn += len;
                need.erase(y);
            }
        }
    }
    sort(ord + 1, ord + n + 1, comp);
    int i = 1;
    rall(x, need) {
        while(i <= n && vs[ord[i]].maxi < x) {
            i++;
        }
        if(i > n) {
            cout << "NO" << endl;
            return 0;
        }
        vs[ord[i]].val = x;
        i++;
    }
    cout << "YES" << endl;
    rep(u, 1, n) {
        rall(v, tree[u]) {
            if(u < v) {
                cout << vs[u].val << " " << vs[v].val << endl;
            }
        }
    }
    return 0;
}
