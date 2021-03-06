/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - We have to answer to the queries online, so we can't use Mo's technique.
 *          - Let riᵢ be the last possible position such that if we take every element from i to riᵢ, the type
 *            at index i will be taken at most k times. We can use n queues to compute this array.
 *          - For each soldier i between l and r, we take it if riᵢ >= k.
 *          - Use a segment tree where each node contains a sorted vector of every value of riᵢ and use 
 *            binary search on them.
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

const int N = 111111;
int a[N], ri[N];
deque<int> de[N];
vector<int> stree[N << 2];
int n, k, q, m;

vector<int>& build(int l, int r, int pos) {
    if(l == r) {
        stree[pos].push_back(ri[l]);
        return stree[pos];
    }
    int m = l + r >> 1;
    vector<int>& x = build(l, m, pos * 2 + 1);
    vector<int>& y = build(m + 1, r, pos * 2 + 2);
    stree[pos].insert(stree[pos].end(), rng(x));
    stree[pos].insert(stree[pos].end(), rng(y));
    sort(rng(stree[pos]));
    return stree[pos];
}

int query(int l, int r, int cl, int cr, int pos) {
    if(cl > r || cr < l) {
        return 0;
    } else if(cl >= l && cr <= r) {
        return stree[pos].end() - lower_bound(rng(stree[pos]), r);
    }
    int m = cl + cr >> 1;
    int x = query(l, r, cl, m, pos * 2 + 1);
    int y = query(l, r, m + 1, cr, pos * 2 + 2);
    return x + y;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    rep(i, 1, n) {
        int x;
        cin >> x;
        m = max(m, x);
        de[x].push_back(i);
        if(sz(de[x]) > k) {
            int j = de[x].front();
            de[x].pop_front();
            ri[j] = i - 1;
        }
        a[i] = x;
    }
    rep(x, 1, m) {
        while(sz(de[x])) {
            int i = de[x].front();
            de[x].pop_front();
            ri[i] = n + 1;
        }
    }
    build(1, n, 0);
    int last = 0;
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        int l = (x + last) % n + 1;
        int r = (y + last) % n + 1;
        if(l > r) swap(l, r);
        int ans = query(l, r, 1, n, 0);
        cout << ans << endl;
        last = ans;
    }
    return 0;
}
