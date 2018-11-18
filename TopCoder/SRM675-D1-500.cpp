/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let m be 1e9 + 7. Divide the [0, m - 1] range in roughly √m blocks of size √m.
 *          - For each block, count the number of elements from the array contained in this block.
 *          - For each query q, find the block that contains the q-th element and iterate over the whole array
 *            again to find which term in this block is the q-th.
 *          - Only about 2√m ≈ 64000 integers are stored with this solution.
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

const int N = 32222;
int cnt[N], cntt[N];

class LimitedMemorySeries1 {
    public:
        ll getSum(int n, int x0, int a, int b, vector<int> query) {
            ll ans = 0;
            ll x = x0;
            rep(i, 1, n) {
                cnt[x / N]++;
                x = (a * x + b) % MOD;
            }
            rall(q, query) {
                int sum = 0, bl = -1;
                rep(i, 0, N - 1) {
                    sum += cnt[i];
                    if(sum >= q + 1) {
                        bl = i;
                        break;
                    }
                }
                fill(cntt, cntt + N, 0);
                int qq = q + 1 - sum + cnt[bl];
                x = x0;
                rep(i, 1, n) {
                    int cb = x / N;
                    if(cb == bl) {
                        cntt[x % N]++;
                    }
                    x = (a * x + b) % MOD;
                }
                rep(i, 0, N - 1) {
                    int ii = bl * N + i;
                    qq -= cntt[i];
                    if(qq <= 0) {
                        ans += ii;
                        break;
                    }
                }
            }
            return ans;
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    LimitedMemorySeries1 test;
    vector<int> qu;
    qu.pb(0);
    qu.pb(1);
    qu.pb(2);
    qu.pb(3);
    cout << test.getSum(5, 123456789, 987654321, 1000000006, qu) << endl;
    return 0;
}
