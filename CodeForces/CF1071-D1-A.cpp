/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - It is optimal to only read the n + m first notes.
 *          - Let x be n + m, choose the biggest x such that x(x+1)/2 <= a + b.
 *          - Iterate over the notes from x to 1 and greedily add a note to the first day if possible, else add
 *            it to the second day.
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
    int a, b;
    cin >> a >> b;
    vector<int> x, y;
    int cur = 0;
    bool sw = false;
    if(a < b) {
        sw = true;
        swap(a, b);
    }
    int n = 0;
    while(n * (n + 1) / 2 <= a + b) {
        n++;
    }
    n--;
    int sa = 0, sb = 0;
    rrep(i, 1, n) {
        if(sa + i <= a) {
            sa += i;
            x.pb(i);
        } else {
            y.pb(i);
        }
    }
    if(sw) swap(x, y);
    cout << sz(x) << endl;
    rall(i, x) {
        cout << i << " ";
    }
    cout << endl;
    cout << sz(y) << endl;
    rall(i, y) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
