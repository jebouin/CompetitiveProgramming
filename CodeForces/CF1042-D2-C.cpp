/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Multiple cases to consider here:
 *              - If all numbers in the array are nonzero:
 *                  - If there is an odd number of negative numbers, remove the greatest negative number.
 *                  - Else don't remove anything.
 *              - Else
 *                  - Remove every zero except one
 *                  - If there is an odd number of negative numbers, multiply the greatest negative number by 
 *                    the last zero.
 *                  - If it's not the last element, remove the zero and multiply the rest.
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

const int N = 222222, INF = 2e9;
int a[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int z = 0, ne = 0;
    cin >> n;
    vector<int> v;
    rep(i, 1, n) {
        cin >> a[i];
        if(a[i] == 0) {
            z++;
            v.pb(i);
        }
        ne += a[i] < 0;
    }
    int b = -1;
    rep(i, 1, n) {
        if(a[i] < 0 && (b < 0 || a[i] > a[b])) {
            b = i;
        }
    }
    if(z == 0) {
        if(b > 0 && (ne & 1)) {
            cout << 2 << " " << b << endl;
        }
        rep(i, 1, n - 1) {
            int ii = i + 1;
            if(ne & 1) {
                if(i == b) continue;
                if(ii == b) ii++;
            }
            if(ii <= n) {
                cout << "1 " << i << " " << ii << endl;
            }
        }
    } else {
        if(sz(v) > 1) {
            rep(i, 0, sz(v) - 2) {
                cout << "1 " << v[i] << " " << v[i + 1] << endl;
                a[v[i]] = INF;
            }
        }
        int pos = v[sz(v) - 1];
        if((ne & 1) && b > 0) {
            cout << "1 " << pos << " " << b << endl;
            a[pos] = INF;
            pos = b;
            z++;
        }
        if(z < n) {
            cout << "2 " << pos << endl;
            a[pos] = INF;
            int i = 1;
            while(i < n) {
                while(i < n && a[i] == INF) i++;
                int j = i + 1;
                while(j <= n && a[j] == INF) j++;
                if(j <= n) {
                    cout << "1 " << i << " " << j << endl;
                }
                i = j;
            }
        }
    }
    return 0;
}
