/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - This is the classical largest rectangle in histogram problem.
 *          - Use a stack of pair (left, height) of each rectangle candidate, keep it sorted by left and height.
 *          - To process the building at index i, remove every pair that have a height at most aᵢ and consider 
 *            rectangles of width i - left and height for every removed pair.
 *          - If the last pair had height = aᵢ, add it back to the stack. Else, add (i, aᵢ) to the stack as new
 *            rectangle candidate.
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
typedef long long ll;
using namespace std;

const int N = 111111;
int a[N];

class BuildingAdvertise {
    public:
    ll getMaxArea(vector<int> h, int n) {
        int j = 0, m = sz(h);
        rep(i, 0, n - 1) {
            a[i + 1] = h[j];
            int s = (j + 1) % m;
            h[j] = ((h[j] ^ h[s]) + 13) % 835454957;
            j = s;
        }
        stack<pair<int, int> > st;
        a[++n] = -1;
        ll ans = 0;
        rep(i, 1, n) {
            int j = i;
            while(sz(st) && st.top().se >= a[i]) {
                j = st.top().fi;
                ll dx = i - j;
                ll dy = st.top().se;
                ans = max(ans, dx * dy);
                st.pop();
            }
            st.push(make_pair(j, a[i]));
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    BuildingAdvertise test;
    vector<int> v;
    v.pb(3);
    v.pb(6);
    v.pb(5);
    v.pb(6);
    v.pb(2);
    v.pb(4);
    cout << test.getMaxArea(v, 6) << endl;
    return 0;
}
