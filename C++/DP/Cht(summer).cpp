#include<bits/stdc++.h>
#define int long long 
#define ll long long 
using namespace std ; 

const int maxn = 5e4 + 5 ; 

int pos[maxn], lst_time[maxn], speed[maxn] ;
int n, q ; 

struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use INF = 1/.0, div(a,b) = a/b)
  static const ll INF = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = INF;
      return false;
    }
    if (x->k == y->k) {
      x->p = x->m > y->m ? INF : -INF;
    } else {
      x->p = div(y->m - x->m, x->k - y->k);
    }
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) {
      z = erase(z);
    }
    if (x != begin() && isect(--x, y)) {
      isect(x, y = erase(y));
    }
    while ((y = x) != begin() && (--x)->p >= y->p) {
      isect(x, erase(y));
    }
  }
  ll query(ll x) const {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
} cht;

int32_t main(){
    ios_base::sync_with_stdio(false) ;cin.tie(NULL) ;
    cin >> n >> q ;  
    for(int i = 1 ; i <= q ; i++){
        int tipo, timer ; cin >> tipo ; 
        if(tipo==1){
            int c, s; cin >> timer >> c >> s ; 
            pos[c] = pos[c] + (timer-lst_time[c])*speed[c] ;
            //cout << c << " " << pos[c] << "\n" ;
            cht.add(s, pos[c]-(timer*s)) ;
            speed[c] = s ; lst_time[c] = timer ; 
        }
        else {
            cin >> timer ; cout << cht.query(timer) << "\n";
        }
    }
}
