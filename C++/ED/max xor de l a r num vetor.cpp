 int n, fim[32*maxn], ct, node[32*maxn][3] ; 
 
int isw(int i, int x){ return (((1<<i)&x)!=0) ; }
 
void add(int x){
 
	int root = 0 ; 
	for(int i = 31 ; i >= 0 ; i--){
		int is_on = isw(i, x) ; 
		if(!node[root][is_on]) node[root][is_on] = ++ct ; 
		root = node[root][is_on] ;
	}
 
	fim[root] = 1 ; 
 
}
 
int quest(int x){
 
	int ans = 0 ; 
	int root = 0 ; 
 
	for(int i = 31 ; i >= 0 ; i--){
		int is_on = !isw(i, x) ;
		if(!node[root][is_on]) is_on = !is_on ; 
		ans += (is_on<<i) ; root = node[root][is_on] ;  
	}
 
	return ans^x ; 
 
}
 
// xor(l, r) = xor(r)^xor(l-1) -> quer maximizar isso 
// ideia de um x ^ algo na trie 
 
int main(){
 
	add(0) ; cin >> n ;
	int mx = 0, xorr = 0 ; 
 
	for(int i = 1 ; i <= n ; i++){
		int a ; cin >> a ; 
		xorr ^= a ;
		mx = max(mx, quest(xorr)) ;  
		add(xorr) ; 
	}
	cout << mx << "\n" ; 
}
