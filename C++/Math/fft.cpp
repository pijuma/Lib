const int maxn = 2e5 + 5 ; 
const ld PI = acos(-1) ;
 
struct num{
    ld a {0.0}, b {0.0};
    num(){}
    num(ld na) : a{na}{}
    num(ld na, ld nb) : a{na}, b{nb} {}
    const num operator+(const num &c) const{
        return num(a + c.a, b + c.b);
    }
    const num operator-(const num &c) const{
        return num(a - c.a, b - c.b);
    }
    const num operator*(const num &c) const{
        return num(a*c.a - b*c.b, a*c.b + b*c.a);
    }
    const num operator/(const int &c) const{
         return num(a/c, b/c);
    }
};
 
void fft(vector<num> &a, bool invert){
    int n = a.size();
    for(int i=1,j=0;i<n;i++){
        int bit = n>>1;
        for(; j&bit; bit>>=1)
            j^=bit;
        j^=bit;
        if(i<j)
            swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1){
        ld ang = 2 * PI / len * (invert ? -1 : 1);
        num wlen(cos(ang), sin(ang));
        for(int i=0;i<n;i+=len){
            num w(1);
            for (int j=0;j<len/2;j++){
                num u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w = w * wlen;
            }
        }
    }
    if(invert)
      for(num &x: a)
          x = x/n;
 
}
 
vector<ll> multiply(vi const& a, vi const& b){
    vector<num> fa(a.begin(), a.end());
    vector<num> fb(b.begin(), b.end());
    int n = 1;
    while(n < (a.size() + b.size()) )
        n <<= 1;      
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);   
    for(int i=0;i<n;i++)
        fa[i] = fa[i]*fb[i];
    fft(fa, true);
    vector<ll> result(n);
    for(int i=0;i<n;i++)
        result[i] = round(fa[i].a);
    while(result.back()==0) result.pop_back();
    return result;
}
 
int main(){
 
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ;
 
    cin >> k >> n >> m ; 
 
    vector<int> f, f2 ; 
 
    for(int i = 0 ; i <= k ; i++) f.push_back(0), f2.push_back(0) ;
    
    for(int i = 1 ; i <= n ; i++){
        int a ; cin >> a ; 
        f[a]++ ; 
    }
    
    for(int i = 1 ; i <= m ; i++){
        int a ; cin >> a ;
        f2[a]++ ; 
    }
 
    vector<ll> vv = multiply(f, f2) ;
 
    while(vv.size() < 2*k+1) vv.push_back(0) ;
 
    for(int i = 2 ; i <= 2*k ; i++) cout << vv[i] << " " ;
    cout << "\n" ;
 
 
}
