/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Use prime sieve to precalculate all primes up to 1e6.
 *          - Pair the smallest prime with the greatest, the second smallest with the second greatest, etc...
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

const int N = 1111111;
bool isp[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fill(isp + 2, isp + N, true);
    rep(i, 2, N - 1) {
        if(isp[i]) {
            for(int j = 2 * i; j < N; j += i) {
                isp[j] = false;
            }
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int l, r;
        cin >> l >> r;
        vector<int> pr;
        vector<pair<int, int> > ans;
        rep(i, l, r) {
            if(isp[i]) {
                pr.pb(i);
            }
        }
        rep(i, 0, sz(pr) / 2 - 1) {
            ans.pb(make_pair(pr[i], pr[sz(pr) - i - 1]));
        }
        cout << sz(ans) << endl;
        rall(p, ans) {
            cout << p.fi << " " << p.se << endl;
        }
    }
    return 0;
}
