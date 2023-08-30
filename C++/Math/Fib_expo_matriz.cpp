struct MAT{

    int v[2][2] ; 

    MAT(){
        for(int i = 0 ; i < 2 ; i++){
            for(int j = 0 ; j < 2 ; j++) v[i][j] = 0 ; 
        }
    }

    void id(){
        for(int i = 0 ; i < 2 ; i++) v[i][i] = 1 ; 
    }

} ;

int add(int a, int b){ return (a+b)%mod ; }
int M(int a, int b){ return (a*b)%mod ; }

typedef struct MAT matriz ;

matriz mult(matriz a, matriz b){
    
    matriz ans ; 

    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            for(int k = 0 ; k < 2 ; k++){
                ans.v[i][j] = add(ans.v[i][j], M(a.v[i][k], b.v[k][j])) ;
            }
        }
    }
    
    return ans ; 

}

matriz exp(matriz a, int b){

    matriz ans ; ans.id() ;

    while(b){
        if(b&1) ans = mult(ans, a) ;
        a = mult(a, a) ; b >>= 1 ; 
    }

    return ans ; 

}

int32_t main(){

    int n ; cin >> n ; 

    if(n <= 1){
        cout << n << "\n" ; return 0 ; 
    }

    matriz base ; 
    base.v[0][0] = 1 , base.v[0][1] = 1 ; 
    base.v[1][0] = 1, base.v[1][1] = 0 ; 

    matriz ini ; ini.v[0][0] = 1 ; 

    matriz resp ; 

    resp = exp(base, n-1) ;
    resp = mult(resp, ini) ;

    cout << resp.v[0][0] << "\n" ;

}
