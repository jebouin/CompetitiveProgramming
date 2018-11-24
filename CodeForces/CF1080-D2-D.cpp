/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Iterate over the answer (the log2 of the length of the lower left square).
 *          - For each value of ans, calculate the minimum and maximum number of splits it is possible to make
 *            to get this answer. If k is in the interval, the answer is YES and we print the answer.
 *          - The minimum value is obtained when only the path is splitted. We can try splitting only along the
 *            left edge and the top edge, yielding 2^n - n - 1 splits for n iterations.
 *          - The maximum value is obtained when every square is of size at most 2 ^ ans, with squares not along
 *            the path splitted to size 1. Let c be the number of splits possible of a square of size ans. 
 *            c = (4^n - 1) / 3. The number of maximum splits is c * (2^(n-ans))².
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

int cuts(int n) {
    if(2 * n >= 62) return -1;
    return ((1LL << (2 * n)) - 1) / 3;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        bool ok = false;
        int ans;
        for(ans = n - 1; ans >= 0; ans--) {
            int di = n - ans;
            if(2 * di >= 62) break;
            int sq = (1 << di) - 1;
            sq *= sq;
            int oc = cuts(ans);
            if(oc == -1) {
                ok = true;
                break;
            }
            int add = oc * sq;
            if(sq > 0 && add / sq != oc) {
                ok = true;
                break;
            }
            int mini = (1 << (di + 1)) - n + ans - 2;
            int maxi = cuts(di) + add;
            if(k >= mini && k <= maxi) {
                ok = true;
                break;
            }
        }
        if(ok) {
            cout << "YES " << ans << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
