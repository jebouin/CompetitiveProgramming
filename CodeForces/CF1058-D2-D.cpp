/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Make a triangle with vertices (0, 0), (x, 0), (0, y).
 *          - If 2nm is not divisible by k, there is no solution.
 *          - If k is even, divide it by 2, a solution is x = n / gcd(n, k) and y = m * gcd(n, k) / k;
 *          - If k is odd, multiply one of the coordinates by 2 instead.
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    int z = 2 * n * m;
    if(z % k) {
        cout << "NO" << endl;
        return 0;
    }
    int x, y;
    if(k & 1) {
        int g = __gcd(n, k);
        x = n / g;
        y = m * g / k;
        if(x < n) {
            x *= 2;
        } else {
            y *= 2;
        }
    } else {
        k /= 2;
        int g = __gcd(n, k);
        x = n / g;
        y = m * g / k;
    }
    cout << "YES" << endl;
    cout << "0 0" << endl;
    cout << x << " 0" << endl;
    cout << "0 " << y << endl;
    return 0;
}
