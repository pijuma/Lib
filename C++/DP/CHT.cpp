#include<bits/stdc++.h>
using namespace std ;
#define int long long 
#define pii pair<int,int> 
#define ff first 
#define ss second 
#define ll long long 
#define ld long double 
#define vi vector<int> 
#define ii int 
#define endd "\n"
#define pb push_back 
#define pf pop_front

#define all(x) x.begin(), x.end()
#define int int64_t
#define pb push_back

void dbg_out() { cerr << endl; }
template <typename H, typename... T>
void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }
#define dbg(...) { cerr << #__VA_ARGS__ << ':'; dbg_out(__VA_ARGS__); }


/*
reta inicial: 
(x, 0)
matar um monstro:
si*fj + dp[j] sendo j o ultimo valor => cht -> qual reta 
pego p minimizar? 
add reta (fi, dp[i])
*/

const int inf = 1e18 + 2 ; 
// CHT - Dynamic Convex Hull Trick
// Description: Maintain the convex hull of some functions
// Complexity: 
//     add - O(logN)
//     query - O(logN)
// se quer pegar o min add(-a, -b) e na pega -query
// Functions:
//     add(a, b) - add line (a * x + b) to the convex hull.
//     query (x) - return the maximum value of any line on point x.
// Details:
//     If you want to maintain the bottom convex hull, it is
//     easier to just change the sign. Be careful with overflow
//     on query. Can use __int128 to avoid.
// Optimization:
//   Use vector instead of multiset, making add O(1) but adding a constraint 
//   that the lines added must be sorted by slope

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> { // comment for Optimization
// struct LineContainer : vector<Line> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a^b) < 0 && a%b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k  - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y; // comment for Optimization
        // if(!empty()) assert(prev(end())->k <= k);
        // push_back({k, m, 0}); 
        // auto z = prev(end()), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x); // comment for Optimization
        // auto l = *lower_bound(begin(), end(), x);
        #warning can overflow
        return l.k * x + l.m;
    }
};

LineContainer merge(LineContainer a, LineContainer b) {
    vector<Line> tmp(a.size() + b.size());
    merge(all(a), all(b), tmp.begin());
    LineContainer res;

    for (auto x : tmp) res.add(x.k, x.m);
    return res;
}

LineContainer add(LineContainer a, LineContainer b) {
    LineContainer res;
    auto x = a.begin(), y = b.begin();
    while (x != a.end() && y != b.end()) {
        res.add(x->k + y->k, x->m + y->m);
        if (x->p < y->p) x++;
        else y++;
    }
    return res;
}

const int maxn = 2e5 + 5 ; 

int dp[maxn], s[maxn], f[maxn] ; 

int32_t main(){

    int n, x ; cin >> n >> x ; 

    LineContainer D ; 
    D.add(-x, 0) ;

    for(int i = 1 ; i <= n ; i++) cin >> s[i] ; 
    for(int i = 1 ; i <= n ; i++) cin >> f[i] ; 

    for(int i = 1 ; i <= n ; i++){
        dp[i] = -D.query(s[i]) ; 
        D.add(-f[i], -dp[i]) ; 
    }

    cout << dp[n] << "\n" ; 

}
