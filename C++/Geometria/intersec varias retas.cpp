//dadas n retas hor/vert quantos pontos de intersec? 
//line sweep 
const int add = 1e6 + 1 ; // tornar td mundo positivo 
 
int n, X, x2, Y, y2, bit[maxn], ans ; 
vector<pair<pair<int,int>,pair<int,int>>> ptos ; 
 
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
 
int32_t main(){

	for(int i = 1 ; i <= n ; i++){
 
		cin >> X >> Y >> x2 >> y2 ;  
		X += add, x2 += add, Y += add, y2 += add ; 
 
		if(Y == y2){ // horizontal 
			ptos.push_back({{Y, 2}, {X, x2}}) ; 
		}
 
		else{
			ptos.push_back({{Y, 1}, {X, 1}}) ;
			ptos.push_back({{y2, 0}, {X, 1}}) ;  
		}
 
	}
 
	sort(ptos.begin(), ptos.end()) ; 
 
	for(int i = 0 ; i < ptos.size() ; i++){
		if(ptos[i].first.second == 2) ans += Bit.query(ptos[i].second.second) - Bit.query(ptos[i].second.first - 1) ;
		if(ptos[i].first.second == 1) Bit.upd(ptos[i].second.first, 1) ; 
		if(ptos[i].first.second == 0) Bit.upd(ptos[i].second.first, -1) ;  
	}
	cout << ans << "\n" ; 
}
