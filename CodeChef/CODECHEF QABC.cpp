/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - If b₁ is smaller than a₁, there is no solution.
 *          - Else, we have to apply the operation to index 1 b₁ - a₁ times and update the array.
 *          - Move to next element and repeat until the end of the array. Don't forget to check the indices n and
 *            n - 1.
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
int a[N];
int n, t;

void solve() {
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
    }
    bool ok = true;
    rep(i, 1, n) {
        int x;
        cin >> x;
        if(ok) {
            if(x < a[i]) {
                ok = false;
            } else if(x > a[i]) {
                if(i <= n - 2) {
                    int k = x - a[i];
                    a[i] += k;
                    a[i + 1] += 2 * k;
                    a[i + 2] += 3 * k;
                } else {
                    ok = false;
                }
            }
        }
    }
    cout << (ok ? "TAK" : "NIE") << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
