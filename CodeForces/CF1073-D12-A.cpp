/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Brute force every substring and use prefix sums on the frequency of each letter to check in
 *            constant time.
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
int cnt[N][26];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    string s;
    cin >> s;
    rep(i, 1, n) {
        rep(j, 0, 25) {
            cnt[i][j] = cnt[i - 1][j];
        }
        cnt[i][s[i - 1] - 'a']++;
    }
    rep(i, 1, n) {
        rep(j, i, n) {
            bool ok = true;
            rep(k, 0, 25) {
                int cur = cnt[j][k] - cnt[i - 1][k];
                if(cur * 2 > j - i + 1) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                cout << "YES" << endl;
                cout << s.substr(i - 1, j - i + 1) << endl;
                return 0;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}
