struct KMP{

    string P ; 
    int n ; // n = |P| 
    vector<int> neig ; 
    vector<vector<int>> dfa;

    KMP(string &p){
        P = p ; 
        n = P.size() ; 
        neig.resize(n+2) ;
        dfa = vector<vector<int>> (n+2, vector<int>(26));
        neig[1] = 0 ; // sempre vivo 
        for(int k = 1 ; k < n ; k++) {
            neig[k+1] = next_leader(neig[k], P[k]) ; 
        }
        neig[n] = n+1 ; neig[n+1] = n+1 ; 
    }

    bool match(int state, char c){
        return state < n && P[state] == c ; 
    }

    int next_leader(int leader, char input){
        if(!leader) return (P[leader] == input) ; 
        if(P[leader] == input) return leader+1 ; 
        return next_leader(neig[leader], input) ; 
    }

    void build_dfa(){//construir explicito 
        
        dfa[0][P[0]-'A'] = 1 ; 

        for(int c = 0 ; c < 26 ; c++) dfa[n+1][c] = n+1 ; 

        for(int k = 1 ; k <= n ; k++){
            for(int c = 0 ; c < 26 ; c++){
                if(k < n && P[k] == 'A' + c) dfa[k][c] = k+1 ; 
                else dfa[k][c] = dfa[neig[k]][c] ; 
            }
        }

        for(int c = 0 ; c < 26 ; c++) dfa[n][c] = n+1 ; 

    }

    int solve(int m, string s){
        //dp que conta quantas palavras de tam m 
        //tem um dado padrão s 
        build_dfa() ; 

        dp[0][0] = 1; 
        
        for(int i = 1 ; i <= m ; i++){ // tamanho da string que tenho
            for(int j = 0 ; j <= n+1 ; j++){//onde to no automato
                for(int c = 0 ; c < 26 ; c++){//qual letra to add
                    if(!dp[i-1][j]) continue ; 
                    dp[i][dfa[j][c]] = (dp[i][dfa[j][c]] + dp[i-1][j])%mod ; 
                }
            }
        }
        
        return (dp[m][n]+dp[m][n+1])%mod ; 

    }

};

int matches(string P, string s){

    KMP kmp(P) ; 

    int leader = 0, count = 0 ; 

    for(int i = 0 ; i < s.size() ; i++){
        leader = kmp.next_leader(leader, s[i]) ; 
        if(leader == P.size()) count++ ; 
    }

    return count ; 

}

void solve(){

    int N ; string S ; 

    cin >> N >> S ; 
    
    KMP kmp(S) ; 

    cout << kmp.solve(N, S) << "\n" ;  
   
}
