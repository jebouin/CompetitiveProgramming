/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The time by using the stairs is ts = t1 * |x - y|.
 *          - The time by using the elevator is te = t2 * (|z - x| + |x - y|) + 3 * t3.
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
    int x, y, z, t1, t2, t3;
    cin >> x >> y >> z >> t1 >> t2 >> t3;
    int ts = abs(x - y) * t1;
    int te = abs(z - x) * t2 + abs(x - y) * t2 + 3 * t3;
    cout << (te <= ts ? "YES" : "NO") << endl;
    return 0;
}
