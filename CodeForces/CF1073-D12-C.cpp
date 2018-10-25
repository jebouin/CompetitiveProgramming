/*
 *  Author: Jeremy Bouin
 *  
 *  Idea:
 *          - Use binary search to find the answer.
 *          - To check if it possible to reach the point (x, y) with changes in a subsegment of length len,
 *            we can try every subsegment position from 1 to n - len + 1. Use prefix sums to find the position
 *            if we only count the moves not in the subsegment. Then check if it is possible to reach the point
 *            by setting the moves inside the subsegment. The order of the moves don't matter.
 *          - Note that we can't delete moves, so the answer is no if there are an odd number of moves left
 *            after reaching the point.
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

const int N = 222222;
int sx[N], sy[N];
int tx, ty;
int n;

bool solve(int len) {
    if(len == 0) {
        return sx[n] == tx && sy[n] == ty;
    }
    rep(i, 1, n - len + 1) {
        int x = sx[i - 1] + sx[n] - sx[i + len - 1];
        int x = sy[i - 1] + sy[n] - sy[i + len - 1];
        int dx = abs(x - tx), dy = abs(y - ty);
        int rem = len - dx - dy;
        if(rem >= 0 && rem % 2 == 0) {
            return true;
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    string s;
    cin >> s;
    rep(i, 1, n) {
        char c = s[i - 1];
        sx[i] = sx[i - 1];
        sy[i] = sy[i - 1];
        if(c == 'U') {
            sy[i]++;
        } else if(c == 'D') {
            sy[i]--;
        } else if(c == 'R') {
            sx[i]++;
        } else {
            sx[i]--;
        }
    }
    cin >> tx >> ty;
    int l = 0, r = n;
    while(r - l > 1) {
        int m = l + r >> 1;
        if(solve(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    int ans = r;
    if(solve(l)) {
        ans = l;
    }
    if(!solve(ans)) {
        ans = -1;
    }
    cout << ans << endl;
    return 0;
}
