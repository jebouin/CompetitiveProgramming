/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Two vertices need at least an edge to be connected so the minimum number of isolated vertices is
 *            max(0, n - 2m).
 *          - To have the maximum number of isolated vertices, the edges should form a part of the smallest
 *            complete graph possible.
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
#define int long long
typedef long long ll;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int mini = max(0LL, n - 2 * m);
    int maxi;
    rep(i, 0, n) {
        int cur = i * (i - 1) / 2;
        if(cur >= m) {
            maxi = n - i;
            break;
        }
    }
    cout << mini << " " << maxi << endl;
    return 0;
}
