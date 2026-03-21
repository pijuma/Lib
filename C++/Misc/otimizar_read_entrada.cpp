// quao mais rapido eh doq ler cada numero?? 
cin.ignore() ;
    
for(int i = 0 ; i < n ; i++){
    string ln;
    getline(cin, ln);
    for (int j = 0; j < n; ++j) {
        a[i][j] = ln[2 * j] - '0';
    }
}
