/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Use a segment tree to process a shower in O(log m) time.
 *          - For each state s, we can use binary search on the number of showers before s gets
 *            enough meteors. The time complexity is O(nq log m) which is too slow.
 *          - We can use parallel binary search: https://codeforces.com/blog/entry/45578
 *          - Process a binary search range [l, r] for multiple states at the same time, traversing
 *            the tree in an in-order fashion to minimize the number of updates.
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

const int N = 333333;
int a[N], sl[N], sr[N], ans[N];
ll p[N], sa[N], stree[N << 2];
vector<int> sectors[N];
int n, m, q;

ll query(int l, int r, int cl, int cr, int pos) {
    if(cl > r || cr < l) {
        return 0LL;
    } else if(cl >= l && cr <= r) {
        return stree[pos];
    }
    int m = cl + cr >> 1;
    ll x = query(l, r, cl, m, pos * 2 + 1);
    ll y = query(l, r, m + 1, cr, pos * 2 + 2);
    return x + y;
}

void update(int i, int cl, int cr, ll val, int pos) {
    if(cl == cr) {
        stree[pos] += val;
        return;
    }
    int m = cl + cr >> 1;
    if(cl <= i && i <= m) {
        update(i, cl, m, val, pos * 2 + 1);
    } else {
        update(i, m + 1, cr, val, pos * 2 + 2);
    }
    stree[pos] = stree[pos * 2 + 1] + stree[pos * 2 + 2];
}

bool getMeteors(int state) {
    ll cur = 0;
    rall(s, sectors[state]) {
        cur += query(1, s, 1, m + 1, 0);
        if(cur >= p[state]) {
            return true;
        }
    }
    return false;
}

void update(int k, bool add) {
    int x = sa[k] * (add ? 1 : -1);
    if(sl[k] > sr[k]) {
        update(1, 1, m + 1, x, 0);
        update(sr[k] + 1, 1, m + 1, -x, 0);
        update(sl[k], 1, m + 1, x, 0);
        update(m + 1, 1, m + 1, -x, 0);
    } else {
        update(sl[k], 1, m + 1, x, 0);
        update(sr[k] + 1, 1, m + 1, -x, 0);
    }
}

void solve(int l, int r, vector<int>& v, int& k) {
    if(!sz(v)) return;
    int m = l + r >> 1;
    while(k < m) {
        k++;
        update(k, true);
    }
    while(k > m) {
        update(k, false);
        k--;
    }
    vector<int> vl, vr;
    rall(i, v) {
        if(getMeteors(i)) {
            vl.pb(i);
            ans[i] = m;
        } else {
            vr.pb(i);
        }
    }
    v.clear();
    if(l < r) {
        solve(l, m, vl, k);
        solve(m + 1, r, vr, k);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d %d", &n, &m);
    rep(i, 1, m) {
        scanf("%d", a + i);
        sectors[a[i]].pb(i);
    }
    rep(i, 1, n) {
        scanf(LL, p + i);
    }
    scanf("%d", &q);
    rep(i, 1, q) {
        scanf("%d %d ", sl + i, sr + i);
        scanf(LL, sa + i);
    }
    vector<int> v;
    rep(i, 1, n) {
        v.pb(i);
    }
    int k = 0;
    solve(1, q, v, k);
    rep(i, 1, n) {
        if(ans[i]) {
            printf("%d\n", ans[i]);
        } else {
            printf("NIE\n");
        }
    }
    return 0;
}

