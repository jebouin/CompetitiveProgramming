/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Start from the least significant digit. 
 *          - For each digit d, maximise the sum of two digits that sum to d modulo 10. If d < 9, the answer is 
 *            d + 10 - c where c is the carry (0 or 1) from the previous operation. If d = 9, the answer is
 *            9 if c = 0 and 18 if c = 1.
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
    int n, ans = 0;
    cin >> n;
    while(n % 10 == 9) {
        ans += 9;
        n /= 10;
    }
    int k = 0;
    while(n) {
        ans += n % 10 + 10 * (n / 10 > 0);
        k++;
        n /= 10;
    }
    ans -= max(0LL, k - 1);
    cout << ans << endl;
    return 0;
}
