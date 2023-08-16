void crivo(){
	for(int i = 2 ; i <= n ; i++) ehprimo[i] = -1 ; 
	for(int i = 2 ; i <= n ; i++){
		if(ehprimo[i] == -1){
			for(int j = i + i ; j <= n ; j += i) ehprimo[j] = 0 ;
			ehprimo[i] = 1 ;  
		}
	}
}