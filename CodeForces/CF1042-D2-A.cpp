/*
 *  Author: Jeremy Bouin
 *
 *  Idea: 
 *          - The maximum answer is max(a_i) + m
 *          - To get the minimum answer, greedily assign each person to the bench with minimum number of people.
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

const int N = 111;
int a[N];
int n, m;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int maxi = 0;
    rep(i, 1, n) {
        cin >> a[i];
        maxi = max(maxi, a[i] + m);
    }
    rep(i, 1, m) {
        int b = 1;
        rep(j, 2, n) {
            if(a[b] > a[j]) {
                b = j;
            }
        }
        a[b]++;
    }
    int mini = 0;
    rep(i, 1, n) {
        mini = max(mini, a[i]);
    }
    cout << mini << " " << maxi << endl;
    return 0;
}
