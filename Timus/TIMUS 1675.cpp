/*
 *  Author: Jeremy Bouin
 *  
 *  Idea:
 *          - Choose k rows and l columns that will contain only zeroes, then count the number of matrices of
 *            size (m - k) x (n - l) that don't have any row or column with only zeroes.
 *          - We can calculate for every i and j the number of matrices that have at least i rows of zeroes and
 *            j columns of zeroes, then use inclusion-exclusion to get the number of matrices that don't have any
 *            row or column of zeroes.
 *          - Use binomial expansion to get a linear algorithm (with a log factor for modular inverse).
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
    return powmod(x, m - 2);
}

const int N = 111111;
int m, n, k, l;

ll fact[N], invfact[N];
void initfact() {
    fact[0] = 1;
    invfact[0] = 1;
    rep(i, 1, N - 1) {
        fact[i] = fact[i - 1] * i % MOD;
        invfact[i] = invmod(fact[i]);
    }
}
inline ll ncr(ll n, ll r, ll m = MOD) {
    if(r < 0 || r > n) return 0;
    if(r == 0 || r == n) return 1;
    return fact[n] * invfact[r] % m * invfact[n - r] % m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	initfact();
    cin >> m >> n >> k >> l;
    if(k == m && l != n || k != m && l == n) {
        cout << 0 << endl;
        return 0;
    }
    if(k == m && l == n) {
        cout << 1 << endl;
        return 0;
    }
    int ans = ncr(m, k) * ncr(n, l) % MOD;
    int mult = 0;
    m -= k;
    n -= l;
    rep(i, 0, m) {
        int sign = 1 - (i & 1) * 2;
        int add = ncr(m, i) * powmod((powmod(2, m - i) - 1 + MOD) % MOD, n) % MOD;
        mult = (mult + sign * add + MOD) % MOD;
    }
    ans = ans * mult % MOD;
    cout << ans << endl;
    return 0;
}
