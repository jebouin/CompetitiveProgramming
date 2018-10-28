/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Try every value of k, time complexity: O(n²).
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
int a[N], d[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        d[i] = a[i] - a[i - 1];
    }
    vector<int> ans;
    rep(x, 1, n) {
        bool ok = true;
        rep(i, 1, n) {
            int ii = (i - 1) % x + 1;
            if(d[i] != d[ii]) {
                ok = false;
            }
        }
        if(ok) {
            ans.pb(x);
        }
    }
    cout << sz(ans) << endl;
    rall(x, ans) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
