/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let's iterate over the house i from n to 1 and only consider building roads from i to a house
 *            smaller than i. Let mask be the number such that its j-th bit is the parity of the number of roads
 *            that share house i - j as an endpoint.
 *          - Let dp[i][j][h][mask] be the number of ways to build roads if j roads are already built using 
 *            houses from i to n, the given mask is mask and we are about to choose if we link house i and 
 *            i - h - 1.
 *          - If h = k, we can't change the parity of house i - k anymore and if it's even, we have
 *            dp[i][j][k][mask] = dp[i+1][j][0][2*mask] (go to the next house, update the mask and start
 *            by considering the house directly to the left).
 *          - If h < k, we either build a road to house i - h - 1 or we don't.
 *            - If we don't, we simply consider the next house to link to i: add dp[i][j][h+1][mask].
 *            - If we do, the parity of house i and i - h - 1 will change: add dp[i][j+1][h][new_mask] where
 *              new_mask is mask where the parity of the 0-th and h + 1-th bit are changed.
 *              Don't increment h since we may build multiple roads to the house.
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
typedef long long ll;
using namespace std;

const int N = 33, K = 9;
ll dp[2][N][N][1 << K];

class DengklekBuildingRoads {
    private:

    public:
    int numWays(int n, int m, int k) {
        rep(i, 0, 1) {
            rep(j, 0, N - 1) {
                rep(h, 0, N - 1) {
                    fill(dp[i][j][h], dp[i][j][h] + (1 << K), 0);
                }
            }
        }
        dp[1][m][0][0] = 1;
        rrep(i, 1, n) {
            int ii = n - i & 1;
            rrep(j, 0, m) {
                rep(mask, 0, (1 << (k + 1)) - 1) {
                    if(!(mask & (1 << k))) {
                        dp[ii][j][k][mask] = dp[ii ^ 1][j][0][mask << 1];
                    }
                }
                rrep(h, 0, k - 1) {
                    rep(mask, 0, (1 << (k + 1)) - 1) {
                        dp[ii][j][h][mask] = dp[ii][j][h + 1][mask];
                        if(i - h - 1 >= 1 && j + 1 <= m) {
                            dp[ii][j][h][mask] += dp[ii][j + 1][h][mask ^ 1 ^ (1 << (h + 1))];
                            dp[ii][j][h][mask] %= MOD;
                        }
                    }
                }
            }
        }
        return dp[1][0][0][0];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    DengklekBuildingRoads test;
    cout << test.numWays(3, 4, 1) << endl;
    cout << test.numWays(4, 3, 3) << endl;
    cout << test.numWays(2, 1, 1) << endl;
    cout << test.numWays(5, 0, 3) << endl;
    cout << test.numWays(10, 20, 5) << endl;
    cout << test.numWays(30, 30, 8) << endl;
    cout << test.numWays(4, 3, 8) << endl;
    cout << test.numWays(4, 2, 8) << endl;
    cout << test.numWays(4, 1, 8) << endl;
    cout << test.numWays(4, 0, 8) << endl;
    cout << test.numWays(1, 0, 8) << endl;
    cout << test.numWays(1, 30, 8) << endl;
    cout << test.numWays(2, 30, 8) << endl;
    return 0;
}
