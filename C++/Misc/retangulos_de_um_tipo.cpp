/*
quantos retangulos de tamanho (i, j) 
tem tal que todos sao "." dentro 
se D = 3 U = 4: 
D = Di-i+1, U = i - Ui + 1 
1 1 
2 2
3 3
4 2 
5 1
6 1
7 0 
soma +1 em 1 com largura R 
ans[1][R]++
ans[D+1][R]--
ans[U+1][R]--
ans[D+U+1][R]++ -> travar de continuar crescendo sempre 
fazendo psum em cima disso 
somando linha anterior, coluna anterior e 
proximo R no R anterior 

ent eu tenho a qtd de todos retangulos [i][j] que posso formar
*/

int n, m, k ; 

void solve(){

    cin >> n >> m ; 

    vector<vector<int>> a(n+2, vector<int>(m+2, 0)) ; 
    vector<vector<int>> r(n+2, vector<int>(m+2, 0)) ; 

    for(int i = 1 ; i <= n ; i++){
        string s ; cin >> s ; 
        for(int j = 0 ; j < m ; j++){
            a[i][j+1] = (s[j]=='.') ; 
        }
    }

    //p cada linha eu tenho em cada coluna o limite a 
    //direita 

    for(int i = 1 ; i <= n ; i++){
        for(int j = m ; j >= 1 ; j--){
            if(!a[i][j]) r[i][j] = 0 ; 
            else r[i][j] = r[i][j+1] + 1 ; 
        }
    }

    //p cada cara eu preciso saber de que intervalo 
    //ele eh minimo (altura)

    vector<vector<int>> U(n+2, vector<int>(m+2, 0)) ; 
    vector<vector<int>> D(n+2, vector<int>(m+2, 0)) ; 

    for(int j = 1 ; j <= m ; j++){
        r[0][j] = -1 ; 
        r[n+1][j] = -1 ; 
        for(int i = 1 ; i <= n ; i++){
            U[i][j] = i-1 ; 
            while(r[i][j] < r[U[i][j]][j]) U[i][j] = U[U[i][j]][j] ; 
        }
        for(int i = n ; i >= 1 ; i--){
            D[i][j] = i+1 ; 
            while(r[i][j] <= r[D[i][j]][j]) D[i][j] = D[D[i][j]][j] ; 
        }
    }

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            U[i][j]++ ; D[i][j]-- ; 
        }
    }

    vector<vector<int>> ans(n+5, vector<int>(m+5, 0)) ; 
    //ans guarda a psum, que mantem quantos retangulos 
    //validos tenho com (i, j) 

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            int d = D[i][j] - i + 1, u = i - U[i][j] + 1 ;  
            ans[1][r[i][j]]++ ; 
            ans[d+1][r[i][j]]-- ; 
            ans[u+1][r[i][j]]-- ; 
            ans[d+u+1][r[i][j]]++ ; 
        }
    }

    //propagando a psum 
    for(int j = 1 ; j <= m ; j++){
        //p construir as atts
        for(int i = 1 ; i <= n ; i++) ans[i][j] += ans[i-1][j] ; 
        //pra atualizar de fato
        for(int i = 1 ; i <= n ; i++) ans[i][j] += ans[i-1][j] ; 
    }
    //se eh possivel criar pra 3 eh pra 2 
    for(int i = 1 ; i <= n ; i++){
        for(int j = m ; j >= 1 ; j--) ans[i][j] += ans[i][j+1] ; 
    } ;

    int resp = 0 ; 
    //nessa questao quero contar quantos com tamanho <= k 

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            cout << ans[i][j] << " "; 
        }
        cout << "\n" ; 
    } 

}
