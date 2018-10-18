/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Let r be a centroid of the tree. Root the tree at r, and add every subtree size to a multiset.
 *          - Consider a node u that is not already a centroid of the tree. We know the subtree that is too big
 *            is the one that goes upwards from its parent, let its size be s > n / 2.
 *          - To make u a centroid, we can detach a subtree that doesn't contain u from the root and attach it
 *            to u, reducing the size of the biggest subtree of u.
 *          - Greedily choose the largest subtree of the root from the set.
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

const int N = 444444;
vector<int> tree[N];
int cnt[N], bn[N];
bool ans[N];
int n, root, root2;

void dfs(int u = 1, int p = 0) {
    cnt[u] = 1;
    bool ok = true;
    rall(v, tree[u]) {
        if(v != p) {
            dfs(v, u);
            if(cnt[v] > n / 2) {
                ok = false;
            }
            cnt[u] += cnt[v];
        }
    }
    if(n - cnt[u] > n / 2) {
        ok = false;
    }
    if(ok) {
        if(root) {
            root2 = root;
        }
        root = u;
    }
}

void dfs2(int b, int u, int p) {
    bn[u] = b;
    rall(v, tree[u]) {
        if(v != p) {
            dfs2(b, v, u);
        }
    }
}

void dfs3(int u, int p = 0) {
    cnt[u] = 1;
    rall(v, tree[u]) {
        if(v != p) {
            dfs3(v, u);
            cnt[u] += cnt[v];
        }
    }
}

void solve(int r) {
    fill(cnt + 1, cnt + n + 1, 0);
    dfs3(r);
    multiset<int> br;
    rall(u, tree[r]) {
        dfs2(u, u, r);
        br.insert(cnt[u]);
    }
    rep(u, 1, n) {
        if(u == r) {
            ans[u] = true;
        } else {
            int b = bn[u];
            br.erase(br.find(cnt[b]));
            if(br.size()) {
                int si = n - cnt[u];
                int after = si - *(br.rbegin());
                ans[u] |= after <= n / 2;
            }
            br.insert(cnt[b]);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d", &n);
    rep(i, 2, n) {
        int u, v;
        scanf("%d %d", &u, &v);
        tree[u].pb(v);
        tree[v].pb(u);
    }
    dfs();
    solve(root);
    if(root2) {
        solve(root2);
    }
    rep(u, 1, n) {
        printf("%d ", ans[u]);
    }
    printf("\n");
    return 0;
}
