void solve(int i, int j, int mask , int next_mask){
 
	if(i == n) return ; 
	if(j >= m) dp[i+1][next_mask] = (dp[i+1][next_mask] + dp[i][mask])%mod ; 
	else{
		int at = 1<<j ; 
		if(mask&at) solve(i, j+1, mask, next_mask) ; 
		else{
			solve(i, j+1, mask, next_mask|at) ; 
			if(j + 1 < m && !(mask&(at<<1))) solve(i, j+2, mask, next_mask) ; 
		}
	} 
 
}
 
int32_t main(){
 
	cin >> m >> n ; 
 
	dp[0][0] = 1 ; // base 
 
	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < (1<<m) ; j++){
			solve(i, 0, j, 0) ; 
		}
	}
 
	cout << dp[n][0] ; 
 
}
