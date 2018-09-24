/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Transform the coordinates (x, y) -> (x + y, x - y) to obtain an aligned axis rectangle.
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, d;
    cin >> n >> d;
    int m, x1 = d, x2 = 2 * n - d, y1 = -d, y2 = d;
    cin >> m;
    while(m--) {
        int x, y;
        cin >> x >> y;
        int t = x + y;
        y = x - y;
        x = t;
        cout << (x >= x1 && x <= x2 && y >= y1 && y <= y2 ? "YES" : "NO") << endl;
    }
    return 0;
}
