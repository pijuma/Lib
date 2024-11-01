/*
a^b^c (Mod P) => a^(k*(P-1)) + j => (teo fermat) a^j 
basta achar j -> b^c Mod (P-1) e aplicar a^j Mod P 
*/

#include<bits/stdc++.h>
#define int long long 
using namespace std ; 

const int MOD = 1e9 + 7 ; 
const int maxn = 2e5 + 5 ; 
int mod ; 

int exp(int a, int b){
    int ans = 1 ; 
    while(b){
        if(b&1) ans = (ans*a)%mod; 
        b >>= 1 ; a = (a*a)%mod ; 
    }
    return ans ; 
}

int32_t main(){

    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 

    int t ; cin >> t ; 

    while(t--){
       int a, b, c ; cin >> a >> b >> c ; 
       mod = MOD - 1 ; 
       int j = exp(b, c) ;
       mod = MOD ;  
       cout << exp(a, j) << "\n" ; 
    }

} 
