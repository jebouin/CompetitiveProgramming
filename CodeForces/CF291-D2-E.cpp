/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Use a modified version of KMP to work on trees by doing a DFS and keeping track of the position in
 *            the pattern on each call.
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

const int N = 111111, SN = 333333;
char in[SN];
int pref[SN];
vector<int> tree[N];
int memo[SN][26];
string es[N], pat;
int l, n;

void buildPref(const string& s) {
    rep(i, 0, sz(s) - 1) {
        fill(memo[i], memo[i] + 26, -1);
    }
    pref[0] = 0;
    rep(i, 1, sz(s) - 1) {
        pref[i] = pref[i - 1];
        while(pref[i] && s[pref[i]] != s[i]) {
            pref[i] = pref[pref[i] - 1];
        }
        if(s[pref[i]] == s[i]) {
            pref[i]++;
        }
    }
}

int getPos(int pos, char c) {
    if(!pos || pat[pos] == c) return pos;
    if(memo[pos][c - 'a'] != -1) {
        return memo[pos][c - 'a'];
    }
    int ans = getPos(pref[pos - 1], c);
    memo[pos][c - 'a'] = ans;
    return ans;
}

int dfs(int u = 1, int p = 0, int pp = 0) {
    int ans = 0;
    rall(v, tree[u]) {
        if(v != p) {
            int npp = pp;
            rep(i, 0, sz(es[v]) - 1) {
                npp = getPos(npp, es[v][i]);
                if(es[v][i] == pat[npp]) {
                    npp++;
                }
                if(npp == sz(pat)) {
                    ans++;
                    npp = pref[npp - 1];
                }
            }
            ans += dfs(v, u, npp);
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d", &n);
    rep(u, 2, n) {
        int v;
        scanf(" %d %s", &v, in);
        es[u] = (string)in;
        tree[u].pb(v);
        tree[v].pb(u);
    }
    scanf(" %s", in);
    pat = (string)in;
    buildPref(pat);
    int ans = dfs();
    printf("%d\n", ans);
    return 0;
}
