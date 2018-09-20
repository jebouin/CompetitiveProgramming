/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Multiple cases to handle here. First, check if the password is already correct.
 *          - If not, try to place a digit or a lowercase/uppercase letter and check again.
 *          - If it's still not correct, try to place a combination of two symbols and check again.
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

bool check(const string& s) {
    bool nl = false, nu = false, nd = false;
    rall(c, s) {
        if(isdigit(c)) {
            nd = true;
        } else if(toupper(c) == c) {
            nu = true;
        } else {
            nl = true;
        }
    }
    return nl && nu && nd;
}

void solve() {
    string s;
    cin >> s;
    if(check(s)) {
        cout << s << endl;
        return;
    }
    rep(i, 0, sz(s) - 1) {
        string t(s);
        t[i] = '0';
        if(check(t)) {
            cout << t << endl;
            return;
        }
        t = s;
        t[i] = 'a';
        if(check(t)) {
            cout << t << endl;
            return;
        }
        t = s;
        t[i] = 'A';
        if(check(t)) {
            cout << t << endl;
            return;
        }
    }
    rep(i, 0, sz(s) - 2) {
        string t(s);
        t[i] = '0';
        t[i + 1] = 'A';
        if(check(t)) {
            cout << t << endl;
            return;
        }
        t = s;
        t[i] = 'a';
        t[i + 1] = 'A';
        if(check(t)) {
            cout << t << endl;
            return;
        }
        t = s;
        t[i] = 'a';
        t[i + 1] = '0';
        if(check(t)) {
            cout << t << endl;
            return;
        }
    }
    exit(1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
