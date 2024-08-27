#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9+7;
const int MAX = 1e6+6;
const int P = 5;

int fatorial[MAX];

int power(int a, int b){ // a^b
    if(b==0) return 1;
    if(b==1) return a;
    
    int ans = power(a, b/2);
    ans = (ans*ans)%MOD;
    if(b%2) ans = (a*ans)%MOD;
    return ans;
}

int inv(int a){
    a = (a%MOD+MOD)%MOD;
    return power(a, MOD-2);
}

int binomial(int a, int b){ // (a b)
    return (fatorial[a]*inv((fatorial[b]*fatorial[a-b])%MOD))%MOD;
}

struct ext{
    int a, b; // a+b√P
    // construtor
    ext(int a=0, int b=0){
        this->a = (a%MOD+MOD)%MOD;
        this->b = (b%MOD+MOD)%MOD;
    }
    // funcoes
    ext conjugado() const{
        return ext(a, -b);
    }
    int norma() const{
        return (((a*a)%MOD-P*((b*b)%MOD))%MOD+MOD)%MOD;
    }
    // operadores
    ext operator*(const int t){
        return ext(t*a, t*b);
    }
    ext operator+(const ext y){
        return ext(a+y.a, b+y.b);
    }
    ext operator-(const ext y){
        return ext(a-y.a, b-y.b);
    }
    ext operator*(const ext y){
        return ext((a*y.a)%MOD+P*((b*y.b)%MOD),
                   (a*y.b)%MOD+   (b*y.a)%MOD);
    }
    ext operator/(const ext y){
        return ext(a, b)*y.conjugado()*inv(y.norma());
    }
    bool operator==(const ext y) const {
        return a==y.a and b==y.b;
    }
};

ext power_ext(ext x, int b){ // x^b
    if(b==0) return ext(1, 0);
    if(b==1) return x;
    
    ext ans = power_ext(x, b/2);
    ans = ans*ans;
    if(b%2) ans = x*ans;
    return ans;
}

const ext phi(inv(2),  inv(2));
const ext psi(inv(2), -inv(2));

int fibonacci(int m){
    ext ans = (power_ext(phi, m)-power_ext(psi, m))/ext(0, 1);
    return ans.a;
}

int32_t main(){
    
    fatorial[0] = 1;
    for(int i=1; i<MAX; i++)
        fatorial[i] = (i*fatorial[i-1])%MOD;
        
    int n, k;
    cin>>n>>k;
    ext ans(0, 0);
    for(int j=0; j<=k; j++){
        int coe = binomial(k, j)*(((k-j)%2)?-1:1);
        coe = (coe%MOD+MOD)%MOD;
        
        ext aux = power_ext(phi, j)*power_ext(psi, k-j);
        if(aux == ext(1, 0))
            ans = ans + ext((n%MOD)*coe);
        else
            ans = ans + ((power_ext(aux, n+1)-aux)/(aux-ext(1, 0)))*coe;
    }
    ans = (ans/power_ext(ext(0, 1), k));
    cout<<ans.a<<"\n";
    
    return 0;
}
