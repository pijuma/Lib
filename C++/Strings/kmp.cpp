//pi[i] = maior pref [0, ...i] tal que é um sufixo de [i, i-1,...,i-k+1] 
vector<int> table(){
	vector<int> ans(pattern.size(), 0) ; 
	int j = 0 ; 
	for(int i = 1 ; i < pattern.size() ; i++){
		while(j > 0 && pattern[i] != pattern[j]) j = ans[j-1] ; 
		if(pattern[i] == pattern[j]) j++ ; 
		ans[i] = j ; 
	}
	return ans ; 
}

vector<int> kmp(vector<int> pi){
	vector<int> ans(s.size(), 0) ; 
	int j = 0 ; 
	for(int i = 0 ; i < s.size() ; i++){
		while(j > 0 && pattern[j] != s[i]) j = pi[j-1] ; 
		if(pattern[j] == s[i]) j++ ; 
		ans[i] = j ; 
	}
	return ans ; 
}

string p;
int neighbor[N];
int walk(int u, char c) { // leader after inputting `c`
    while (u != -1 && (u+1 >= (int)p.size() || p[u + 1] != c)) // leader doesn't match
        u = neighbor[u];
    return p[u + 1] == c ? u+1 : u;
}
void build() {
    neighbor[0] = -1; // -1 is the leftmost state
    for (int i = 1; i < (int)p.size(); i++)
        neighbor[i] = walk(neighbor[i-1], p[i]);
}
