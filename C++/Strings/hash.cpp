#include<bits/stdc++.h>
using namespace std ;

#define ll long long 

const int prime = 911382323 ; 
const int prime2 = 31 ;
const int mod2 = 1e9 + 7 ;
const int mod = 972663749 ; 
const int maxn = 1e6 + 5 ; 

ll inv[maxn], pot[maxn] ;
vector<ll> Hash ; 

ll exp(ll a, ll b, int m){
	ll ans = 1 ; 
	while(b){
		if(b&1) ans = (ans*a)%m ; 
		b >>= 1 ; 
		a = (a*a)%m ; 
	}
	return ans ; 
}

void calc_Hash(string s, int m, int p){
	ll pot_at = 1 ; 
	for(int i = 0 ; i < s.size() ; i++){
		if(i == 0) Hash[i] = ((s[i]-'a'+1)*pot_at)%m ;
		else Hash[i] = (Hash[i-1] + ((s[i]-'a'+1)*pot_at)%m)%m ; 
		pot_at = (pot_at*p)%m ;
	}
}

ll Hash_inter(int l, int r, int m, int p){
	ll sum = Hash[r] ; 
	if(l) sum = (sum + m - Hash[l-1])%m ;
	sum = (sum * inv[l])%m ;
	return sum ;   
}

int main(){

	ios_base::sync_with_stdio(false) ; cin.tie(NULL) ;

	string s ; cin >> s ; 
	Hash.resize(s.size(), 0) ;
	calc_Hash(s, mod, prime) ;

	pot[0] = inv[0] = 1LL ; 
	inv[1] = exp(prime, mod-2, mod) ; 
 
	for(int i = 1 ; i < s.size() ; i++) pot[i] = (pot[i-1]*prime)%mod ; 
	for(int i = 2 ; i < s.size() ; i++) inv[i] = (inv[i-1]*inv[1])%mod ; 

}
