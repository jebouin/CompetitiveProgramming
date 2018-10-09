/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Draw a grid of the box with its reflections along both axis. A valid polyline in the original box
 *            is a straight line from a blue point in a box to a red point in another box.
 *          - For the polyline to touch the four sides of the original box, the line has to cross two horizontal
 *            borders between grid boxes and two vertical borders. The answer is the shortest valid line.
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
#define int long long
typedef long long ll;
using namespace std;

class Polyline {
    private:
    int a, b;
    double dist(int x1, int y1, int x2, int y2) {
        int dx = x1 - x2, dy = y1 - y2;
        return sqrt(dx * dx + dy * dy);
    }

    bool ok(int x1, int y1, int x2, int y2) {
        x1 += 1000 * a;
        y1 += 1000 * b;
        x2 += 1000 * a;
        y2 += 1000 * b;
        int bx1 = x1 / a, bx2 = x2 / a;
        int by1 = y1 / b, by2 = y2 / b;
        return abs(bx1 - bx2) >= 2 && abs(by1 - by2) >= 2;
    }

    public:
    double length(int a, int b, int x0, int y0, int x1, int y1) {
        this->a = a;
        this->b = b;
        double ans = 1e5;
        rep(i, -5, 5) {
            rep(j, -5, 5) {
                bool ri = i % 2, rj = j % 2;
                int xx1 = (ri ? a - x1 : x1) + i * a;
                int yy1 = (rj ? b - y1 : y1) + j * b;
                if(ok(x0, y0, xx1, yy1)) {
                    double d = dist(x0, y0, xx1, yy1);
                    if(d < ans) {
                        ans = d;
                    }
                }
            }
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Polyline test;
    cout << test.length(98, 200, 78, 32, 35, 174) << endl;
    return 0;
}
