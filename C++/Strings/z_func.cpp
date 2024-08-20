//z[i] = maior pref começando em i que tambem eh pref da palavra original 
//ex.: aabaabaa
//i = 3 -> AABAA e AABAABAA logo z[3] = 5
vector<int> Z(string s) {
    int n = s.size();
    vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - x], y - i + 1));
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            x = i; y = i + z[i]; z[i]++;
        }
    }
    return z;
}
