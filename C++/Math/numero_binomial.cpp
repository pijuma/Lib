int bin_coef(int n, int k){ return (fac[n]*inv[k]%mod*inv[n-k]%mod) ; }
 
int exp(int a, int b){
	
	int ans = 1 ; 
	
	a %= mod ; 
 
	while(b){
		if(b&1) ans = (ans*a)%mod ; 
		a = (a*a)%mod ; 
		b >>= 1 ; 
	} 
 
	return ans ; 
 
}
 
void solve(){
	
	fac[0] = inv[0] = 1 ; 
 
	for(int i = 1 ; i <= maxn - 5 ; i++){
		fac[i] = (i*fac[i-1])%mod ; 
		inv[i] = (exp(fac[i], mod - 2)) ; 
	}
 
}