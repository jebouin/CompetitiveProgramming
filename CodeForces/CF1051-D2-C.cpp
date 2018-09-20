/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Calculate the frequency of every element of s.
 *          - If the frequency of an element is 1, it adds a nice number to a or b.
 *          - If it is 2, we add one element to a and the other to b, or both to a or b. Either way, it
 *            doesn't change the relative count of nice numbers.
 *          - If it is greater than two, we can add one nice number to a or b or do nothing.
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
int a[N], cnt[N];
bool ans[N];
set<int> st[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        int x;
        cin >> x;
        cnt[x]++;
        st[x].insert(i);
    }
    int x = 0, y = 0;
    rep(i, 1, 100) {
        if(cnt[i] == 1) {
            if(x > y) {
                y++;
                ans[*(st[i].begin())] = true;
                st[i].erase(st[i].begin());
            } else {
                x++;
                ans[*(st[i].begin())] = false;
                st[i].erase(st[i].begin());
            }
        }
    }
    rep(i, 1, 100) {
        if(cnt[i] > 2) {
            if(x > y) {
                y++;
                ans[*(st[i].begin())] = true;
                st[i].erase(st[i].begin());
            } else if(y > x) {
                x++;
                st[i].erase(st[i].begin());
                while(st[i].size()) {
                    ans[*(st[i].begin())] = true;
                    st[i].erase(st[i].begin());
                }
            } else {
                
            }
        }
    }
    if(x != y) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    rep(i, 1, n) {
        cout << (ans[i] ? 'A' : 'B');
    }
    cout << endl;
    return 0;
}
