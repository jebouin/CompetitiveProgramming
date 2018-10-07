/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let a and x be the smallest side of the box and the tile, and b and y the greatest sides.
 *          - If x >= a and y >= b, there is no solution.
 *          - If x < a and y < b, we can fit the box with its sides aligned with the tile.
 *          - If y >= b, it may be possible to place the box by rotating it.
 *          - Let α be the angle between y and b, write a system of parametric equations in α.
 *            See https://www.jstor.org/stable/2691523?seq=1 for the proof.
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

void solve() {
    double a, b, x, y;
    cin >> a >> b >> x >> y;
    if(a > b) {
        swap(a, b);
    }
    if(x > y) {
        swap(x, y);
    }
    bool ok = x < a && y < b;
    if(!ok && x < a) {
        double v = pow((a + b) / (x + y), 2) + pow((b - a) / (y - x), 2);
        if(v > 2) {
            ok = true;
        }
    }
    cout << (ok ? "Escape is possible." : "Box cannot be dropped.") << endl;
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
