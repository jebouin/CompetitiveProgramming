/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The number of divisors of a number is the product of eᵢ+ 1 for every exponent eᵢ in its prime
 *            factorization.
 *          - The order of the exponents doesn't matter so we can store them in a vector in decresing order.
 *          - There are 289 vectors that correspond to numbers not greater than 1e6. However, we need to
 *            consider more than that since a number can be greater than 1e6 after an operation. Consider the
 *            case a = 3^12 and b = 2 * 3^6, the optimal solution is to change a to 3^13 > 1e6.
 *          - For every of the 289 starting vectors, run a bfs to compute the distance to any other vector.
 *            Keep track of the minimum number of operations to obtain a number with k divisors from the
 *            starting vector u (cnt[u][k] here), for every k encountered in the bfs. 
 *          - For every input (a, b), the answer will be min(cnt[u][k] + cnt[v][k]) where u and v are the nodes
 *            that correspond to the sorted exponent vectors of a and b.
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

const int X = 1000000, N = 33333, S = 333;
bool isp[X], pi[X];
int ndiv[N];
int dist[S][N], cnt[S][N];
int q[N], qs, qe;
set<int> graph[N];
vector<int> primes;
map<vector<int>, int> toNode;
int xtn[X + 1];

vector<int> getPow(int x) {
    if(isp[x]) {
        return vector<int>(1, 1);
    }
    vector<int> ans;
    rep(i, 0, sz(primes) - 1) {
        if(x % primes[i] == 0) {
            int p = 0;
            while(x % primes[i] == 0) {
                x /= primes[i];
                p++;
            }
            ans.pb(p);
        }
        if(x == 1) break;
    }
    sort(rng(ans), std::greater<int>());
    if(ans.empty()) {
        ans.pb(0);
    }
    return ans;
}

int getVal(const vector<int>& v) {
    int ans = 1;
    rep(i, 0, sz(v) - 1) {
        rep(j, 1, v[i]) {
            ans *= primes[i];
            if(ans > 1e6) {
                return -1;
            }
        }
    }
    return ans;
}

int getDiv(const vector<int>& v) {
    int ans = 1;
    rall(x, v) {
        ans *= x + 1;
    }
    return ans;
}

set<vector<int> > generateAll() {
    set<vector<int> > st, ans;
    rep(x, 1, 25) {
        st.insert(vector<int>(1, x));
    }
    bool ch = true;
    while(ch) {
        set<vector<int> > stt;
        ch = false;
        rall(v, st) {
            ans.insert(v);
            rep(i, 0, sz(v) - 1) {
                rep(x, 1, v[i] - 1) {
                    vector<int> nv(v);
                    nv[i] -= x;
                    nv.pb(x);
                    sort(rng(nv), std::greater<int>());
                    stt.insert(nv);
                    ch = true;
                }
            }
        }
        st = stt;
    }
    ans.insert(vector<int>(1, 0));
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fill(isp + 2, isp + X, true);
    rep(i, 2, X - 1) {
        if(isp[i]) {
            primes.pb(i);
            for(int j = 2 * i; j < X; j += i) {
                isp[j] = false;
            }
        }
    }
    rep(i, 0, sz(primes) - 1) {
        pi[primes[i]] = i;
    }
    set<vector<int> > st = generateAll();
    set<vector<int> > stst, ost;
    rall(v, st) {
        if(getVal(v) == -1) {
            ost.insert(v);
        } else {
            stst.insert(v);
        }
    }
    int n = 0;
    rall(v, stst) {
        toNode[v] = ++n;
    }
    rall(v, ost) {
        toNode[v] = ++n;
    }
    int ed = 0;
    rall(v, st) {
        int from = toNode[v];
        ndiv[from] = getDiv(v);
        rep(i, 0, sz(v) - 1) {
            if(!v[i]) continue;
            vector<int> nv(v);
            nv[i]--;
            sort(rng(nv), std::greater<int>());
            if(nv.back() == 0 && sz(nv) > 1) {
                nv.pop_back();
            }
            if(toNode.find(nv) == toNode.end()) {
                continue;
            }
            int to = toNode[nv];
            graph[from].insert(to);
            graph[to].insert(from);
            ed++;
        }
    }
    rall(v, stst) {
        int u = toNode[v];
        fill(cnt[u] + 1, cnt[u] + N, 42);
    }
    rall(v, stst) {
        int s = toNode[v];
        fill(dist[s] + 1, dist[s] + n + 1, 42);
        qs = 0, qe = 0;
        q[qs++] = s;
        dist[s][s] = 0;
        while(qs != qe) {
            int u = q[qe++];
            qe %= N;
            if(ndiv[u] < N) {
                cnt[s][ndiv[u]] = min(cnt[s][ndiv[u]], dist[s][u]);
            }
            rall(v, graph[u]) {
                if(dist[s][v] > dist[s][u] + 1) {
                    dist[s][v] = dist[s][u] + 1;
                    q[qs++] = v;
                    qs %= N;
                }
            }
        }
    }
    int t;
    scanf("%d", &t);
    while(t--) {
        int a, b;
        scanf("%d %d", &a, &b);
        vector<int> va = getPow(a), vb = getPow(b);
        int u = toNode[va], v = toNode[vb];
        int ans = 42;
        rep(nd, 1, 300) {
            ans = min(ans, cnt[u][nd] + cnt[v][nd]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
