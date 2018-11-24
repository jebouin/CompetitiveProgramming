/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - We can find the number of white cells in a rectangle (x1, y1, x2, y2) of the original chessboard
 *            in constant time. We can then find the chang in the number of white cells when a rectangle is 
 *            painted black or white.
 *          - Calculate the number of white cells by adding the change from both rectangles.
 *          - If the two rectangles intersect, compute the intersection (which is also a rectangle) and fill
 *            the rest of the intersection black.
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

inline int getWhite(int x1, int y1, int x2, int y2) {
    int area = (x2 - x1 + 1) * (y2 - y1 + 1);
    return area & 1 ? area / 2 + 1 - (x1 + y1 & 1) : area / 2;
}

inline void setColor(int x1, int y1, int x2, int y2, bool cw, int& w) {
    int area = (x2 - x1 + 1) * (y2 - y1 + 1);
    int white = getWhite(x1, y1, x2, y2);
    if(cw) {
        w += area - white;
    } else {
        w -= white;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        int area = n * m, w = getWhite(1, 1, m, n);
        int x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        if(x1 > x4 || x2 < x3 || y1 > y4 || y2 < y3) {
            setColor(x1, y1, x2, y2, true, w);
            setColor(x3, y3, x4, y4, false, w);
        } else {
            int xx1, yy1, xx2, yy2;
            if(x1 >= x3 && x2 <= x4) {
                xx1 = x1, xx2 = x2;
            } else if(x3 >= x1 && x4 <= x2) {
                xx1 = x3, xx2 = x4;
            } else if(x1 >= x3 && x1 <= x4) {
                xx1 = x1, xx2 = x4;
            } else {
                xx1 = x3, xx2 = x2;
            }
            if(y1 >= y3 && y2 <= y4) {
                yy1 = y1, yy2 = y2;
            } else if(y3 >= y1 && y4 <= y2) {
                yy1 = y3, yy2 = y4;
            } else if(y1 >= y3 && y1 <= y4) {
                yy1 = y1, yy2 = y4;
            } else {
                yy1 = y3, yy2 = y2;
            }
            setColor(x1, y1, x2, y2, true, w);
            setColor(x3, y3, x4, y4, false, w);
            setColor(xx1 + 1, yy1, xx2 + 1, yy2, false, w);
        }
        cout << w << " " << area - w << endl;
    }
    return 0;
}
