/*
 *  Author: Jeremy Bouin
 *
 *  Idea:   
 *          - The goal is to find the fermat point of a triangle.
 *          - Calculate its trilinear coordinates then convert back to cartesian coordinates.
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

double px[5], py[5], ppx[5], ppy[5];

double dist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

double dist(int i, int j) {
    return dist(px[i], py[i], px[j], py[j]);
}

double det(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double det(int i, int j, int k) {
    return det(px[k] - px[j], py[k] - py[j], px[j] - px[i], py[j] - py[i]);
}

double dot(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

double dot(int i, int j, int k) {
    return dot(px[k] - px[j], py[k] - py[j], px[j] - px[i], py[j] - py[i]);
}

double angle(int i, int j, int k) {
    double ans = atan2(det(i, j, k), dot(i, j, k)) + PI;
    return min(ans, 2 * PI - ans);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    rep(i, 1, 3) {
        cin >> px[i] >> py[i];
    }
    double aa = angle(3, 1, 2), ba = angle(1, 2, 3), ca = angle(2, 3, 1);
    const double r120 = 2 * PI / 3, d = PI / 6;
    double u = aa < r120, v = ba < r120, w = ca < r120;
    double ta = 1 - u + u * v * w / cos(aa - d);
    double tb = 1 - v + u * v * w / cos(ba - d);
    double tc = 1 - w + u * v * w / cos(ca - d);
    double la = dist(2, 3), lb = dist(1, 3), lc = dist(1, 2);
    double den = la * ta + lb * tb + lc * tc;
    double x = la * ta / den * px[1] + lb * tb / den * px[2] + lc * tc / den * px[3];
    double y = la * ta / den * py[1] + lb * tb / den * py[2] + lc * tc / den * py[3];
    cout << setprecision(13) << fixed << x << " " << y << endl;
    return 0;
}
