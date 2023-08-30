#include<bits/stdc++.h>
using namespace std ; 
 
int n ; 
string s ; 
map<string, int> p ; 
 
void dfs(string s){
	
	p[s] = 1 ; 
 
	cout << s << "\n" ; 
	
	for(int i = 0 ; i < n ; i++){
		s[i] == '1' ? s[i] = '0' : s[i] = '1';
        if (!p[s]) dfs(s);
        s[i] == '1' ? s[i] = '0' : s[i] = '1';
	}
 
}
 
int main(){
 
	cin >> n ; 
 
	for(int i = 1 ; i <= n ; i++) s += '0' ; 
 
	dfs(s) ; 
 
}
