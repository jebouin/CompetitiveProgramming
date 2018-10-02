/*
 *  Author: Jeremy Bouin
 *
 *  Idea:
 *          - The names are short, so brute forcing every prefix is enough.
 *          - Each time a name is added, insert its prefixes in a set and the name itself to a map that counts
 *            the occurences.
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    map<string, int> mp;
    set<string> st;
    while(n--) {
        string s;
        cin >> s;
        bool ok = false;
        rep(i, 1, sz(s)) {
            string t = s.substr(0, i);
            if(st.find(t) == st.end()) {
                cout << t << endl;
                ok = true;
                break;
            }
        }
        if(!ok) {
            int k = mp[s] + 1;
            if(k > 1) {
                cout << s << " " << k << endl;
            } else {
                cout << s << endl;
            }
        }
        rep(i, 1, sz(s)) {
            st.insert(s.substr(0, i));
        }
        mp[s]++;
    }
    return 0;
}
