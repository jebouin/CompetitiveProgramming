/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Calculate the expected score starting from any cell with value x.
 *          - The answer is the sum of score[x] for each cell that has a value x smaller than the starting cell,
 *            divided by the number of such cells.
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
#define MOD 998244353
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

const int N = 1111, M = 1111111;
int a[N][N];
map<int, int> mp;
int is[M], js[M], iss[M], jss[M], cnt[M], score[M];
set<int> st;
int n, m, si, sj, be, sum1, sum2, sum3, sum4;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d %d", &n, &m);
    rep(i, 1, n) {
        rep(j, 1, m) {
            int x;
            scanf("%d", &x);
            a[i][j] = x;
            st.insert(x);
        }
    }
    scanf("%d %d", &si, &sj);
    int nn = 0;
    rall(x, st) {
        mp[x] = ++nn;
    }
    rep(i, 1, n) {
        rep(j, 1, m) {
            int y = mp[a[i][j]];
            a[i][j] = y;
            is[y] = (is[y] + i) % MOD;
            js[y] = (js[y] + j) % MOD;
            iss[y] = (iss[y] + i * i % MOD) % MOD;
            jss[y] = (jss[y] + j * j % MOD) % MOD;
            cnt[y]++;
        }
    }
    rep(y, 1, nn) {
        score[y] = (cnt[y] * sum1 % MOD + (iss[y] + jss[y]) * sum2 % MOD) % MOD;
        score[y] = ((score[y] - 2 * (is[y] * sum3 + js[y] * sum4)) % MOD + MOD) % MOD;
        score[y] = score[y] * invmod(cnt[y] * sum2 % MOD) % MOD;
        sum1 = (sum1 + cnt[y] * score[y] % MOD + iss[y] + jss[y]) % MOD;
        sum2 = (sum2 + cnt[y]) % MOD;
        sum3 = (sum3 + is[y]) % MOD;
        sum4 = (sum4 + js[y]) % MOD;
    }
    int num = 0, den = 0;
    rep(i, 1, n) {
        rep(j, 1, m) {
            if(a[i][j] < a[si][sj]) {
                den++;
                int di = i - si, dj = j - sj;
                num = (num + di * di % MOD + dj * dj % MOD + score[a[i][j]]) % MOD;
            }
        }
    }
    int ans = num * invmod(den) % MOD;
    printf("%d\n", ans);
    return 0;
}
