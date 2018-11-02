/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Use 2d prefix sums to check if a rectangle is free of any objects.
 *          - Time complexity: O(n²m²)
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

const int N = 33;
string grid[N];
int sum[N][N];
int n, m;

int getSum(int i, int j, int k, int l) {
    return sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    rep(i, 1, n) {
        string s;
        cin >> s;
        grid[i] = ' ' + s + ' ';
        rep(j, 1, m) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (grid[i][j] == '1');
        }
    }
    int ans = 0;
    rep(i, 1, n) {
        rep(j, 1, m) {
            rep(k, i, n) {
                rep(l, j, m) {
                    int di = k - i + 1;
                    int dj = l - j + 1;
                    int p = 2 * di + 2 * dj;
                    int out = getSum(i, j, k, l);
                    if(!out) {
                        ans = max(ans, p);
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
