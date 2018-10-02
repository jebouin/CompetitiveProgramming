/*
 *  Author: Jeremy Bouin
 *  
 *  Idea:
 *          - The k-th power of the adjacency matrix A gives the number of paths of length k between every pair
 *            of vertices.
 *          - The number of cycles of length less than k is the trace of the matrix A + A^2 + ... + A^(k-1).
 *          - This solution runs in O(n³ log k) with a bigger constant, it uses a 2n * 2n block matrix B to 
 *            directly compute the sum of powers of A.
 *                ╭       ╮              ╭                                     ╮
 *                │ 1 | A │              │        1        │ A + A² + ... + Aⁿ │
 *          - B = │ ──┼── │         Bⁿ = │ ────────────────┼────────────────── │
 *                │ 0 │ A │              │        0        │        Aⁿ         │
 *                ╰       ╯              ╰                                     ╯
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
#define int long long
typedef long long ll;
using namespace std;

const int N = 100;

class TourCounting {
    private:
    int a[N][N], b[N][N], ans[N];
    int n;
    
    int trace(int a[N][N], int mod) {
        int ans = 0;
        rep(i, 0, n - 1) {
            ans = (ans + a[i][i]) % mod;
        }
        return ans;
    }

    void add(int a[N][N], int b[N][N], int ans[N][N], int mod) {
        int temp[N][N];
        rep(i, 0, n - 1) {
            rep(j, 0, n - 1) {
                temp[i][j] = a[i][j] + b[i][j];
                temp[i][j] %= mod;
            }
        }
        rep(i, 0, n - 1) {
            copy(temp[i], temp[i] + n, ans[i]);
        }
    }
    
    void mult(int a[N][N], int b[N][N], int ans[N][N], int mod) {
        int temp[N][N];
        rep(i, 0, 2 * n - 1) {
            rep(j, 0, 2 * n - 1) {
                temp[i][j] = 0;
                rep(k, 0, 2 * n - 1) {
                    temp[i][j] += a[i][k] * b[k][j];
                    temp[i][j] %= mod;
                }
            }
        }
        rep(i, 0, 2 * n - 1) {
            copy(temp[i], temp[i] + 2 * n, ans[i]);
        }
    }

    void power(int a[N][N], int k, int ans[N][N], int mod) {
        int temp[N][N], x[N][N];
        rep(i, 0, 2 * n - 1) {
            rep(j, 0, 2 * n - 1) {
                temp[i][j] = i == j;
                x[i][j] = a[i][j];
            }
        }
        while(k) {
            if(k & 1) {
                mult(temp, x, temp, mod);
            }
            mult(x, x, x, mod);
            k >>= 1;
        }
        rep(i, 0, 2 * n - 1) {
            copy(temp[i], temp[i] + 2 * n, ans[i]);
        }
    }

    public:
    int countTours(vector<string> g, int k, int m) {
        n = sz(g[0]);
        rep(i, 0, n - 1) {
            rep(j, 0, n - 1) {
                a[i][j] = g[i][j] == 'Y';
                b[i][j] = i == j;
                b[n + i][j] = 0;
                b[i][n + j] = a[i][j];
                b[n + i][n + j] = a[i][j];
            }
        }
        power(b, k - 1, b, m);
        int ans = 0;
        rep(i, 0, n - 1) {
            ans = (ans + b[i][n + i]) % m;
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<string> v;
    v.pb("NYYY");
    v.pb("YNYY");
    v.pb("YYNY");
    v.pb("YNYN");
    TourCounting test;
    cout << test.countTours(v, 1000, 10000) << endl;
    return 0;
}
