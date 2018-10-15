/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let g[i][j][k] be the probability that pᵢ is greater than pⱼ after k steps of the program.
 *          - On each swap of a and b with probability 1/2, we need to update the values of g:
 *              - g[i][j][k] <- g[i][j][k - 1] if none of i and j are swapped elements.
 *              - g[a][b][k] <- 1/2
 *              - g[i][a][k], g[i][b] <- (g[i][a][k - 1] + g[i][b][k - 1]) / 2
 *          - The answer is the sum for i < j of g[i][j][m].
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

const int N = 1111;
int p[N];
double g[N][N], tmp[N];
int n, m;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    rep(i, 1, n) {
        cin >> p[i];
    }
    rep(i, 1, n) {
        rep(j, 1, n) {
            g[i][j] = p[i] > p[j] ? 1 : 0;
        }
    }
    while(m--) {
        int a, b;
        cin >> a >> b;
        g[a][b] = .5;
        g[b][a] = .5;
        rep(i, 1, n) {
            tmp[i] = g[i][a];
            if(i != a && i != b) {
                tmp[i] = .5 * g[i][a] + .5 * g[i][b];
            }
        }
        rep(i, 1, n) {
            if(i != a && i != b) {
                g[i][a] = tmp[i];
                g[i][b] = tmp[i];
                g[a][i] = 1. - g[i][a];
                g[b][i] = 1. - g[i][b];
            }
        }
    }
    double ans = 0;
    rep(i, 1, n) {
        rep(j, i + 1, n) {
            ans += g[i][j];
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}
