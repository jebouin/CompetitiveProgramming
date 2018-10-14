/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Place the points along a line. Decrease the distance from the previous point by half each time.
 *            If the previous point is of a different color than the first, place the next point between the
 *            two last points. If the previous point is of the same color, place the next one away from it.
 *          - Since all coordinates must be integers and there can be at most 30 iterations, the distance
 *            between the coordinates of two points will get small, 1 in the worst case. Since we don't want 
 *            the line to touch any point, place the points alon the main diagonal and draw the line
 *            perpendicular to it.
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
typedef long long ll;
using namespace std;

const int R = 500000000;

bool color(int x, int y = 0) {
    cout << x << " " << y << endl;
    string s;
    cin >> s;
    return s == "black";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    if(n == 1) {
        color(0, 0);
        cout << "0 1 1 1" << endl;
    } else {
        bool col = color(0, 0);
        bool fc = col;
        bool diff = false;
        int ppos;
        int pos = 5e8, dist = 5e8;
        rep(k, 2, n) {
            col = color(pos, pos);
            if(col != fc) {
                diff = true;
            }
            if(k == n) {
                if(diff) {
                    if(fc != col) {
                        cout << pos << " " << pos - dist << " " << pos - dist << " " << pos << endl;
                    } else {
                        cout << pos + dist << " " << pos << " " << pos << " " << pos + dist << endl;
                    }
                } else {
                    cout << "0 1 1 2" << endl;
                }
                break;
            }
            dist >>= 1;
            ppos = pos;
            pos += col == fc ? dist : -dist;
        }
    }
    return 0;
}
