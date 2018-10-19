/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The mex of the complete array will always be the biggest number plus one. Taking the mex of
 *            a subset means that we can have duplicates of previous numbers in the array.
 *          - A number appended to the array a is valid iff it is not greater than max(a) + 1.
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int cur = 0;
    rep(i, 1, n) {
        int x;
        cin >> x;
        if(x > cur) {
            cout << i << endl;
            return 0;
        }
        cur = max(cur, x + 1);
    }
    cout << -1 << endl;
    return 0;
}
