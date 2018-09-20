/*
 *  Author: Jeremy Bouin
 *
 *  Idea: 
 *          - Element i is irrelevant iff m divides (n - 1) choose (i - 1).
 *          - We can't use Euler's theorem directly since m is not necessarily prime. The idea is to check if
 *            for every prime p with power k in the prime factorization of m, p^k divides (n - 1) choose (i - 1). 
 *          - Use the formula n choose r = n * (n - 1) choose (r - 1) / r and cancel every p in the fraction
 *            since it doesn't have a multiplicative inverse modulo p ^ k.
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
bool has[N];

ll powmod(ll x, ll n, ll m = MOD) {
    ll ans = 1;
    while(n) {
        if(n & 1) {
            ans = ans * x % m;
        }
        x = x * x % m;
        n >>= 1;
    }
    return ans;
}
inline ll invmod(ll x, ll m = MOD) {
    return powmod(x, m - 2, m);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    while(cin >> n >> m) {
        if(n <= 2) {
            cout << 0 << endl << endl;
            continue;
        }
        fill(has + 1, has + n + 1, true);
        has[1] = false;
        has[n] = false;
        vector<pair<int, int> > pf;
        vector<int> ans;
        int x = m;
        for(int d = 2; d * d <= m; d++) {
            if(x % d == 0) {
                pf.pb(make_pair(d, 0));
                while(x % d == 0) {
                    x /= d;
                    pf.back().se++;
                }
            }
        }
        if(x > 1) {
            pf.pb(make_pair(x, 1));
        }
        rall(pa, pf) {
            int p = pa.fi, mo = powmod(p, pa.se);
            ll num = 1, den = 1, po = 0;
            if(n - 1 >= 2) {
                rep(i, 2, n - 1) {
                    int cn = n - i + 1, cd = i - 1;
                    while(cn % p == 0) {
                        cn /= p;
                        po++;
                    }
                    num = (num * cn) % mo;
                    while(cd % p == 0) {
                        cd /= p;
                        po--;
                    }
                    den = (den * cd) % mo;
                    int cur = num * invmod(den, mo) % mo * powmod(p, po, mo) % mo;
                    if(cur) {
                        has[i] = false;
                    }
                }
            }
        }
        rep(i, 1, n) {
            if(has[i]) {
                ans.pb(i);
            }
        }
        cout << sz(ans) << endl;
        rep(i, 0, sz(ans) - 1) {
            cout << ans[i];
            if(i < sz(ans) - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
