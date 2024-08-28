#include<bits/stdc++.h>
using namespace std ; 

const int maxl = 22 ; 
const int maxn = 2e5 + 5 ; 

int n, q ; 
int vis[maxn] ; 
int tab[maxl][maxn] ; 
int pai[maxn], sz[maxn] ;
int nivel[maxn] ; 
vector<int> grafo[maxn] ; 
int ct, comp[maxn] ;
int tam_ciclo[maxn] ; 

int find(int a){return (a == pai[a] ? a : pai[a] = find(pai[a])) ; }

bool merge(int a, int b){
    a = find(a), b = find(b) ;
    if(a == b) return 0 ; 
    if(sz[a] > sz[b]) swap(a, b) ; 
    sz[b] += sz[a] ; pai[a] = b ;
    return 1;  
}


void dfs(int v, int p){

    comp[v] = ct ; vis[v] = 1 ; 
    
    for(auto a : grafo[v]){
        if(!vis[a]) { nivel[a] = nivel[v] + 1 ; dfs(a, v) ; }
        else tam_ciclo[v] = nivel[v] + 1 ; 
        tam_ciclo[v] = max(tam_ciclo[a], tam_ciclo[v]) ; 
    }

}

//se subir t a partir de a onde paro? 
int who(int a, int t){
    int f = a ; 
    for(int i = maxl - 1 ; i >= 0 ; i--){
        if(t&(1<<i)){
            f = tab[i][f] ; 
        }
    }
    return f ; 
}

int query(int ini, int fim){
    
    if(ini == fim) return 0 ; 
    if(comp[ini] != comp[fim]) return -1 ; // um n alcança o outro 

    if(tam_ciclo[ini]){//ini ta em ciclo 
        if(!tam_ciclo[fim]) return -1 ; 
        else return (tam_ciclo[ini] + (nivel[ini] - nivel[fim]))%tam_ciclo[ini] ; 
    }

    if(!tam_ciclo[fim]){ //ngm ta em ciclo 
        if(nivel[ini] <= nivel[fim]) return -1 ; 
        int d = abs(nivel[fim] - nivel[ini]) ;
        return (who(ini, d) == fim) ? d : -1;  
    }

    // a em arvore e b em ciclo 
    int root = ini ; 
    for(int i = maxl - 1 ; i >= 0 ; i--){
        if(!tam_ciclo[tab[i][root]]){
            root = tab[i][root] ; 
        } 
    }

    root = tab[0][root] ; 

    return abs(nivel[ini] - nivel[root]) + query(root, fim) ; 

}

int main(){

    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
    
    cin >> n >> q ; 

    for(int i = 1 ; i <= n ; i++){
        pai[i] = i, sz[i] = 1 ; 
    }

    for(int i = 1 ; i < maxl ; i++){
        for(int j = 1 ; j <= n ; j++) tab[i][j] = -1 ; 
    }

    vector<int> cycleSeeds ; 

    for(int i = 1 ; i <= n ; i++) { 
        cin >> tab[0][i] ; 
        grafo[tab[0][i]].push_back(i) ;
        int x = tab[0][i] ; 
        if(!merge(x, i))
            cycleSeeds.push_back(x);

    }


    for(auto i : cycleSeeds) if(!vis[i]){++ct ; dfs(i, -1) ; } 

    for(int i = 1 ; i < maxl ; i++){
        for(int j = 1 ; j <= n ; j++){
            if(tab[i-1][j] == -1) continue ; 
            tab[i][j] = tab[i-1][tab[i-1][j]] ;
        }
    }

    while(q--){
        int a, b ; cin >> a >> b ; 
        cout << query(a, b) << "\n" ; 
    }

}
