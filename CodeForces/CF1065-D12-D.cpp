/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - We can model a game state by (x, y, has, piece) where (x, y) is the position of the piece, has is 
 *            the last number visited and piece is the current piece.
 *          - There are at most 3n⁴ <= 30000 states.
 *          - The answer is the shortest path from the first position with has = 1 and any piece to the last
 *            position with has = n² and any piece.
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

typedef struct S {
    int x, y, has, piece;
} S;

bool operator < (const S& x, const S& y) {
    if(x.x < y.x) return true;
    if(x.x > y.x) return false;
    if(x.y < y.y) return true;
    if(x.y > y.y) return false;
    if(x.has < y.has) return true;
    if(x.has > y.has) return false;
    return x.piece < y.piece;
}

const int N = 11;
const int KDX[] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int KDY[] = {-1, 1, 2, 2, 1, -1, -2, -2};
int a[N][N], tx[N * N], ty[N * N];
map<S, int> dist, cnt;
queue<S> q;
int n;

void add(S to, int nd, int ncnt) {
    if(dist.find(to) == dist.end() || dist[to] > nd || dist[to] == nd && cnt[to] > ncnt) {
        dist[to] = nd;
        cnt[to] = ncnt;
        q.push(to);
    }
}

bool isCorrect(const S& s) {
    return s.x >= 1 && s.y >= 1 && s.x <= n && s.y <= n;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int nn = n * n;
    rep(i, 1, n) {
        rep(j, 1, n) {
            cin >> a[i][j];
            tx[a[i][j]] = i;
            ty[a[i][j]] = j;
        }
    }
    rep(p, 0, 2) {
        S s;
        s.x = tx[1];
        s.y = ty[1];
        s.has = 1;
        s.piece = p;
        dist[s] = 0;
        q.push(s);
    }
    while(q.size()) {
        S u = q.front();
        q.pop();
        rep(p, 0, 2) {
            S v = u;
            v.piece = p;
            add(v, dist[u] + 1, cnt[u] + 1);
        }
        if(u.piece == 0) {
            rep(d, 0, 7) {
                S v = u;
                v.x += KDX[d];
                v.y += KDY[d];
                if(isCorrect(v)) {
                    add(v, dist[u] + 1, cnt[u]);
                }
            }
        } else if(u.piece == 1) {
            S v = u;
            rep(i, 1, n) {
                v.x = i;
                v.y = u.y;
                add(v, dist[u] + 1, cnt[u]);
            }
            rep(i, 1, n) {
                v.x = u.x;
                v.y = i;
                add(v, dist[u] + 1, cnt[u]);
            }
        } else if(u.piece == 2) {
            S v = u;
            rep(i, -n, n) {
                v.x = u.x + i;
                v.y = u.y + i;
                if(isCorrect(v)) {
                    add(v, dist[u] + 1, cnt[u]);
                }
            }
            rep(i, -n, n) {
                v.x = u.x + i;
                v.y = u.y - i;
                if(isCorrect(v)) {
                    add(v, dist[u] + 1, cnt[u]);
                }
            }
        }
        if(u.has < nn && u.x == tx[u.has + 1] && u.y == ty[u.has + 1]) {
            S v = u;
            v.has++;
            add(v, dist[u], cnt[u]);
        }
    }
    int ans = 1e9, anss;
    rep(i, 0, 2) {
        S e;
        e.x = tx[nn];
        e.y = ty[nn];
        e.piece = i;
        if(dist.find(e) != dist.end()) {
            if(dist[e] < ans || dist[e] == ans && cnt[e] < anss) {
                ans = dist[e];
                anss = cnt[e];
            }
        }
    }
    cout << ans << " " << anss << endl;
    return 0;
}
