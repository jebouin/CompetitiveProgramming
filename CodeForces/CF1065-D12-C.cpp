/*
 *  Author: Jeremy Bouin
 *  
 *  Idea:
 *          - Sort the building by descending height, and group the ones that have the same height.
 *          - Since the maximum height of a building is at most 2e5, we can iterate over the heightf and greedily
 *            add the number of buildings so far to the current slice.
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

const int N = 222222;
int a[N];
int n, k;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d %d", &n, &k);
    rep(i, 1, n) {
        scanf("%d", a + i);
    }
    sort(a + 1, a + n + 1, std::greater<int>());
    vector<pair<int, int> > v;
    rep(i, 1, n) {
        if(sz(v) == 0 || v.back().fi != a[i]) {
            v.pb(make_pair(a[i], 1));
        } else {
            v.back().se++;
        }
    }
    if(sz(v) == 1) {
        printf("0\n");
        return 0;
    }
    int ans = 1, cur = 0, s = 0;
    rep(i, 0, sz(v) - 2) {
        s += v[i].se;
        while(v[i].fi > v[i + 1].fi) {
            v[i].fi--;
            cur += s;
            if(cur > k) {
                cur = s;
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
