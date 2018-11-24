/*
 *  Author: Jeremy Bouin
 *  
 *  Idea:   
 *          - Let f(n) be the sum of i * (-1) ^ i for i from 1 to n. f(n) = ⌈n/2⌉ * (-1) ^ n.
 *          - The answer to a query is f(r) - f(l - 1).
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

inline int get(int x) {
    return (x + 1) / 2 * (x & 1 ? -1 : 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        int ans = get(r) - get(l - 1);
        cout << ans << endl;
    }
    return 0;
}
