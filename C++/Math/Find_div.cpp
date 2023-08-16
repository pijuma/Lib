void div(){
     for(int i = 1 ; i*i <= n ; i++){
     	if(n%i) continue ; 
     	if(n/i == i) divs.push_back(i) ; 
     	else divs.push_back(i), divs.push_back(n/i) ; 
     }	
}