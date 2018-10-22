/*
 *  Author: Jeremy Bouin
 *  
 *  Idea:
 *          - Brute force the answer for n <= 14, observe that there is always a solution for 8 <= n <= 14.
 *          - If n > 14, there is always a way to reduce n by 6 by flipping the first 6 elements to zeroes using
 *            the 5 next elements after that if necessary. This can be done under 2 moves using a translation
 *            of the brute-forced answer for n = 11.
 *          - This solution uses less than n / 3 operations plus less than 12 operations for the remaining
 *            brute force solution.
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

const int N = 111111, NN = 15;
int dist[NN][1 << NN], pr[NN][1 << NN];
pair<int, int> op[NN][1 << NN];
int q[N], a[N];
int qs, qe;

int f(int v, int p, int x, int n) {
    assert(p + 2 * x <= n);
    rep(i, 0, 2) {
        int pos = p + i * x;
        v ^= 1 << (pos - 1);
    }
    return v;
}

void bfs(int n) {
    if(dist[n][0] == 0) return;
    dist[n][0] = 0;
    q[qs++] = 0;
    while(qs != qe) {
        int u = q[qe++];
        qe %= N;
        rep(p, 1, n) {
            rep(x, 1, n) {
                if(p + 2 * x <= n) {
                    int v = f(u, p, x, n);
                    if(dist[n][u] + 1 < dist[n][v]) {
                        dist[n][v] = dist[n][u] + 1;
                        pr[n][v] = u;
                        op[n][v] = make_pair(p, x);
                        q[qs++] = v;
                        qs %= N;
                    }
                }
            }
        }
    }
}

vector<pair<int, int> > get(int n, int v) {
    vector<pair<int, int> > ans;
    if(dist[n][v] > 1e6) {
        return ans;
    }
    while(v) {
        ans.pb(op[n][v]);
        v = pr[n][v];
    }
    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    rep(i, 3, NN - 1) {
        fill(dist[i], dist[i] + (1 << i), 1e7);
        bfs(i);
    }
    int n;
    cin >> n;
    rep(i, 1, n) {
        cin >> a[i];
    }
    vector<pair<int, int> > ans;
    int pos = 1;
    while(pos <= n) {
        int rem = n - pos + 1;
        int cur = NN - 1, add = 0;
        if(cur >= rem) {
            cur = rem;
        } else {
            cur = 6;
            add = 5;
        }
        int v = 0;
        rep(i, 1, cur) {
            v = v * 2 + a[pos + cur - i];
        }
        vector<pair<int, int> > ops;
        if(add) {
            int mini = 10, bv, bm;
            rep(mask, 0, (1 << add) - 1) {
                int vv = v + mask * (1 << cur);
                int di = dist[cur + add][vv];
                if(di < mini) {
                    mini = di;
                    bv = vv;
                    bm = mask;
                }
            }
            ops = get(cur + add, bv);
            rep(i, 0, add - 1) {
                a[pos + cur + i] ^= (bm & (1 << i)) > 0;
            }
        } else {
            if(dist[cur][v] > 1e6) {
                cout << "NO" << endl;
                return 0;
            }
            ops = get(cur, v);
        }
        rall(p, ops) {
            ans.pb(make_pair(p.fi + pos - 1, p.se));
        }
        pos += cur;
    }
    cout << "YES" << endl;
    cout << sz(ans) << endl;
    rall(p, ans) {
        rep(i, 0, 2) {
            cout << p.fi + i * p.se << " ";
        }
        cout << endl;
    }
    return 0;
}
