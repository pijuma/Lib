/*
n prisioneiros em celulas de 0 a n-1 
G guardas -> assegurar que nao escapam - so lidam com celulas adjs
cada jail tem um guarda 
priosioneiro tem inteligencia si 
se o guarda tiver vigiando k pessoas 
possibilidade de escape será k*Si
arrumar os guardas de forma que a possibilidade 
total de escapar seja minima 

dp[i][j] = min valor pra ter pego os primeiros j 
usando até o guarda i 

eh monotonico?? 
se pra uma certa qtd de guardas i 
em algum momento k a melhor resp vem dele 
entao nunca vou pegar menos conforme avanço com j 
pois o valor de c(i, j) eh j-k+1 
se j aumenta entao o intervalo fica maior (mais custoso)
oq empurra o k otimo pra direita nunca pra esq 

-> monotonico -> D&C DP
*/
vector<ll> dp_cur, dp_bef ; 

int c(int i, int j){
    return (pref[j]-pref[i-1])*(j-i+1) ; 
}

//computar dp_cur[l]...dp_cur[r]
//com os valores deles vindo de ptl ate ptr
void compute(int l, int r, int ptl, int ptr){

    if(l > r) return ; 

    int mid = (l+r)>>1 ; 
    pii best = {inf, -1} ; 

    for(int k = ptl ; k <= min(mid, ptr) ; k++){
        best = min(best, {(k ? dp_bef[k-1] : 0)+c(k, mid), k}) ;
    }

    dp_cur[mid] = best.ff ; 
    int opt = best.ss ; 

    compute(l, mid-1, ptl, opt) ; compute(mid+1, r, opt, ptr) ;

}

int solve_dp(){

    dp_bef.assign(n, 0) ; dp_cur.assign(n, 0) ; 

    for(int i = 0 ; i < n ; i++){
        dp_bef[i] = c(0, i) ; //um guarda cuidando até o cara i
    }

    for(int i = 1 ; i < g ; i++){//qtd guardas
        compute(0, n-1, 0, n-1) ; 
        dp_bef = dp_cur ; 
    }

    return dp_bef[n-1] ; 

}

void solve(){

    cin >> n >> g ; 

    for(int i = 0 ; i < n ; i++){
        cin >> v[i] ; 
        pref[i] = v[i] ; 
        if(i) pref[i] += pref[i-1]; 
    }

    cout << solve_dp() << "\n" ; 

}
