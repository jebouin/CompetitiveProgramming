/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Find which positions in the array have the largest value. Such positions have l = 0 and r = 0.
 *          - Update the l and r arrays as if we removed the biggest values and repeat the first step to find
 *            which positions have the second largest value and so on.
 *          - Use prefix sums to speed up the process to O(n²).
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
int l[N], r[N], a[N], rem[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> l[i];
    }
    rep(i, 1, n) {
        cin >> r[i];
    }
    rrep(x, 1, n) {
        int cnt = 0;
        fill(rem + 1, rem + n + 1, 0);
        rep(i, 1, n) {
            if(a[i]) continue;
            if(l[i] == 0 && r[i] == 0) {
                cnt++;
                a[i] = x;
                rem[i]++;
            }
        }
        int sr = 0;
        rep(i, 1, n) {
            sr += rem[i];
            if(!a[i]) {
                l[i] -= sr;
            }
        }
        sr = 0;
        rrep(i, 1, n) {
            sr += rem[i];
            if(!a[i]) {
                r[i] -= sr;
            }
        }
    }
    rep(i, 1, n) {
        if(!a[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    rep(i, 1, n) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
