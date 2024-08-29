/*
1-Set the value a in array k to x.
2-Calculate the sum of values in range [a,b] in array k.
3-Create a copy of array k and add it to the end of the list. 
*/ 

vector<int> root, e, d, sum ; 
 
struct SEG{
 
	int create(){
		sum.push_back(0), e.push_back(0), d.push_back(0) ;
		return max((int)sum.size()-1, 0LL) ;  
	}
 
	int upd(int no, int i, int j, int pos, int val){
		
		if(j < i) return 0 ; 
		
		int neww = create() ; 
		sum[neww] = sum[no], e[neww] = e[no], d[neww] = d[no] ; 
 
		if(i == j){
			sum[neww] = val ; 
			return neww ; 
		}
		
		if(pos <= meio){
			int aux ; aux = upd(e[neww], i, meio, pos, val) ; 
			e[neww] = aux ; 
		}
 
		else{
			int aux ; aux = upd(d[neww], meio + 1, j, pos, val) ; 
			d[neww] = aux ; 
		}
 
		sum[neww] = sum[e[neww]] + sum[d[neww]] ; 
		return neww ; 
	}
 
	int query(int no, int i, int j, int l, int r){
		if(!no || j < i) return 0 ; 
		if(i > r || j < l) return 0 ; 
		if(l <= i && r >= j) return sum[no] ;  
		return query(e[no], i, meio, l, r) + query(d[no], meio+1, j, l, r) ; 
	}
 
} Seg ; 
 
int32_t main(){
 
	ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
	
	cin >> n >> q ; 
 
	root.push_back(Seg.create()) ; 
	root.push_back(Seg.create()) ; 
 
	for(int i = 1 ; i <= n ; i++){
		int v ; cin >> v ; 
		root.back() = Seg.upd(root.back(), 1, n, i, v) ; 
	} 
 
	while(q--){
		
		int t ; cin >> t ; 
 
		if(t == 1){
			int k, a, x ; cin >> k >> a >> x ; 
			root[k] = Seg.upd(root[k], 1, n, a, x) ; 
		}
 
		else if(t == 2){
			int k, a, b ; cin >> k >> a >> b ; 
			cout << Seg.query(root[k], 1, n, a, b) << "\n" ; 
		}
 
		else{
			int k ; cin >> k ; 
			root.push_back(root[k]) ; 
		}
	}
 
}
