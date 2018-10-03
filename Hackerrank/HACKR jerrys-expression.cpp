/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - Build the expression tree, and count the number of leaves that add to the total.
 *          - Greedily increase the value of some leaves to make the total equal to zero.
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

const int N = 1111111;
set<pair<int, int> > st;
int val[N];

typedef struct Node {
    Node *l, *r;
    int t;
    bool add;
    int build(const string& s, int i, bool a) {
        int j = i;
        val[i] = 1;
        add = a;
        l = NULL;
        r = NULL;
        if(s[i] == '?') {
            t = 0;
            st.insert(make_pair(i, add));
        } else {
            t = s[i] == '+' ? 1 : -1;
            i++;
            l = new Node;
            i = l->build(s, i, add);
            i++;
            r = new Node;
            i = r->build(s, i, t == 1 ? add : !add);
        }
        return i;
    }
} Node;

Node tree;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    tree.build(s, 0, true);
    int x = 0, y = 0;
    rall(p, st) {
        if(p.se) {
            x += val[p.fi];
        } else {
            y += val[p.fi];
        }
    }
    while(x - y) {
        rall(p, st) {
            if(p.se && x < y) {
                val[p.fi]++;
                x++;
            }
            if(!p.se && x > y) {
                val[p.fi]++;
                y++;
            }
        }
    }
    rall(p, st) {
        cout << val[p.fi] << endl;
    }
    return 0;
}
