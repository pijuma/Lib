//cuidado que o maxn tem q ser 2*string
//se for so inserção aproveita oq ja tinha antes (fica mais rapido) 
void remocao(){ //se n remover reaproveita oq foi feito 
    for(int i = 1 ; i <= extra.size() ; i++) p[i] = 0 ; 
}

// palindromo par centrado em i se i e i-1 são centros!!!
vector<int> manacher_odd(){//calcular pra impar

    int n = extra.size() ;  

    string k = '$' + extra + '^' ;
    //cout << k << "\n" ; 
    int l  = 1, r = 1 ; 

    //cout << pos << "\n" ; 

    for(int i = 1 ; i <= n ; i++){
        if(!p[i]) p[i] = max(0, min(r-i, p[l+(r-i)])) ; // faz parte do l, r dado? 
        //se n fizer r-i vai dar negativo e ele vai guardar 0 
        while(k[i-p[i]] == k[i+p[i]]){ //algoritmo trivial (n^2)
            p[i]++ ; 
        }
        if(i + p[i] > r){
            l = i-p[i] ; r = i+p[i] ; //arrumando os limites  
        }
    }

    return vector<int> (begin(p) + 1, end(p) - 1) ; //n passar 1a e ultima pos (caracteres add)

}

int id, mx ; 
int qp[maxn], qi[maxn] ; 

//n qro lidar com caso par
vector<int> manacher(){

    auto res = manacher_odd() ; //transformar td em palindromo impar 

    vector<int> dpar(s.size()+2, 0), dimp(s.size()+2, 0) ; 
    //resi -> qts palindromos impares tenho centrado em i 

    for(int i = 0 ; i < s.size() ; i++){
        //tamanho de fato do valor q tenho centrado em i 
        int sz_neww_par = (2*res[2*i]-1) ;
        dpar[i] = (sz_neww_par - 1)/2 ; //max pal par em i
        int sz_neww_imp = (2*res[(2*i)+1]-1) ;
        dimp[i] = sz_neww_imp/2 ; //max pal impar em i 
    }

    //qts palindromos centrados em i? 
    //par -> tam k -> k/2 palindromos centrados ali 
    //impar -> tam k -> (k+1)/2 palindromos centrados ali 

    for(int i = 0 ; i < s.size() ; i++){
        ans += dpar[i]/2 ;
        ans += (dimp[i]+1)/2 ;  
    }

    return res ; 

}

int main(){

    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 

    int q ; cin >> q ; 
    
    extra = '#' ;

    while(q--){
        char a ; cin >> a ; 
        ans = 0 ; 
        if(a == '-') {
            s.pop_back() ; extra.pop_back() ; extra.pop_back() ;
            remocao() ; 
            manacher() ; 
        } 
        else{
            s += a ;
            extra +=a ;extra += string("#") ; 
            manacher() ;  
        }
        //cout << s << "\n" ; 
        //cout << extra << "\n" ;
        cout << ans << " " ; 
    }

}
