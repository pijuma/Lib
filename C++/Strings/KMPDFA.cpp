struct KMP{
        string P;
        int n; 
        vector<int> neighbor;
        vector<vector<int> > dfa;

        KMP(string& p){
            P = p;
            n = (int)P.size();
            neighbor.resize(n+1);
            neighbor[1] = 0; // starting node is always alive
            for(int k = 1; k < n; k++){
                neighbor[k+1] = next_leader(neighbor[k], P[k]);

            }
            build_dfa();
        }

        bool match(int state, char c){
            return state < n and P[state] == c;
        }

        int next_leader(int leader, char input){
            if(leader == 0) return P[0] == input;
            //ou avança pra 1 ou fica no inicio
            if(match(leader, input)) return leader+1;
            else return next_leader(neighbor[leader], input);
        }

        void build_dfa(){
            dfa.assign(n + 1, vector<int>(26, 0));
            dfa[0][P[0]-'A'] = 1; //only way to advance at 0
            for(int k = 1; k <= n; k++)
            for(int c = 0; c < 26; c++)
                if (k < n and P[k] == 'A'+c) dfa[k][c] = k+1;
                else dfa[k][c] = dfa[neighbor[k]][c];
        }

    };

    int dp[1010][110][2];

    void solve(int TIMES){
        int n;

        cin >> n;

        string p;

        cin >> p;

        KMP kmp(p);

        dp[0][0][0] = 1;

        fr1(i, n){
            for(int j=0;j<=sz(p);j++){
                fr(c, 26){
                    int nextState = kmp.dfa[j][c]; // estou no estado j e input c retorna o proximo estado

                    if(nextState == p.size()){
                        dp[i][nextState][0] += 0;
                        dp[i][nextState][1] += (dp[i-1][j][1] + dp[i-1][j][0])%MOD;
                        dp[i][nextState][1]%=MOD;
                    }else{
                        dp[i][nextState][0] += dp[i-1][j][0];
                        dp[i][nextState][0]%=MOD;
                        dp[i][nextState][1] += dp[i-1][j][1];
                        dp[i][nextState][1]%=MOD;
                    }

                }
            }
        }

        int ans = 0;
        for(int j=0;j<=sz(p);j++){
            ans+=dp[n][j][1];
            ans%=MOD;
        }

        cout << ans << '\n';
    }
