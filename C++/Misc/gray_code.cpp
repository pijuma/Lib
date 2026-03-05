void flip(int l, int r){
	cout << l << " " << r << endl ; 
	cin >> qtd ; 
	if(qtd == n) exit(0);
}

int gray(int y){return y^(y>>1);}

bool ligado(int i){

	int old = qtd ; 
    flip(i, i) ;  
    
    if(old == qtd){
        flip(i, i) ; 
        return 0 ; 
    }

	if(qtd < old){
		flip(i, i) ; 
		return 1 ; 
	}

    return 1 ; 

}

void solve(){

	cin >> n ; 
	cin >> qtd ; 

	if(qtd == n) exit(0) ;

	for(int i = n ; i >= 1 ; i--){

        if(ligado(i)){//testo se ta tudo ok do inicio (mask 0) - caso de borda 
            continue ; 
        }

		//qro pegar o bit que mudou atualmente no gray code (gray code incluindo ate o bit i)
		for(int mask = 1, ot = gray(0) ; mask < (1LL<<i) ; mask++){
			int at = ot^gray(mask);
			ot = gray(mask) ; 
			int j = __builtin_ctzll((unsigned)at) ;
			int old = qtd ; 
			flip(j+1, i) ; 
			if(qtd > old){
				if(ligado(i)) break ;
			}
		}
 
	}
}   
