/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The answer is at most 7 since the product of the first 7 primes is greater than 300000.
 *          - Let dp[i][g] be the number of ways to select a subset of size i that has a gcd of g.
 *          - Use inclusion-exclusion to compute the states: Let f(g) be the number of multiples of g in the
 *            original set. dp[i][g] = (f(g) choose i) - sum of dp[i][k * g] for k from 2 until k * g >= 300000.
 *          - Compute dp[i][g] modulo a big prime number, the answer is the smallest i such that dp[i][1] >= 1.
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

const int N = 333333, M = 8;
int cnt[N], cntt[N], dp[M][N];
int n;

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

ll fact[N], invfact[N];
void initfact(ll m = MOD) {
    fact[0] = 1;
    invfact[0] = 1;
    rep(i, 1, N - 1) {
        fact[i] = fact[i - 1] * i % m;
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
    cin >> n;
    rep(i, 1, n) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    rep(d, 1, N - 1) {
        for(int m = d; m < N; m += d) {
            cntt[d] += cnt[m];
        }
    }
    rep(i, 1, 7) {
        rrep(g, 1, N - 1) {
            dp[i][g] = ncr(cntt[g], i);
            for(int x = 2 * g; x < N; x += g) {
                dp[i][g] = ((dp[i][g] - dp[i][x]) % MOD + MOD) % MOD;
            }
        }
        if(dp[i][1] > 0) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
