/*
 *  Author: Jeremy Bouin
 *
 *  Idea: 
 *          - Using prefix sum and binary search, we can compute the total length of air flow between any two
 *            coordinates in O(log n) time.
 *          - The optimal flight starts from the beginning of an air flow, so we can check in O(n log n) time
 *            if a certain flight distance is achievable.
 *          - Using binary search on the answer, the total time complexity is O(n log² n).
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
int l[N], r[N], sum[N];
int n, h;

int getSum(int x) {
    int i = upper_bound(l + 1, l + n + 2, x - 1) - l;
    int ii = i - 1;
    int ans = sum[ii];
    return ans;
}

bool possible(int start, int len) {
    int end = start + len;
    int i = upper_bound(l + 1, l + n + 2, end) - l;
    int ii = i - 1;
    if(ii && end > l[ii] && end <= r[ii]) {
        return possible(start, len + (r[ii] + 1) - end);
    }
    bool ans = getSum(end) - getSum(start - 1) + h >= len;
    return ans;
}

bool possible(int len) {
    rep(i, 1, n) {
        if(possible(l[i], len)) {
            return true;
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> h;
    rep(i, 1, n) {
        cin >> l[i] >> r[i];
        sum[i] = sum[i - 1] + r[i] - l[i];
    }
    l[n + 1] = 1e10;
    int l = 0, r = 3e9;
    while(r - l > 1) {
        int m = l + r >> 1;
        if(possible(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    int ans = l;
    if(possible(r)) {
        ans = r;
    }
    cout << ans << endl;
    return 0;
}
