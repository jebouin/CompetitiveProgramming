/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - We can consider every team and then remove the teams that don't cooperate.
 *          - We have min(x_i + y_j, x_j + y_i) == x_i + y_j iff x_i - y_i <= x_j - y_j.
 *          - Sort every person by increasing x_i - y_i, compute prefix sums for x and y then sum for each person
 *            the minimum score with every other person.
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

typedef struct T {
    int x, y, id;
} T;

const int N = 333333;
int u[N], v[N], ans[N];
T teams[N];
int sx[N], sy[N], ord[N];
int n, m;

bool comp(const T& t, const T& s) {
    int di = t.x - t.y;
    int dj = s.x - s.y;
    return di < dj;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf(LL, &n);
    scanf(LL, &m);
    rep(i, 1, n) {
        scanf(LL, &(teams[i].x));
        scanf(LL, &(teams[i].y));
        teams[i].id = i;
    }
    rep(i, 1, m) {
        scanf(LL, u + i);
        scanf(LL, v + i);
    }
    sort(teams + 1, teams + n + 1, comp);
    rep(i, 1, n) {
        sx[i] = sx[i - 1] + teams[i].x;
        sy[i] = sy[i - 1] + teams[i].y;
        ord[teams[i].id] = i;
    }
    rep(i, 1, n) {
        int sum = (n - i) * teams[i].x + sy[n] - sy[i];
        sum += (i - 1) * teams[i].y + sx[i - 1];
        ans[teams[i].id] = sum;
    }
    rep(i, 1, m) {
        int ii = ord[u[i]], jj = ord[v[i]];
        int mini = min(teams[ii].x + teams[jj].y, teams[ii].y + teams[jj].x);
        ans[u[i]] -= mini;
        ans[v[i]] -= mini;
    }
    rep(i, 1, n) {
        printf(LL, ans[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}
