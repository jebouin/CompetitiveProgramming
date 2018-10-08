/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The queen divides the board in 4 quadrants.
 *          - The answer is YES iff the starting and ending positions are in the same quadrant.
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

int n, ax, ay, bx, by, cx, cy;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    bool x = bx > ax, y = by > ay;
    bool xx = cx > ax, yy = cy > ay;
    cout << (x == xx && y == yy ? "YES" : "NO") << endl;
    return 0;
}
