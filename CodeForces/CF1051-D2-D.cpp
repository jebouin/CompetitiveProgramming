/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Calculate for every i, k and mask m the number of ways to color the i first columns with k 
 *            connected components such as the i-th column is m.
 *          - There are 4 possibilities for every column, which means 16 transitions per column.
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

const int N = 1111;
int dp[N][N << 1][4];
int n, k;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    dp[1][1][0] = 1;
    dp[1][2][1] = 1;
    dp[1][2][2] = 1;
    dp[1][1][3] = 1;
    rep(i, 2, n) {
        rep(k, 1, 2 * n) {
            dp[i][k][0] = (dp[i - 1][k][0] + dp[i - 1][k][1] + dp[i - 1][k][2]) % MOD;
            dp[i][k][1] = dp[i - 1][k][1];
            dp[i][k][2] = dp[i - 1][k][2];
            dp[i][k][3] = (dp[i - 1][k][1] + dp[i - 1][k][2] + dp[i - 1][k][3]) % MOD;

            dp[i][k][0] = (dp[i][k][0] + dp[i - 1][k - 1][3]) % MOD;
            dp[i][k][1] = (dp[i][k][1] + dp[i - 1][k - 1][0] + dp[i - 1][k - 1][3]) % MOD;
            dp[i][k][2] = (dp[i][k][2] + dp[i - 1][k - 1][0] + dp[i - 1][k - 1][3]) % MOD;
            dp[i][k][3] = (dp[i][k][3] + dp[i - 1][k - 1][0]) % MOD;

            if(k > 1) {
                dp[i][k][1] = (dp[i][k][1] + dp[i - 1][k - 2][2]) % MOD;
                dp[i][k][2] = (dp[i][k][2] + dp[i - 1][k - 2][1]) % MOD;
            }
        }
    }
    int ans = 0;
    rep(i, 0, 3) {
        ans += dp[n][k][i];
    }
    ans %= MOD;
    cout << ans << endl;
    return 0;
}
