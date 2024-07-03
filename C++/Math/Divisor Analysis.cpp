/*
Código pra calcular 
- número de divisores
- soma dos divisores
- produto dos divisores
*/

const int MOD = 1e9+7;

vector<pii> factors;

int fexp(int a, int b){ // a^b
    if(b==0) return 1;
    if(b==1) return a;
    int ret = fexp(a, b/2);
    ret = (ret*ret)%MOD;
    if(b%2) ret = (a*ret)%MOD;
    return ret;
}

int inv(int a){
    return fexp(a, MOD-2);
}

int num_div(){
    int ret = 1;
    for(pii f : factors){
        int a = f.second;
        ret *= a+1; ret %= MOD;
    }
    return ret;
}

int sum_div(){
    int ret = 1;
    for(pii f : factors){
        int p = f.first;
        int a = f.second;
        ret *= fexp(p, a+1)-1; ret %= MOD;
        ret *= inv(p-1);       ret %= MOD;
    }
    return ret;
}

int prod_div(){
    int n = 1;
    int r = 1; // root
    int d = 1; // number of divisors
    for(pii f : factors){
        int p = f.first;
        int a = f.second;
        n *= fexp(p, a);   n %= MOD;
        r *= fexp(p, a/2); r %= MOD;
        d *= a+1;          d %= 2*(MOD-1);
    }
    if(d%2)
        return fexp(r, d);
    return fexp(n, (d/2)%(MOD-1));
}

int32_t main(){
    
    int n; cin>>n;
    while(n--){
        int x, k;
        cin>>x>>k;
        factors.push_back({x, k});
    }
    cout<<num_div()<<" ";
    cout<<sum_div()<<" ";
    cout<<prod_div()<<"\n";
    
    return 0;
}
