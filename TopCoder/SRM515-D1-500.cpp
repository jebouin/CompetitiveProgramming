/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - For every customer i, calculate for every probability p_j the probability p'_j that he comes to the
 *            shop after not coming before t_j. (conditional probability)
 *          - Use dp with the following states: (t, s, m) corresponds to the answer starting from time t with
 *            s swords left and mask m corresponding to the customers who already came to the shop.
 *          - As there are too many possible states (about 10 billion), only put in the mask the customers who
 *            appear at least twice.
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

const static int T = 25, S = 25;
double p[T], c[T];
int ind[T], cnt[T];
double dp[T][S][1 << 12];

class NewItemShop {
    double solve(int t, int s, int m) {
        if(dp[t][s][m] > -1e6) {
            return dp[t][s][m];
        }
        if(t == 24 || s == 0) {
            return 0;
        }
        if(ind[t]) {
            int ma = ind[t] > 0 ? 1 << (ind[t] - 1) : 0;
            if(m & ma) {
                dp[t][s][m] = solve(t + 1, s, m);
            } else {
                dp[t][s][m] = (1. - p[t]) * solve(t + 1, s, m);
                dp[t][s][m] += p[t] * max(solve(t + 1, s, m | ma), c[t] + solve(t + 1, s - 1, m | ma));
            }
        } else {
            dp[t][s][m] = solve(t + 1, s, m);
        }
        return dp[t][s][m];
    }

    int readInt(string& s) {
        int x = 0, i = 0;
        while(s[i] != ',') {
            x = x * 10 + s[i++] - '0';
        }
        s = s.substr(i + 1);
        return x;
    }

    public:
    double getMaximum(int swords, vector<string> customers) {
        int n = sz(customers);
        fill(ind, ind + 24, 0);
        rep(t, 0, 24) {
            rep(s, 0, 24) {
                fill(dp[t][s], dp[t][s] + (1 << 12), -1e6);
            }
        }
        int i1 = -1, i2 = 1;
        rep(i, 1, n) {
            string cs(customers[i - 1]), ev;
            stringstream ss(cs);
            vector<string> v;
            while(getline(ss, ev, ' ')) {
                v.pb(ev);
            }
            int ii = sz(v) > 1 ? i2++ : i1--;
            rall(ev, v) {
                ev += ',';
                int ti = readInt(ev);
                int ci = readInt(ev);
                int pi = readInt(ev);
                ind[ti] = ii;
                p[ti] = pi / 1e2;
                c[ti] = ci;
            }
        }
        rep(i, i1, i2) {
            double sum = 0;
            rep(t, 0, 23) {
                if(ind[t] != i) continue;
                double d = sum;
                sum += p[t];
                p[t] = p[t] / (1 - d);
            }
        }
        return solve(0, swords, 0);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    NewItemShop test;
    vector<string> v;
    v.pb("0,90,25 2,90,25 4,90,25 6,90,25");
    v.pb("7,100,80");
    v.pb("1,90,90 13,100,42");
    cout << test.getMaximum(1, v) << endl;
    return 0;
}
