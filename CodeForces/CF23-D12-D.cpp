/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let x1, x2 and x3 be the given points.
 *          - Let's place the first point of the tetragon such that its distance to x1 and x2 is the same.
 *            The distance d from the first point to the segment [x1, x2] must be choosen such that the distance
 *            from the second point to x2 and x3 is the same. As d increases, the difference between the distance
 *            from the second point to x2 and the distance to x3 is monotonous, so use binary search to find it.
 *          - Don't forget to check that the teetragon is strictly convex.
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
#endif
#define y0    oooo
#define y1    ooox
#define yn    ooxo
#define prev  ooxx
#define next  oxoo
#define read  oxox
#define tm    oxxo
#define rng(a) a.begin(), a.end()
#define PI 3.14159265358979323846
#define MOD 1000000007
#define endl "\n"
typedef long long ll;
using namespace std;

pair<int, int> p[4];

double distsq(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
}

template<typename T>
T det(T x1, T y1, T x2, T y2) {
    return x1 * y2 - x2 * y1;
}

template<typename T>
T turn(T x1, T y1, T x2, T y2, T x3, T y3) {
    return det(x2 - x1, y2 - y1, x3 - x2, y3 - y2);
}

double getDist(double d) {
    double ax = (p[1].fi + p[2].fi) * .5;
    double ay = (p[1].se + p[2].se) * .5;
    ax += d * (p[2].se - p[1].se);
    ay -= d * (p[2].fi - p[1].fi);
    double bx = 2 * p[2].fi - ax;
    double by = 2 * p[2].se - ay;
    double d2 = distsq(bx, by, p[2].fi, p[2].se);
    double d3 = distsq(bx, by, p[3].fi, p[3].se);
    return d2 - d3;
}

bool solve(double l) {
    if(abs(getDist(l)) > 1e-9) {
        return false;
    }
    vector<pair<double, double> > ans;
    ans.pb(make_pair((p[1].fi + p[2].fi) * .5 + l * (p[2].se - p[1].se), (p[1].se + p[2].se) * .5 - l * (p[2].fi - p[1].fi)));
    ans.pb(make_pair(2 * p[2].fi - ans[0].fi, 2 * p[2].se - ans[0].se));
    ans.pb(make_pair(2 * p[3].fi - ans[1].fi, 2 * p[3].se - ans[1].se));
    ans.insert(ans.begin(), make_pair(2 * p[1].fi - ans[0].fi, 2 * p[1].se - ans[0].se));
    int t = -1;
    rep(i, 0, 3) {
        double tu = turn(ans[i].fi, ans[i].se, ans[i + 1 & 3].fi, ans[i + 1 & 3].se, ans[i + 2 & 3].fi, ans[i + 2 & 3].se);
        if(abs(tu) < 1e-9) {
            return false;
        }
        bool cur = tu > 0;
        if(t == -1) {
            t = cur;
        } else if(t != cur) {
            return false;
        }
    }
    printf("YES\n");
    rall(p, ans) {
        printf("%.12g %.12g ", p.fi, p.se);
    }
    printf("\n");
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    scanf("%d", &t);
    while(t--) {
        rep(i, 1, 3) {
            scanf("%d %d", &(p[i].fi), &(p[i].se));
        }
        if(turn(p[1].fi, p[1].se, p[2].fi, p[2].se, p[3].fi, p[3].se) == 0) {
            printf("NO\n\n");
            continue;
        }
        sort(p + 1, p + 4);
        bool found = false;
        do {
            double l = -1e4, r = 1e4;
            double ld = l, rd = r;
            rep(i, 1, 70) {
                double m = (l + r) / 2;
                double dm = getDist(m);
                if(dm > 0) {
                    r = m;
                } else {
                    l = m;
                }
                double md = (ld + rd) / 2;
                double dmd = getDist(md);
                if(dmd > 0) {
                    ld = md;
                } else {
                    rd = md;
                }
            }
            if(solve(l)) {
                found = true;
                break;
            }
            if(solve(ld)) {
                found = true;
                break;
            }
        } while(next_permutation(p + 1, p + 4));
        if(!found) {
            printf("NO\n\n");
        }
    }
    return 0;
}
