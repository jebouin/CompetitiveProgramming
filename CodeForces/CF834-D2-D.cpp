/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let dp[nb][i] be the maximum score if nb boxes are used to store the first i cakes.
 *          - Let score(l, r) be the score of a box from l to r, we have 
 *            dp[nb][i] = max(dp[nb-1][j-1] + score(j, i)) for every j <= i.
 *          - This solution takes O(kn²) time which is too slow.
 *          - Store the value of dp[nb-1][j-1] + score(j, i) in a segment tree. To go from i to i+1, we need
 *            to add 1 to every element at position j such that no cake from j to i is equal to aᵢ. These
 *            indices form a segment from the last index of aᵢto i, so we need to keep in memory the last time
 *            every element of the array a was encountered.
 *          - Using lazy propagation, this solution takes O(kn log n) time.
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

const int N = 35555, K = 55;
int a[N], dp[K][N], lp[N], stree[N << 2], lazy[N << 2];
int n, k;

int build(int l, int r, int pos, int nb) {
    if(l == r) {
        stree[pos] = dp[nb - 1][l - 1];
        return stree[pos];
    }
    int m = l + r >> 1;
    int x = build(l, m, pos * 2 + 1, nb);
    int y = build(m + 1, r, pos * 2 + 2, nb);
    stree[pos] = max(x, y);
    return stree[pos];
}

void updateLazy(int cl, int cr, int pos) {
    if(lazy[pos]) {
        stree[pos] += lazy[pos];
        if(cl < cr) {
            lazy[pos * 2 + 1] += lazy[pos];
            lazy[pos * 2 + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
}

void update(int l, int r, int cl, int cr, int v, int pos) {
    updateLazy(cl, cr, pos);
    if(cl > r || cr < l) {
        return;
    } else if(cl >= l && cr <= r) {
        stree[pos] += v;
        if(cl < cr) {
            lazy[pos * 2 + 1] += v;
            lazy[pos * 2 + 2] += v;
        }
        return;
    }
    int m = cl + cr >> 1;
    update(l, r, cl, m, v, pos * 2 + 1);
    update(l, r, m + 1, cr, v, pos * 2 + 2);
    stree[pos] = max(stree[pos * 2 + 1], stree[pos * 2 + 2]);
}

int query(int l, int r, int cl, int cr, int pos) {
    updateLazy(cl, cr, pos);
    if(cl > r || cr < l) {
        return -1;
    } else if(cl >= l && cr <= r) {
        return stree[pos];
    }
    int m = cl + cr >> 1;
    int x = query(l, r, cl, m, pos * 2 + 1);
    int y = query(l, r, m + 1, cr, pos * 2 + 2);
    return max(x, y);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    rep(i, 1, n) {
        cin >> a[i];
    }
    rep(nb, 1, k) {
        fill(lazy, lazy + (N << 2), 0);
        fill(lp, lp + n + 1, 0);
        build(1, n, 0, nb);
        rep(i, 1, n) {
            int le = lp[a[i]] + 1;
            int ri = i;
            update(le, ri, 1, n, 1, 0);
            lp[a[i]] = i;
            dp[nb][i] = query(1, i, 1, n, 0);
        }
    }
    cout << dp[k][n] << endl;
    return 0;
}
