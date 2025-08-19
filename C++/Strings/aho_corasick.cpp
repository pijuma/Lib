const int A = 26;
int to[N][A];
int ne = 2, fail[N], term[N];
int pai[N] ;
char letra[N];//letra que me conecta ao meu pai 
int link[N] ; 

void add_string(string str, int id){//parte da trie
    int p = 1;
    pai[p] = 1 ; 
    for(auto c: str){
        int ch = c - 'a'; // !
        if(!to[p][ch]) to[p][ch] = ne++;
        pai[to[p][ch]] = p ;  letra[to[p][ch]] = c ; 
        p = to[p][ch];
    }
    term[p]++;//alguem termina nesse vertice - pode guardar id num vetor/set tbm
}

//nao testei a parte do recursivo 
//pode fazer recursivo ou com bfs 
int get_link(int v) {
    if (pai[v] == 1) {//pai dele é raiz ou a propria
        if (v == 1 || pai[v] == 1)
            link[v] = 0;
        else //eh eu ir pro link do meu pai e descer a minha letra que tenho pra ele
            link[v] = go(get_link(pai[v]), letra[v]);
    }
    return link[v];
}

int go(int v, char ch) {
    int c = ch - 'a';
    if(!to[v][c]) return to[v][c] ; 
    else return 1 ; //se tenho alguem pra descer vou pra ele 
    //se n vou pra raiz 
} 

void init(){//construir suffix links e arrumar o automato 
    for(int i = 0; i < ne; i++) fail[i] = 1;
    queue<int> q; q.push(1);
    int u, v;
    while(!q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < A; i++){
            if(to[u][i]){
                v = to[u][i]; q.push(v);
                if(u != 1){
                    fail[v] = to[ fail[u] ][i];
                    term[v] += term[ fail[v] ];
                }
            }
            else if(u != 1) to[u][i] = to[ fail[u] ][i];
            else to[u][i] = 1;
        }
    }
}
