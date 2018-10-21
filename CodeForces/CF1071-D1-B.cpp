/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - If k >= 2n-1, the answer is 2n-1 times the letter 'a'.
 *          - If k < 2n-1, use BFS to find the furthests points from the top left corner reachable only
 *            with 'a's.
 *          - Find the lexicographically smallest path from these starting points by greedily adding the next
 *            positions to a set to avoid an exponential complexity.
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

const int N = 2222;
string mat[N];
int dist[N][N];
pair<int, int> q[N * N];
int qs, qe;
int n, k;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    rep(i, 1, n) {
        string s;
        cin >> s;
        fill(dist[i] + 1, dist[i] + n + 1, -1);
        mat[i] = " " + s + " ";
    }
    if(k >= 2 * n - 1) {
        cout << string(2 * n - 1, 'a') << endl;
        return 0;
    }
    q[qs++] = make_pair(1, 1);
    dist[1][1] = mat[1][1] == 'a';
    while(qs != qe) {
        pair<int, int> u = q[qe++];
        qe %= N * N;
        int cd = dist[u.fi][u.se];
        if(u.fi < n) {
            int nd = dist[u.fi + 1][u.se];
            if((cd + (mat[u.fi + 1][u.se] == 'a')) > nd) {
                dist[u.fi + 1][u.se] = cd + (mat[u.fi + 1][u.se] == 'a');
                q[qs++] = make_pair(u.fi + 1, u.se);
                qs %= N * N;
            }
        }
        if(u.se < n) {
            int nd = dist[u.fi][u.se + 1];
            if((cd + (mat[u.fi][u.se + 1] == 'a')) > nd) {
                dist[u.fi][u.se + 1] = cd + (mat[u.fi][u.se + 1] == 'a');
                q[qs++] = make_pair(u.fi, u.se + 1);
                qs %= N * N;
            }
        }
    }
    set<pair<int, int> > pos;
    int l = 0;
    rep(i, 1, n) {
        rep(j, 1, n) {
            int d = i + j - 1;
            int na = dist[i][j];
            int changed = d - na;
            if(changed <= k) {
                if(d > l) {
                    l = d;
                    pos.clear();
                }
                if(d == l) {
                    pos.insert(make_pair(i, j));
                }
            }
        }
    }
    string ans = string(l, 'a');
    if(pos.empty()) {
        pos.insert(make_pair(1, 1));
        ans = string(1, mat[1][1]);
    }
    bool ok = true;
    while(ok) {
        set<pair<int, int> > poss;
        char best = 'z' + 1;
        ok = false;
        rall(p, pos) {
            if(p.fi < n) {
                char ne = mat[p.fi + 1][p.se];
                if(ne < best) {
                    best = ne;
                    poss.clear();
                }
                if(ne == best) {
                    poss.insert(make_pair(p.fi + 1, p.se));
                }
                ok = true;
            }
            if(p.se < n) {
                char ne = mat[p.fi][p.se + 1];
                if(ne < best) {
                    best = ne;
                    poss.clear();
                }
                if(ne == best) {
                    poss.insert(make_pair(p.fi, p.se + 1));
                }
                ok = true;
            }
        }
        if(ok) {
            pos = poss;
            ans += best;
        }
    }
    cout << ans << endl;
    return 0;
}
