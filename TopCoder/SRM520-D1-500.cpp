/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let's order the competitors from worst to best.
 *          - Let dp[i][s] be the number of scoreboards with the i first competitors and a score of s for the
 *            ith one. There are at most 200000 values for s.
 *          - The score of the ith competitor is greater than the i-1th so dp[i][s] is the sum of dp[i - 1][t]
 *            for every t smaller than s.
 *          - For every s, we also need to count the number of ways to get the score s with the number of problem
 *            solved. Ans multiply dp[i][s] by this value. Let k be the number of problems solved.
 *            - If k <= 1, the answer is 1.
 *            - If k = 2, let a and b be the maximum value of the solved problems. We need to find the number 
 *              pairs (x, y) that satisfy 1 <= x,y
 *                                        x <= a
 *                                        y <= b
 *                                        x + y = s
 *              Let f(a, b, s) be the answer, we have f(a, b, s) = max(0, min(a, s-1) - max(1, s-b) + 1).
 *            - If k = 3, let c be the maximum value of the third solved problem. The answer is the sum of
 *              f(a, b, s - z) for every z between 1 and c. To compute this for every s, initialize the answer
 *              to 0 and for every s, add f(a, b, s - 1) - f(a, b, s - c - 1) to the answer.
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
#define int long long
typedef long long ll;
using namespace std;

const int N = 22, S = 200002;
int dp[N][S], sum[N][S];
int n;

class SRMIntermissionPhase {
    private:
    inline int cnt2(int a, int b, int s) {
        return max(0LL, min(a, s - 1) - max(1LL, s - b) + 1);
    }
    public:
    int countWays(vector<int> pts, vector<string> descr) {
        n = sz(descr);
        rep(i, 1, n) {
            int mini = 0, maxi = 0;
            string ds = descr[n - i];
            rep(j, 0, 2) {
                if(descr[n - i][j] == 'Y') {
                    mini++;
                    maxi += pts[j];
                }
            }
            int pos = 0, a, b, c;
            if(mini <= 1) {

            } else if(mini == 2) {
                if(ds[0] == 'Y') {
                    a = pts[0];
                    b = ds[1] == 'Y' ? pts[1] : pts[2];
                } else {
                    a = pts[1];
                    b = pts[2];
                }
            } else if(mini == 3) {
                a = pts[0]; b = pts[1]; c = pts[2];
            }
            rep(s, 0, S - 1) {
                if(mini <= 1) {
                    pos = 1;
                } else if(mini == 2) {
                    pos = cnt2(a, b, s);
                } else if(mini == 3) {
                    pos += cnt2(a, b, s - 1);
                    pos -= cnt2(a, b, s - c - 1);
                    pos = (pos % MOD + MOD) % MOD;
                }
                if(s >= mini && s <= maxi) {
                    if(i == 1) {
                        dp[i][s] = 1;
                    } else if(s) {
                        dp[i][s] = sum[i - 1][s - 1];
                    }
                }
                dp[i][s] *= pos;
                dp[i][s] %= MOD;
                sum[i][s] = dp[i][s];
                if(s) {
                    sum[i][s] = (sum[i][s] + sum[i][s - 1]) % MOD;
                }
            }
        }
        return sum[n][S - 1];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    SRMIntermissionPhase test;
    vector<int> pts;
    vector<string> descr;
    pts.pb(25600);
    pts.pb(51200);
    pts.pb(102400);
    descr.pb("NYY");
    descr.pb("YNY");
    descr.pb("YYY");
    descr.pb("YNN");
    descr.pb("YYN");
    descr.pb("NNY");
    descr.pb("NYN");
    descr.pb("NNN");
    cout << test.countWays(pts, descr) << endl;
    return 0;
}
