/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - If m = 1, the answer is n(n+1)/2.
 *          - If m > 1, count the number of subarrays of the first array that appear in every other array.
 *          - To do so, iterate over every element of the first array and store for the other arrays the
 *            number of consecutive elements so far.
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

const int N = 111111, M = 11;
int a[M][N], cnt[M], pp[N], pos[M][N];
int n, m;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d %d", &n, &m);
    rep(i, 1, m) {
        rep(j, 1, n) {
            scanf("%d", &(a[i][j]));
            pos[i][a[i][j]] = j;
        }
    }
    int ans = 0;
    if(m == 1) {
        ans = n * (n + 1) / 2;
    } else {
        rep(i, 1, n) {
            int cur = a[1][i];
            int mini = i;
            rep(j, 2, m) {
                if(pp[j] && pp[j] != pos[j][cur] - 1) {
                    cnt[j] = 1;
                } else {
                    cnt[j]++;
                }
                pp[j] = pos[j][cur];
                mini = min(mini, cnt[j]);
            }
            ans += mini;
        }
    }
    printf(LL, ans);
    printf("\n");
    return 0;
}
