/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Count the votes with increasing values of k until Awruk wins the election.
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

const int N = 111;
int a[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int k = 0;
    rep(i, 1, n) {
        cin >> a[i];
        k = max(k, a[i]);
    }
    for(int l = k; l <= 1000; l++) {
        int ev = 0, av = 0;
        rep(i, 1, n) {
            ev += a[i];
            av += l - a[i];
        }
        if(av > ev) {
            cout << l << endl;
            return 0;
        }
    }
    return 0;
}
