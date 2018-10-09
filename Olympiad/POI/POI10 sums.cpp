/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - A value x in A' can be written as y + ka₁ where y is a smaller value also in A'. So x is in A' iff
 *            the minimum value in A' congruent to y modulo a₁ is not greater than x.
 *          - Build a directed graph with a₁ nodes, where u and v share an edge of weight aᵢ iff u and v are
 *            congruent to v modulo a₁. Calculate the shortest paths in this graph.
 *          - A number is in A' iff the distance from 0 to x modulo a₁ is not greater than x.
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

const int N = 5555, A = 55555;
int a[N], dist[A];
int n, k;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
    }
    fill(dist, dist + A, 2e9);
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    dist[0] = 0;
    while(sz(q)) {
        pair<int, int> u = q.front();
        q.pop();
        rep(i, 1, n) {
            pair<int, int> v = make_pair((u.fi + a[i]) % a[1], u.se + a[i]);
            if(dist[v.fi] > v.se) {
                dist[v.fi] = v.se;
                q.push(v);
            }
        }
    }
    cin >> k;
    while(k--) {
        int x;
        cin >> x;
        cout << (dist[x % a[1]] <= x ? "TAK" : "NIE") << endl;
    }
    return 0;
}
