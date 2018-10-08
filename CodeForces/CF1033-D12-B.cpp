/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The area of the piece is a² - b² = (a - b)(a + b).
 *          - Since a > b, the area is prime iff a - b = 1 and a + b is prime.
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

bool isp(ll x) {
    if(x < 2) return false;
    if(x == 2) return true;
    for(ll d = 2; d * d <= x; d++) {
        if(x % d == 0) {
            return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        ll a, b;
        cin >> a >> b;
        cout << (a - b == 1 && isp(a + b) ? "YES" : "NO") << endl;
    }
    return 0;
}
