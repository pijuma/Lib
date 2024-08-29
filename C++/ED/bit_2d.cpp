//query retangulo a, b, c, d 
// y_1 x_1 y_2 x_2 = a, b, c, d
// cout << Bit.query(c, d) + Bit.query(a-1, b-1) - Bit.query(a-1, d) - Bit.query(c, b-1) << "\n" ;
struct BIT{

	void upd(int x, int y, int v){
		for(int i = x ; i < maxn ; i += i&-1){
			for(int j = y ; j < maxn ; j+= j&-j){
				bit[i][j] += v ; 
			}
		}
	}

	int query(int x, int y){
		int tot = 0 ; 
		for(int i = x ; i < maxn ; i += i&-1){
			for(int j = y ; j < maxn ; j+= j&-j){
				tot += bit[i][j] ; 
			}
		}
		return tot ; 
	}


} bit ; 
