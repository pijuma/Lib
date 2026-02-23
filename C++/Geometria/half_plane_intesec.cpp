#define ld long double 

const ld EPS = 1e-6;
const ld LLINF = 1e12;
const long double INF = 1e18L;
#define vp vector<point>
using T = double ; 

bool eq(T a, T b){ return abs(a - b) <= EPS; }

struct point{
    double x, y;
    int id;
    point(T x=0, T y=0): x(x), y(y){}

    point operator+(const point &o) const{ return {x + o.x, y + o.y}; }
    point operator-(const point &o) const{ return {x - o.x, y - o.y}; }
    point operator*(T t) const{ return {x * t, y * t}; }
    point operator/(T t) const{ return {x / t, y / t}; }
    T operator*(const point &o) const{ return x * o.x + y * o.y; }
    T operator^(const point &o) const{ return x * o.y - y * o.x; }
    bool operator<(const point &o) const{
        return (eq(x, o.x) ? y < o.y : x < o.x);
    }
    bool operator==(const point &o) const{
        return eq(x, o.x) and eq(y, o.y);
    }
	friend ostream& operator<<(ostream& os, point p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

struct line{
    point p1, p2;
    T a, b, c; // ax+by+c = 0;
    // y-y1 = ((y2-y1)/(x2-x1))(x-x1)
    line(point p1=0, point p2=0): p1(p1), p2(p2){
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1 ^ p2;
    }

    T eval(point p){
        return a*p.x+b*p.y+c;
    }
    bool inside(point p){
        return eq(eval(p), 0);
    }
    point normal(){
        return point(a, b);
    }

    bool inside_seg(point p){
        return (
            ((p1-p) ^ (p2-p)) == 0 and
            ((p1-p) * (p2-p)) <= 0
        );
    }

};

struct Halfplane {
    point p, pq;// p + t*pq eh a reta
    ld angle;
    Halfplane() {}
    Halfplane(const point &a, const point &b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);
    }

    bool out(const point &r) { return (pq ^ (r - p)) < -EPS; }
    bool operator<(const Halfplane &e) const { return angle < e.angle; }

    friend point inter(const Halfplane &s, const Halfplane &t) {
        ld alpha = ((t.p - s.p) ^ t.pq) / (s.pq ^ t.pq);
        return s.p + (s.pq * alpha);
    }
};

//retorna os vertices do poligono convexo 
vp hp_intersect(vector<Halfplane> &H) {

    point box[4] = {
        point(LLINF, LLINF),
        point(-LLINF, LLINF),
        point(-LLINF, -LLINF),
        point(LLINF, -LLINF)
    };

    for(int i = 0; i < 4; i++) {
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < (int)H.size(); i++) {

        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        if (len > 0 && fabsl((H[i].pq ^ dq[len-1].pq)) < EPS) {
            if ((H[i].pq * dq[len-1].pq) < 0.0)
                return vp();

            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }

        dq.push_back(H[i]);
        ++len;
    }

    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    if (len < 3) return vp();

    vp ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}

line ret[maxn] ;

ld norm(point a){ // Modulo
    return sqrt(a * a);
}

int ccw(point a, point b, point e){ // -1=dir; 0=collinear; 1=esq;
    T tmp = (b-a) ^ (e-a); // vector from a to b
    return (tmp > EPS) - (tmp < -EPS);
}

bool test(int mid){
    
    vector<Halfplane> at ; 

    for(int i = 1 ; i <= mid ; i++){
        at.pb(Halfplane(ret[i].p1, ret[i].p2)) ; 
    }

    auto ans = hp_intersect(at) ;

    if(ans.empty()) return 0 ; 

    //qual maior dist pra algum vertice? 
    ld mx = 0.000 ; 

    for(auto a : ans){
        if(norm(a) - d > EPS) return 1 ; 
    }

    
    return 0 ; 

}

void solve(){

    cin >> n >> d ; 

    for(int i = 1 ; i <= n ; i++){
        double x1, x2, y1, y2 ; 
        cin >> x1 >> y1 >> x2 >> y2 ; 
        point p1(x1, y1), p2(x2, y2) ;
        //ponto (0, 0) com orientação continua
		//tomar cuidado para manter a mesma orientação
        if(ccw(p1, p2, point(0, 0)) == -1) swap(p1, p2) ; 
        ret[i] = line(p1, p2) ; 
    }

    int ini = 1, fim = n, mid, best = n+1 ; 

    while(ini <= fim){
        mid = (ini + fim)>>1 ; 
        if(test(mid)) ini = mid + 1 ; 
        else best = min(best, mid), fim = mid - 1 ; 
    }

    if(best == n+1) cout << "*\n" ; 
    else cout << best << "\n" ;
    
}
