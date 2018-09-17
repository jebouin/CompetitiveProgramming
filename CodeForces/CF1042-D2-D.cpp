/*
 *  Author: Jeremy Bouin
 *
 *  Idea: 
 *          - Iterating over every subarray is too slow.
 *          - Compute prefix sums as a new array, a valid subarray [l, r] satisfies sum[r] - t < sum[l - 1].
 *          - Iterate over every r and find the number of valid l using a persistent segment tree on compressed
 *            coordinates.
 *          - Time complexity: O(n log n)
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

const int N = 222222;
int sum[N], stree[N << 3], lazy[N << 3];
set<int> st;
map<int, int> comp;
int n, t, nn;

void updateLazy(int cl, int cr, int pos) {
    if(lazy[pos]) {
        stree[pos] += lazy[pos] * (cr - cl + 1);
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
        stree[pos] += (cr - cl + 1) * v;
        if(cl < cr) {
            lazy[pos * 2 + 1] += v;
            lazy[pos * 2 + 2] += v;
        }
        return;
    }
    int m = cl + cr >> 1;
    update(l, r, cl, m, v, pos * 2 + 1);
    update(l, r, m + 1, cr, v, pos * 2 + 2);
    stree[pos] = stree[pos * 2 + 1] + stree[pos * 2 + 2];
}

int query(int l, int r, int cl, int cr, int pos) {
    updateLazy(cl, cr, pos);
    if(cl > r || cr < l) {
        return 0;
    } else if(cl >= l && cr <= r) {
        return stree[pos];
    }
    int m = cl + cr >> 1;
    int x = query(l, r, cl, m, pos * 2 + 1);
    int y = query(l, r, m + 1, cr, pos * 2 + 2);
    return x + y;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> t;
    rep(i, 1, n) {
        int x;
        cin >> x;
        sum[i] = sum[i - 1] + x;
        st.insert(sum[i]);
        st.insert(sum[i - 1] + t);
    }
    rall(x, st) {
        comp[x] = ++nn;
    }
    int ans = 0;
    rep(r, 1, n) {
        int i = comp[sum[r - 1] + t];
        update(i, i, 1, nn, 1, 0);
        i = comp[sum[r]];
        if(i == nn) continue;
        i++;
        int cur = query(i, nn, 1, nn, 0);
        ans += cur;
    }
    cout << ans << endl;
    return 0;
}
