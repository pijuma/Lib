#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define pii pair<int,int>
#define int long long 
// order_of_key(k)  : Number of items strictly smaller than k
// find_by_order(k) : K-th element in a set (counting from zero) - ordena os elementos 

// to swap two sets, use a.swap(b);

// Declaring ordered_set 
typedef tree<int, null_type, less<int>, rb_tree_tag,  
            tree_order_statistics_node_update>  
    ordered_set;  
    
#define pii pair<int,int>
#define int long long 

const int maxn = 2e5 + 5 ; 
int mark[maxn] ; 

int32_t main(){
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ;
    int t ; cin >> t ; 

    while(t--){
        int n ; cin >> n ; 
        int ans = 0 ; 
        vector<pii> v ; ordered_set st ; 
        for(int i = 1 ; i <= n ; i++){
            int l, r; cin >> l >> r ; 
            v.push_back({l, r}) ; st.insert(r) ;
        }
        sort(v.begin(), v.end()) ; 
        for(auto a : v){
            ans += st.order_of_key(a.second) ;
            st.erase(st.find(a.second)) ;
        }
        cout << ans << "\n" ; 
    }

}
