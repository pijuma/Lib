#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int> 
using namespace std ; 
 
const int inf = 1e9 + 2 ; 
const int maxn = 2e5 + 5 ;  
int contem[maxn] ;
 
int32_t main(){
 
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; 
    
    int n, k ; cin >> n >> k ; 
 
    vector<pair<pii, int>> fila ; 
 
    queue<pii> at[k+1] ;
 
    int timer = 0 ; 
 
    for(int i =1 ; i <= 2*n ; i++){
        int t ; cin >> t ; 
        if(t == 1){
            int kra, f ; cin >> kra >> f ; 
            at[f].push({kra, timer}) ; 
        }
        else{
            int f ; cin >> f ; 
            auto a =  at[f].front() ; at[f].pop() ; 
            fila.push_back({{a.second, -timer}, a.first}) ; 
        }
        timer++ ; 
    } 
 
    sort(fila.begin(), fila.end()) ; 
 
    int mn = inf ; 
 
    for(int i = fila.size() - 1 ; i >= 0 ; i--){
        contem[fila[i].second] = (-fila[i].first.second >= mn) ; 
        mn = min(mn, -fila[i].first.second) ;
    }
 
    vector<int> ans ; 
 
    for(int i = 1 ; i <= n ; i++) if(contem[i] != 0) ans.push_back(i) ; 
 
    cout << ans.size() <<"\n" ; 
 
    for(auto a : ans) cout << a << " " ; 
    cout << "\n" ; 
 
}

//cses
#include<bits/stdc++.h>
using namespace std ; 
 
const int maxn = 2e5 + 5 ; 
 
int n, x, y ; 
pair<int,int> pto[maxn], resp[maxn] ; 
map<pair<int,int>, int> contem, cont ; 
 
int main(){
 
	cin >> n ; 
 
	for(int i = 1 ; i <= n ; i++){
		cin >> pto[i].first >> pto[i].second ;
		pto[i].second *= -1 ; 
		resp[i] = pto[i] ; 
	} 
 
	sort(pto + 1, pto + 1 + n) ;
    
    int mny = (int) (1e9 + 5) ;
 
    for(int i = n ; i > 0 ; i--){
    	contem[pto[i]] = (-pto[i].second >= mny) ; 
    	mny = min(mny, -pto[i].second) ; 
    }
 
    mny = 0 ; 
 
    for(int i = 1 ; i <= n ; i++){
    	cont[pto[i]] = (-pto[i].second <= mny) ; 
    	mny = max(mny, -pto[i].second) ; 
    }
 
    for(int i = 1 ; i <= n ; i++) cout << contem[resp[i]] << " " ; 
    cout << "\n" ; 
    for(int i = 1 ; i <= n ; i++) cout << cont[resp[i]] << " " ;
    cout << "\n" ; 
 
}
