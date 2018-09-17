/*
 *  Author: Jeremy Bouin
 *
 *  Idea:   
 *          - For each set of vitamin, compute its minimum price.
 *          - As there are only 3 vitamins, try every combination of vitamin masks.
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

const int N = 1111, INF = 1e8;
int n, a = INF, b = INF, c = INF, ab = INF, ac = INF, bc = INF, abc = INF;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        string s;
        int w;
        cin >> w >> s;
        sort(rng(s));
        if(s == "A") {
            a = min(a, w);
        } else if(s == "B") {
            b = min(b, w);
        } else if(s == "C") {
            c = min(c, w);
        } else if(s == "AB") {
            ab = min(ab, w);
        } else if(s == "BC") {
            bc = min(bc, w);
        } else if(s == "AC") {
            ac = min(ac, w);
        } else {
            abc = min(abc, w);
        }
    }
    a = min(a, min(ab, ac));
    b = min(b, min(ab, bc));
    c = min(c, min(bc, ac));
    int ans = min(abc, a + b + c);
    ans = min(ans, ab + c);
    ans = min(ans, ac + b);
    ans = min(ans, bc + a);
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}
