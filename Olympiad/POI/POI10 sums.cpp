/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - For small values, the problem can be solved with an O(n * A) dynamic programming solution.
 *          - For values bigger than a[n], an element is in A' iff the gcd of every a_i divides it.
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

const int N = 5555, A = 55555;
bool dp[A];
int a[N];
int n, k;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
    }
    dp[0] = 1;
    int g = a[1];
    rep(i, 1, n) {
        g = __gcd(g, a[i]);
        rep(x, a[i], a[n]) {
            dp[x] |= dp[x - a[i]];
        }
    }
    cin >> k;
    while(k--) {
        int x;
        cin >> x;
        bool ans;
        if(x <= a[n]) {
            ans = dp[x];
        } else {
            ans = x % g == 0;
        }
        cout << (ans ? "TAK" : "NIE") << endl;
    }
    return 0;
}
