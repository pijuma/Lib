/*
util para quando queremos saber quantos primos 
tem num intervalo [L, R] quando L, R < 1e12/14 
mas R-L < 1e7 ou algo proximo 
O(raiz(R)*loglog(raiz(R)) + (R-L+1)*log) +/-
*/
vector<int> sieve(int n){
    vector<int> ans ; int sq = sqrt(n)+1 ; 
    vector<bool> eh_primo(sq+1, 1); 
    for(int i = 2 ; i * i <= n ; i++){
        if(eh_primo[i]){
            ans.pb(i) ; 
            for(int j = i ; j * j <= n ; j+=i) eh_primo[j] = 0 ; 
        }
    } 
    return ans ; 
}

void solve(){

    int l, r ; cin >> l >> r ; 

    auto primos = sieve(r+100) ; 

    int ans = 1 ; vector<bool> vis(r-l+2, 0) ; 

    for(auto a : primos){
       //descobrir primos no intervalo ]l, r]
       for(int beg = ((l/a)+1)*a ; beg <= r ; beg += a){
            //cout << beg << "\n" ; 
            if(vis[beg-l]) continue ; //ja foi marcado como n primo
            vis[beg-l] = 1 ; //nao sou primo 
            // sou da forma prime^k? 
            int at = beg; 
            while(at%a==0) at /= a ; 
            if(at == 1) ans++ ;
       }
    }

    //quantos primos temos ]l, r]?
    for(int i = l + 1 ; i <= r ; i++)if(!vis[i-l]) ans++ ; 
    cout << ans << "\n" ; 

}
