/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Store the position of every book in the stack and keep a pointer to the position in the stack.
 *          - When asked to retrieve a book, get its position in constant time and add all the books between the
 *            current position and the book position.
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

const int N = 222222;
int a[N], b[N], pos[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    rep(i, 1, n) {
        cin >> b[i];
    }
    int cur = 1;
    rep(i, 1, n) {
        int ne = pos[b[i]];
        int ans = 0;
        if(ne >= cur) {
            ans = ne - cur + 1;
            cur = ne + 1;
        }
        cout << ans << " ";
    }
    cout << endl;
    return 0;
}
