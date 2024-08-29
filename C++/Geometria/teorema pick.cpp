int cross(Point a, Point b){ return (a.x*b.y)-(a.y*b.x) ; }
 
int area(){
 
	int val = 0 ; 
 
	for(int i = 3 ; i <= n ; i++){
		Point b = {(p[i-1].x - p[1].x), (p[i-1].y - p[1].y)} ;
		Point a = {(p[i].x - p[1].x), (p[i].y - p[1].y)} ; 
		val += cross(a, b) ;  
	}
 
	return abs(val) ; 
}
 
int find_numb(){
 
	int tot = 0 ; 
 
	for(int i = 2 ; i <= n ; i++){
		int dx = abs(p[i].x - p[i-1].x), dy = abs(p[i].y - p[i-1].y) ; 
		tot += (__gcd(dx, dy)) ; 
	}
 
	int dx = abs(p[n].x - p[1].x), dy = abs(p[n].y - p[1].y) ; 
	tot += (__gcd(dx, dy)) ; 
	return tot ; 
 
}
 
int32_t main(){
 
	cin >> n ; 
 
	for(int i = 1 ; i <= n ; i++) cin >> p[i].x >> p[i].y ; 
 
	// queremos o n° pontos inteiros dentro e no limite 
	// teorema de pick -> area = 1/2b + i - 1 -> 2A = B - 2I - 2 
	// sendo i pontos internos e b pontos no limite 
	// no limite = na reta mdc(dx, dy) - 1 
 
	int A = area() ; 
    int B = find_numb() ;
 
    cout << (A - B + 2)/2 << " " << B << "\n" ; 
}
