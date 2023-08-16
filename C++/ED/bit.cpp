struct BIT{

	void upd(int pos, int val){
		for(; pos < maxn ; pos += pos&-pos) bit[pos] += val ; 
	}
    
    int query(int pos){
    	int tot = 0 ; 
    	for(; pos > 0 ; pos -= pos&-pos) tot += bit[pos] ; 
    	return tot ; 
    }

} Bit ; 