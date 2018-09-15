/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The game has less than n² states, each state can be written as (i, j) where i is the number of
 *            digits deleted from the front and j is the number of digits deleted from the back.
 *          - The transitions are (i, j) -> {(i + 1, j), (i, j + 1)}
 *          - Calculate the grundy number of every state, the answer is Alice iff gr[0][0] is nonzero.
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

const int N = 20;
bool pr[N][N];
int gr[N][N];
int n;

bool isp(int x) {
    if(x < 2) return false;
    if(x == 2) return true;
    if(x == 3) return true;
    if(x % 2 == 0) return false;
    for(int d = 3; d * d <= x; d += 2) {
        if(x % d == 0) return false;
    }
    return true;
}

bool isp(const string& s) {
    int x = 0;
    rep(i, 0, sz(s) - 1) {
        x = x * 10 + s[i] - '0';
    }
    return isp(x);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        n = sz(s);
        rep(i, 0, sz(s)) {
            fill(pr[i], pr[i] + n, false);
            rep(j, 0, sz(s)) {
                if(i + j >= sz(s)) continue;
                int len = sz(s) - i - j;
                string ss = s.substr(i, len);
                pr[i][j] = isp(ss);
            }
        }
        rrep(i, 0, n - 1) {
            fill(gr[i], gr[i] + n, 0);
            rrep(j, 0, n - 1) {
                if(i + j >= n - 1) continue;
                if(pr[i + 1][j] && pr[i][j + 1]) {
                    gr[i][j] = 0;
                } else if(pr[i + 1][j]) {
                    gr[i][j] = gr[i][j + 1] == 0 ? 1 : 0;
                } else if(pr[i][j + 1]) {
                    gr[i][j] = gr[i + 1][j] == 0 ? 1 : 0;
                } else {
                    bool h0 = false, h1 = false;
                    if(i < n - 1) {
                        if(gr[i + 1][j] == 0) h0 = true;
                        if(gr[i + 1][j] == 1) h1 = true;
                    }
                    if(j < n - 1) {
                        if(gr[i][j + 1] == 0) h0 = true;
                        if(gr[i][j + 1] == 1) h1 = true;
                    }
                    gr[i][j] = !h0 ? 0 : (!h1 ? 1 : 2);
                }
            }
        }
        cout << (gr[0][0] ? "Alice" : "Bob") << endl;
    }
    return 0;
}
