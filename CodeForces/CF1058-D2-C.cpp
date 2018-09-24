/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The maximum possible sum is 900 so we can bruteforce on the sum of a segment.
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

int n;
string s;

bool solve(int l) {
    int sum = 0;
    int cnt = 0;
    rall(c, s) {
        sum += c - '0';
        if(sum > l) return false;
        if(sum == l) {
            sum = 0;
            cnt++;
        }
    }
    return sum == 0 && cnt > 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s;
    rep(l, 0, 900) {
        if(solve(l)) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
