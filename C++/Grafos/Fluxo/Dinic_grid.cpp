/*
Grid em que temos posições q devem ser "marcadas" 
podemos marcas cada 2 adjs 
qual menor qtd de peças pra todas estarem marcadas?   
queremos saber quantas podemos unir assim eh total - juntas 
min node cover 
eu crio nos tal que sao 
o tipo de peça na posicao 
e ligo pra posicoes q ele cobre que precisam ser 
cobertas 
queremos 
biparticao -> (x, y) pode ligar em (x+-1, y)/ (x, y+-1)
paridade diferente 
x+y par liga na fonte 
impar liga no terminal 
*/

bool valid(int i, int j){
    return i > 0 && j > 0 && i <= n && j <= m && v[i][j] ; 
}

int main(){

    int t ; cin >> t ;

    while(t--){
        Dinic dinic ; 
        cin >> n >> m ; 
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m ; j++){
                char a ; cin >> a ; 
                v[i][j] = (a=='*') ; 
            }
        }
      
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m ; j++){
                id[i][j] = ++ct ; 
            }
        }
        int S = 0, T = ct+1 ; int ans = 0 ; 
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m ; j++){
                if(!v[i][j]) continue ; 
                ans++ ; 
                if((i+j)&1){
                    dinic.addEdge(id[i][j], T, 1, 0) ;
                }
                else{
                    dinic.addEdge(S, id[i][j], 1, 0) ; 
                    if(valid(i-1, j)) dinic.addEdge(id[i][j], id[i-1][j], 1, 0) ;
                    if(valid(i+1, j)) dinic.addEdge(id[i][j], id[i+1][j], 1, 0) ; 
                    if(valid(i, j+1)) dinic.addEdge(id[i][j], id[i][j+1], 1, 0) ; 
                    if(valid(i, j-1)) dinic.addEdge(id[i][j], id[i][j-1], 1, 0) ; 
                }
            }
        }
        cout << ans - dinic.flow(S, T) << "\n" ; 
    }

}
