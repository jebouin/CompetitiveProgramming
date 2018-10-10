/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let's solve the problem in reverse: Some panels are ON and the goal is to flip them OFF.
 *          - Let bᵢ be 1 if the panels i and i + 1 are different and 0 if they are equal.
 *          - Flipping the panels i to i + a - 1 only flips two values in b: bᵢ₋₁ and bᵢ₊ₐ₋₁.
 *          - The problem can be seen as a graph with n + 1 nodes and an edge between u and v iff there exists
 *            an aᵢ such that |u - v| = aᵢ. A value in b can be seen as a token that we can move in the graph
 *            by following the edges and merge when encountering another token.
 *          - The goal is to make every token disappear. Since we have at most 2k tokens, the problem can be
 *            solved with dp on masks.
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

const int N = 11111, K = 11, L = 111;
vector<int> graph[N];
int x[K], dist[K << 1][N];
int dp[1 << 22];
int q[L * N], qs, qe;
vector<int> xv;
int n, k, l;

int solve(int mask) {
    if(mask == 0) {
        return 0;
    }
    if(dp[mask] >= 0) {
        return dp[mask];
    }
    int m = mask;
    int b0, b1;
    rep(i, 0, sz(xv) - 1) {
        if(mask & (1 << i)) {
            b0 = i;
            break;
        }
    }
    mask ^= 1 << b0;
    int ans = 1e7;
    rep(i, 0, sz(xv) - 1) {
        if(mask & (1 << i)) {
            b1 = i;
            ans = min(ans, dist[b0][xv[b1]] + solve(mask ^ (1 << b1)));
        }
    }
    dp[m] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fill(dp, dp + (1 << 22), -1);
    cin >> n >> k >> l;
    rep(i, 1, k) {
        cin >> x[i];
    }
    rep(i, 1, k) {
        if(i == 1 || x[i - 1] < x[i] - 1) {
            xv.pb(x[i] - 1);
        }
        if(i == k || x[i + 1] > x[i] + 1) {
            xv.pb(x[i]);
        }
    }
    set<int> ast;
    rep(i, 1, l) {
        int a;
        cin >> a;
        ast.insert(a);
    }
    rall(a, ast) {
        rep(u, 0, n - a) {
            int v = u + a;
            graph[u].pb(v);
            graph[v].pb(u);
        }
    }
    rep(i, 0, sz(xv) - 1) {
        fill(dist[i], dist[i] + n + 1, 1e7);
        qs = 0, qe = 0;
        q[qs++] = xv[i];
        qs %= L * N;
        dist[i][xv[i]] = 0;
        while(qs != qe) {
            int u = q[qe++];
            qe %= L * N;
            rall(v, graph[u]) {
                if(dist[i][u] + 1 < dist[i][v]) {
                    dist[i][v] = dist[i][u] + 1;
                    q[qs++] = v;
                    qs %= L * N;
                }
            }
        }
    }
    int ans = solve((1 << sz(xv)) - 1);
    cout << (ans >= 1e7 ? -1 : ans) << endl;
    return 0;
}
