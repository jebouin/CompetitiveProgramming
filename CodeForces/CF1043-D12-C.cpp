/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Only reverse the substring of length i if the ith character of s is different than the next one.
 *          - That way, the final string will be of the form a..ab..b or b..ba..a.
 *          - Do a final swap if the string is of the second form.
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
bool a[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    n = sz(s);
    if(n == 1) {
        cout << 0 << endl;
        return 0;
    }
    s += ' ';
    rep(i, 1, n) {
        if(s[i - 1] != s[i]) {
            a[i] = true;
        }
        if(i == n) {
            string ss(s);
            a[i] = s[n - 1] == 'a';
        }
        if(a[i]) {
            reverse(s.begin(), s.begin() + i);
        }
    }
    rep(i, 1, n) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
