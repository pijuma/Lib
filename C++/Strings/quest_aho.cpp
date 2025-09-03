/*
F:number of length-L lowercase English strings that contain all of S1​,S2​,…,SN​ as substrings.
N strings e um inteiro L 
quantas strings modulo mod de tamanho L 
tem essas strings como substrings 
aho??
dp andando na trie c aho 
dp[i][no_trie][quais subs] 
*/

const int maxn = 110 ; 
const int mod = 998244353;
const int A = 26 ; 

int dp[maxn][maxn][(1<<9)];
int n, l ; 
int to[maxn][26];
int ne = 2, fail[maxn] ; 
vector<int>term[maxn];

void add_string(string str, int id){
    int p = 1;
    for(auto c: str){
        int ch = c - 'a'; 
        if(!to[p][ch]) to[p][ch] = ne++;
        p = to[p][ch];
    }
    term[p].pb(id);
}

void init(){
    for(int i = 0; i < ne; i++) fail[i] = 1;
    queue<int> q; q.push(1);
    int u, v;
    while(!q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < A; i++){
            if(to[u][i]){
                v = to[u][i]; q.push(v);
                if(u != 1){
                    fail[v] = to[fail[u]][i];
                    for(auto a : term[fail[v]]) term[v].pb(a) ; 
                }
            }
            else if(u != 1) to[u][i] = to[fail[u]][i];
            else to[u][i] = 1;
        }
    }
}

string atual ; 

int solve(int i, int node, int mask){

    if(dp[i][node][mask] != -1) return dp[i][node][mask] ; 
    if(i >= l){//finalizei
        int new_mask = mask ; 
        for(auto a : term[node]) new_mask |= (1<<a) ;
        return (new_mask == ((1<<n)-1)) ; 
    }

    int ans = 0 ; 

    for(char nxt = 'a' ; nxt <= 'z' ; nxt++){
        atual += nxt ; 
        if(to[node][nxt-'a']){//vou pra ele - existe 
            //ver quais terminam nele 
            int nxt_node = to[node][nxt-'a'];
            int new_mask = mask ;
            for(auto a : term[nxt_node]) new_mask |= (1<<a) ; 
            ans = (ans + solve(i+1, nxt_node, new_mask))%mod ; 
        }
        else{//sobe pra algum sufixo do meu atual - n tenho padrao
            int nxt_node = to[node][nxt-'a'] ; 
            int new_mask = mask ; 
            for(auto a : term[nxt_node]) new_mask |= (1<<a) ; 
            ans = (ans + solve(i+1, nxt_node, new_mask))%mod ; 
        }
        atual.pop_back() ; 
    }

    return dp[i][node][mask] = ans ; 
}
