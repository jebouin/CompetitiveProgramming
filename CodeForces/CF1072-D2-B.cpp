/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Use dynamic programming: dp[i][x] is true iff it is possible to find a prefix of t of length i that
 *            ends with x. If it is possible, keep track of the previous chosen element.
 *          - When a solution is found, follow the chosen elements from n to 1 to fetch a solution.
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
int a[N], b[N];
bool dp[N][4];
int pr[N][4];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n - 1) {
        cin >> a[i];
    }
    rep(i, 1, n - 1) {
        cin >> b[i];
    }
    fill(dp[1], dp[1] + 4, true);
    rep(i, 2, n) {
        rep(x, 0, 3) {
            rep(y, 0, 3) {
                if((x | y) == a[i - 1] && (x & y) == b[i - 1]) {
                    if(dp[i - 1][x]) {
                        dp[i][y] = true;
                        pr[i][y] = x;
                    }
                }
            }
        }
    }
    rep(i, 0, 3) {
        if(dp[n][i]) {
            cout << "YES" << endl;
            vector<int> ans(1, i);
            int x = i;
            rrep(j, 2, n) {
                x = pr[j][x];
                ans.pb(x);
            }
            reverse(rng(ans));
            rall(x, ans) {
                cout << x << " ";
            }
            cout << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
