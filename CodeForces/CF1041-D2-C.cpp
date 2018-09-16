/*
 *  Author: Jeremy Bouin
 *
 *  Idea:   - For every coffee break in ascending order, choose a day that doesn't have a coffee break in the last *            d minutes. Add a day to the answer if necessary.
 *          - Speed up the process with a priority queue.
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
int a[N], ord[N];
int n, m, d;

bool comp(const int& i, const int& j) {
    return a[i] < a[j];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf(LL, &n);
    scanf(LL, &m);
    scanf(LL, &d);
    rep(i, 1, n) {
        scanf(LL, a + i);
        ord[i] = i;
    }
    sort(ord + 1, ord + n + 1, comp);
    priority_queue<pair<int, int> > days;
    days.push(make_pair(1e10, 1));
    vector<int> v(n);
    rep(i, 1, n) {
        int x = a[ord[i]];
        pair<int, int> p = days.top();
        days.pop();
        int diff = x + p.fi - 1;
        if(diff >= d) {
            p.fi = -x;
            days.push(p);
            v[ord[i] - 1] = p.se;
        } else {
            days.push(p);
            days.push(make_pair(-x, sz(days) + 1));
            v[ord[i] - 1] = sz(days);
        }
    }
    printf("%d\n", sz(days));
    rall(x, v) {
        printf(LL, x);
        printf(" ");
    }
    printf("\n");
    return 0;
}
