#include<bits/stdc++.h>
using namespace std ; 
 
/*
divide a pilha em duas com diferentes valores
*/
 
const int maxn = 1e6 + 5 ; 
 
int dp[maxn] ; 
int freq[maxn] ; 
 
int mex(vector<int> a){
    for(auto b : a) freq[b]++ ; 
    int mex = 0 ; 
    while(freq[mex]) mex++ ; 
    for(auto b : a) freq[b]-- ; 
    return mex ; 
}
 
int solve(int a){
    if(a == 1 || a == 2) return dp[a] = 0 ; 
    if(a == 3) return dp[a] = 1 ; 
    if(dp[a] != -1) return dp[a] ;
    vector<int> seq ; 
    for(int i = 1 ; i < a ; i++){
        if(2*i == a) continue; 
        //cout << i << " " << a-i << "\n" ; 
        int neww = (solve(i)^solve(a-i)) ;
        //cout << "xorr " << neww << "\n" ; 
        seq.push_back(neww) ; 
    }
    return dp[a] = mex(seq) ;
}
 
int main(){
 
    memset(dp, -1, sizeof(dp)) ; 
    
    for(int i = 1 ; i <= 5000 ; i++){
        dp[i] = solve(i)  ; 
        //if(ans == 0) cout << i << "\n" ; 
        //cout << ans << "\n" ; 
    }
 
    int t ; cin >> t ; 
 
    while(t--){
        int n ; cin >> n ; 
        if(n <= 5000){
            if(dp[n] == 0) cout << "second\n" ; 
            else cout << "first\n" ;
        }
        else cout << "first\n" ; 
    }
 
} 
