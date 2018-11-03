/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - First, check if the sum of aᵢ is equal to the sum of bᵢ.
 *          - Build a flow network as follows:
 *            - Add an arc from the source to the node 2i with capacity aᵢ.
 *            - Add an arc from the node 2i+1 to the sink wit capacity bᵢ.
 *            - Add an arc from node 2i to 2i+1 with infinite capacity. The flow going through this arc is the number of people that stay on the
 *              i-th city.
 *            - For every road from u to v, add an arc from 2u to 2v+1 and 2v to 2u+1 with infinite capacity.
 *          - Compute the maximum flow in the network. If it is smaller than the sum of aᵢ, the answer is NO.
 *          - Else, the answer is YES and the number of people who move from city u to city v is equal to the flow from the arc 2u to 2v+1.
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
#define MOD 100000000
//#define endl "\n"
typedef long long ll;
using namespace std;

const int N = 111, INF = 200;
const int NN = 222;
int a[N], b[N];
int n, m;

bool vis[NN];
int flow[NN][NN], cap[NN][NN], par[NN];
bool augment(int nn, int s, int t, int& maxFlow) {
    fill(vis + 1, vis + nn + 1, false);
    fill(par + 1, par + nn + 1, 0);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while(sz(q)) {
        int u = q.front();
        q.pop();
        rep(v, 1, nn) {
            if(v != u && !vis[v] && cap[u][v] - flow[u][v] > 0) {
                q.push(v);
                par[v] = u;
                vis[v] = true;
            }
        }
    }
    if(!vis[t]) {
        return false;
    }
    int mini = 1e9;
    for(int v = t; v != s; v = par[v]) {
        int u = par[v];
        mini = min(mini, cap[u][v] - flow[u][v]);
    }
    for(int v = t; v != s; v = par[v]) {
        int u = par[v];
        flow[u][v] += mini;
        flow[v][u] -= mini;
    }
    maxFlow += mini;
    return true;
}
int fordFulkerson(int nn, int s, int t) {
    int ans = 0;
    while(augment(nn, s, t, ans));
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    rep(i, 1, n) {
        cin >> a[i];
    }
    rep(i, 1, n) {
        cin >> b[i];
    }
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        cap[u * 2][v * 2 + 1] = INF;
        cap[v * 2][u * 2 + 1] = INF;
    }
    rep(i, 1, n) {
        cap[i * 2][i * 2 + 1] = INF;
    }
    int so = 1, si = 2 * n + 2;
    int nn = 2 * n + 2;
    int sin = 0, sout = 0;
    rep(i, 1, n) {
        cap[so][2 * i] = a[i];
        sin += a[i];
    }
    rep(i, 1, n) {
        cap[2 * i + 1][si] = b[i];
        sout += b[i];
    }
    int f = fordFulkerson(nn, so, si);
    if(f != sin || sin != sout) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    rep(i, 1, n) {
        rep(j, 1, n) {
            cout << max(0, flow[2 * i][2 * j + 1]) << " ";
        }
        cout << endl;
    }
    return 0;
}
