// como considerar na dp tds os jeitos 
// de pegar ou n pegar cada kra? linha 58 etc
/*
dp[v][qtd]
[0] -> += dp[v][0]*dp[a][0]
[1] -> += dp[v][1]*dp[a][0] + (dp[v][0]*dp[a][1]) 
[2] -> += dp[a][1] + dp[v][2]
*/
int dp[maxn][4] ; 

void dfs(int v, int p){

    int folha = 1 ; 

    for(auto a : grafo[v]){
        if(a == p) continue ; 
        folha = 0 ; 
        dfs(a, v) ; 
    }

    if(folha){
        dp[v][1] = dp[v][0] = 1 ; 
        dp[v][2] = 0 ; 
    }

    else{

        dp[v][1] = dp[v][0] = 1 ; 
        dp[v][2] = 0 ;

        for(auto a : grafo[v]){
            if(a == p) continue; 
            dp[v][0] = (dp[v][0]*dp[a][0])%mod ;
            dp[v][1] = (dp[v][1] + (dp[v][1]*dp[a][1])%mod)%mod ;
            // como calcular rapido tds os jeitos de pegar e n pegar cada componente? 
            // em dp[v][1] eu ja terei tds as formas anteriores de pegar ou n pegar assim pro meu 
            // qd faço *dp[a][1] e somo noq eu tinha antes 
            // eu add todas as possibilidades de pegar o kra a n pegando ou pegando cada cara anterior 
            // q eu ja considerei na resp de dp[v][1] assim ao final 
            // dp[v][1] guardara tds os jeitos de ter 1 kra pegando ou n pegando os filhos
            dp[v][2] = (dp[v][2] + (dp[a][1] + dp[a][2])%mod)%mod ; 
        }

    }

}

void solve(){

    cin >> n ; 

    for(int i = 1 ; i < n ; i++){
        int a, b ; cin >> a >> b ; 
        grafo[a].push_back(b) ; grafo[b].push_back(a) ; 
    }

    dfs(1, 0) ; 

    cout << ((dp[1][0] + dp[1][2])%mod + dp[1][1])%mod << "\n" ;

    for(int i = 1 ; i <= n ; i++) grafo[i].clear() ; 

}
 
int32_t main(){
 
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
 
    int t; 
    //t = 1 ; 
    cin >> t ; 
 
    while(t--) solve() ;
 
}  
