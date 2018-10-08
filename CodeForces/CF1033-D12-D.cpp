/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Every number is of the form x², x³, x⁴ or yz where x, y and z are prime numbers.
 *          - It is easy to find every x but we can't find y and z since the numbers are too large.
 *          - We don't need to know every y and z, we only need to know the exponent of each factor. The problem
 *            is that y or z can appear as factors of other numbers. We can check it by taking the gcd of every
 *            couple of numbers and update the exponent count accordingly.
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
#define MOD 998244353
#define int long long
typedef long long ll;
using namespace std;

int sq(int x) {
    int s = sqrt(x);
    rep(i, -1, 1) {
        int cur = s + i;
        if(cur > 0 && cur * cur == x) {
            return cur;
        }
    }
    return -1;
}

int sq3(int x) {
    int s = pow(x, 1 / 3.);
    rep(i, -1, 1) {
        int cur = s + i;
        if(cur > 0 && cur * cur * cur == x) {
            return cur;
        }
    }
    return -1;
}

int sq2(int x) {
    int s = sq(x);
    if(s < 0) return -1;
    s = sq(s);
    if(s < 0) return -1;
    return s;
}

const int N = 555;
map<int, int> mp, mpp;
int a[N];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
        int val5 = sq2(a[i]);
        int val4 = sq3(a[i]);
        int val3 = sq(a[i]);
        if(val5 > 0) {
            mp[val5] += 4;
        } else if(val4 > 0) {
            mp[val4] += 3;
        } else if(val3 > 0) {
            mp[val3] += 2;
        } else {
            mpp[a[i]]++;
            mpp[-a[i]]++;
        }
    }
    rall(p, mpp) {
        rall(pp, mpp) {
            if(p.fi < 0 || pp.fi < 0 || abs(p.fi) == abs(pp.fi)) continue;
            int g = __gcd(p.fi, pp.fi);
            if(g > 1) {
                mp[g] += p.se + pp.se;
                mp[p.fi / g] += p.se;
                mp[pp.fi / g] += pp.se;
                mpp[p.fi] = 0;
                mpp[-p.fi] = 0;
                mpp[pp.fi] = 0;
                mpp[-pp.fi] = 0;
                break;
            }
        }
    }
    rall(pp, mpp) {
        if(!pp.se) continue;
        rall(p, mp) {
            if(pp.fi < 0) continue;
            if(pp.fi % p.fi == 0) {
                mp[p.fi] += pp.se;
                mp[pp.fi / p.fi] += pp.se;
                mpp[pp.fi] = 0;
                mpp[-pp.fi] = 0;
                break;
            }
        }
    }
    int ans = 1;
    rall(p, mp) {
        ans *= (p.se + 1);
        ans %= MOD;
    }
    rall(p, mpp) {
        ans *= (p.se + 1);
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
