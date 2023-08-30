multiset<int> low, up ; 
 
void ins(int val){
	
	int mid = *low.rbegin() ; 
 
	if(val > mid){
		up.insert(val) ;
		if(up.size() > low.size()){
			int newlow = *up.begin() ; 
		    up.erase(up.find(newlow)) ; 
		    low.insert(newlow) ;
		} 
	}
 
	else{
		
		low.insert(val) ; 
		
		if(low.size() > up.size() + 1){
			int newup = *low.rbegin() ; 
			low.erase(low.find(newup)) ; 
		    up.insert(newup) ;
		}
 
	}
 
}
 
void ren(int val){
	if(low.find(val) != low.end()) low.erase(low.find(val)) ; 
	else up.erase(up.find(val)) ;
	if(low.size() < up.size()){
		int newlow = *up.begin() ; 
		up.erase(up.find(newlow)) ; 
		low.insert(newlow) ; 
	} 
}
// mediana ta no low.rbegin() 
