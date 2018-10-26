/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - To build a partition of people in valid marriages, we can choose a subset of men and women who
 *            will represent their marriage and try to link the remaining people to them.
 *          - Try every subset of men and women, the answer is the minimum size for which it is possible to add
 *            everyone in a marriage.
 *          - There are at most 2^24 possibilities and the check is O(n+m) using bitmasks.
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

const int N = 13;
int mx[N], my[N];

class MarriageProblemRevised {
    private:
        int n, m;

    public:
        int neededMarriages(vector<string> pref) {
            n = sz(pref);
            m = sz(pref[0]);
            rep(i, 1, n) {
                rep(j, 1, m) {
                    mx[i] |= (1 << (j - 1)) * (pref[i - 1][j - 1] - '0');
                    my[j] |= (1 << (i - 1)) * (pref[i - 1][j - 1] - '0');
                }
            }
            rep(i, 1, n) {
                if(!mx[i]) {
                    return -1;
                }
            }
            rep(i, 1, m) {
                if(!my[i]) {
                    return -1;
                }
            }
            int ans = n + m;
            rep(ml, 0, (1 << n) - 1) {
                rep(mr, 0, (1 << m) - 1) {
                    int cm = mr;
                    rep(i, 1, n) {
                        if(ml & (1 << (i - 1))) {
                            cm |= mx[i];
                        }
                    }
                    if(cm != (1 << m) - 1) continue;
                    cm = ml;
                    rep(i, 1, m) {
                        if(mr & (1 << (i - 1))) {
                            cm |= my[i];
                        }
                    }
                    if(cm != (1 << n) - 1) continue;
                    ans = min(ans, (int)(pcnt(ml) + pcnt(mr)));
                }
            }
            return ans;
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    MarriageProblemRevised test;
    vector<string> in;
    in.pb("11101011");
    in.pb("00011110");
    in.pb("11100100");
    in.pb("01010000");
    in.pb("01000010");
    in.pb("10100011");
    in.pb("01110110");
    in.pb("10111111");
    cout << test.neededMarriages(in) << endl;
    return 0;
}
