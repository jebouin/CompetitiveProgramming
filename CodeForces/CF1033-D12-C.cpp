/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - For each value in the array in descending order, find who wins the game starting with this value.
 *          - Alice wins iff she can reach at least one value that makes her lose.
 *          - The number of values to test is the sum for every x of n / x which is O(n log n).
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

const int N = 111111;
int a[N], pos[N];
int ans[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    ans[pos[n]] = -1;
    rrep(x, 1, n - 1) {
        int i = pos[x];
        int j = i - x;
        bool wins = false;
        while(j >= 1) {
            if(ans[j] == -1) {
                wins = true;
            }
            j -= x;
        }
        j = i + x;
        while(j <= n) {
            if(ans[j] == -1) {
                wins = true;
            }
            j += x;
        }
        ans[i] = wins ? 1 : -1;
    }
    rep(i, 1, n) {
        cout << (ans[i] == 1 ? 'A' : 'B');
    }
    cout << endl;
    return 0;
}
