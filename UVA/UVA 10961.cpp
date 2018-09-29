/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Easy implementation problem, store every position between stops and compare them.
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

void moveTo(vector<pair<int, int> >& path, const int& x, const int& y) {
    while(path.back().fi < x) {
        path.pb(make_pair(path.back().fi + 1, y));
    }
    while(path.back().fi > x) {
        path.pb(make_pair(path.back().fi - 1, y));
    }
    while(path.back().se < y) {
        path.pb(make_pair(x, path.back().se + 1));
    }
    while(path.back().se > y) {
        path.pb(make_pair(x, path.back().se - 1));
    }
}

void solve(int t) {
    int x, y, n;
    vector<pair<int, int> > dg, lp;
    cin >> x >> y;
    dg.pb(make_pair(x, y));
    cin >> x >> y;
    lp.pb(make_pair(x, y));
    cin >> n;
    rep(i, 1, n) {
        cin >> x >> y;
        moveTo(lp, x, y);
    }
    cin >> n;
    rep(i, 1, n) {
        cin >> x >> y;
        moveTo(dg, x, y);
    }
    bool safe = true;
    rep(i, 0, min(sz(dg), sz(lp)) - 1) {
        if(i < sz(lp) - 1 && dg[i] == lp[i]) {
            safe = false;
            break;
        }
    }
    cout << (safe ? "Yes" : "No") << endl;
    if(t) {
        cout << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        solve(t);
    }
    return 0;
}
