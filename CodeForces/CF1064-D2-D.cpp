/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Use BFS with states (x, y, m) where m is 0 if there are more right moves left than left moves.
 *          - Store how many left/right moves are left.
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
    int x, y;
    bool ml;
} S;
 
const int N = 2222;
const int DX[] = {1, -1, 0, 0};
const int DY[] = {0, 0, 1, -1};
bool grid[N][N], vis[N][N];
pair<int, int> dist[N][N][2];
S q[N * N];
int qs, qe;
int n, m, r, c, x, y;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> r >> c >> x >> y;
    rep(i, 1, n) {
        string s;
        cin >> s;
        rep(j, 1, m) {
            grid[i][j] = s[j - 1] == '*';
            dist[i][j][0] = make_pair(-1, -1);
            dist[i][j][1] = make_pair(-1, -1);
        }
    }
    S st;
    st.x = r;
    st.y = c;
    st.ml = false;
    q[qe++] = st;
    dist[r][c][0] = make_pair(x, y);
    while(qs != qe) {
        S u = q[qs++];
        qs %= N * N;
        vis[u.x][u.y] = true;
        int le = dist[u.x][u.y][u.ml].fi, ri = dist[u.x][u.y][u.ml].se;
        rep(d, 0, 3) {
            S v = u;
            v.x += DX[d];
            v.y += DY[d];
            if(v.x < 1 || v.x > n || v.y < 1 || v.y > m) continue;
            if(grid[v.x][v.y]) continue;
            int nle = v.y < u.y ? le - 1 : le;
            int nri = v.y > u.y ? ri - 1 : ri;
            if(nle < 0 || nri < 0) continue;
            v.ml = nle > nri;
            if(dist[v.x][v.y][v.ml].fi == -1) {
                dist[v.x][v.y][v.ml] = make_pair(nle, nri);
                q[qe++] = v;
                qe %= N * N;
            } else {
                int vle = dist[v.x][v.y][v.ml].fi, vri = dist[v.x][v.y][v.ml].se;
                bool add = false;
                if(v.ml && nle > vle) add = true;
                if(!v.ml && nri > vri) add = true;
                if(add) {
                    dist[v.x][v.y][v.ml] = make_pair(nle, nri);
                    q[qe++] = v;
                    qe %= N * N;
                }
            }
        }
    }
    int ans = 0;
    rep(i, 1, n) {
        rep(j, 1, m) {
            ans += vis[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}
