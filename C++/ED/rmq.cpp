// max ou min eh analogo 
int query(int l, int r){
    int k = _log[r-l+1] ; 
    return max(dp[l][k], dp[r-(1<<k)+1][k]) ; 
}

for(int i = 1 ; i <= n ; i++) dp[i][0] = v[i] ; 
  _log[1] = 0 ; 
  for(int i = 2 ; i <= n ; i++) _log[i] = _log[i>>1] + 1 ; 
  for(int i = 1 ; i <= _log[n] ; i++){
      for(int j = 1 ; j + (1<<i) <= n + 1 ; j++){
          dp[j][i] = max(dp[j][i-1], dp[j+(1<<(i-1))][i-1]) ; 
    }
}
