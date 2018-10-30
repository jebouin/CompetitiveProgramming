/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Simulate the process from time s to 1. With t time left, each thief hires a new thief on every cell
 *            in a diamond shape of size t - 1 around his position.
 *          - To speed up the process, use 2d diagonal prefix sums.
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

const int N = 101;
ll g[N][N], th[2][N << 2][N << 2];
int n, m, s, pi, pj, nn, mm;

inline void addh(int i, int j, ll x, int k) {
    th[k][i][j] += x;
}

int solve() {
    scanf("%d %d %d %d %d", &n, &m, &s, &pi, &pj);
    int off = N;
    nn = n + 2 * off;
    mm = m + 2 * off;
    rep(i, 1, n) {
        rep(j, 1, m) {
            scanf(LL, &(g[i][j]));
        }
    }
    int k = 0;
    rep(i, 1, nn) {
        fill(th[1][i] + 1, th[1][i] + mm + 1, 0);
    }
    th[1][pi + off][pj + off] = 1;
    while((s--) > 1) {
        rep(i, 1, nn) {
            fill(th[k][i] + 1, th[k][i] + mm + 1, 0);
        }
        rep(i, off + 1, off + n) {
            rep(j, off + 1, off + m) {
                ll x = th[k ^ 1][i][j];
                addh(i, j - s + 1, x, k);
                addh(i, j - s, x, k);
                addh(i - s, j + 1, -x, k);
                addh(i - s - 1, j + 1, -x, k);
                addh(i + s, j + 1, -x, k);
                addh(i + s + 1, j + 1, -x, k);
                addh(i, j + s + 1, x, k);
                addh(i, j + s + 2, x, k);
            }
        }
        rep(d, 1, nn) {
            rep(j, 1, min(d, mm)) {
                int i = d - j + 1;
                addh(i, j, th[k][i + 1][j - 1], k);
            }
        }
        rep(d, 2, mm) {
            rep(j, d, min(mm, nn - 1 + d)) {
                int i = nn - j + d;
                addh(i, j, th[k][i + 1][j - 1], k);
            }
        }
        rep(d, 1, mm) {
            rep(j, d, min(mm, nn + d - 1)) {
                int i = j - d + 1;
                addh(i, j, th[k][i - 1][j - 1], k);
            }
        }
        rep(d, 2, nn) {
            rep(i, d, min(nn, mm + d - 1)) {
                int j = i - d + 1;
                addh(i, j, th[k][i - 1][j - 1], k);
            }
        }
        rep(i, 1, nn) {
            rep(j, 1, mm) {
                th[k][i][j] = (th[k][i][j] % MOD + MOD) % MOD;
            }
        }
        k ^= 1;
    }
    ll ans = 0;
    rep(i, 1, n) {
        rep(j, 1, m) {
            ans = (ans + th[k ^ 1][off + i][off + j] * g[i][j] % MOD) % MOD;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("treasures.in", "r", stdin);
    int t;
    scanf("%d", &t);
    rep(i, 1, t) {
        int ans = solve();
        printf("Case %d: %d\n", i, ans);
    }
    return 0;
}
