//encontra a soma de minkowski dos poligonos a e b (devem ser CCW)
void reorder(vector<P> &p){
    int best = 0;
    rep(i, 1, sz(p))
        if(p[best].y > p[i].y or (p[best].y == p[i].y and p[best].x > p[i].x)){
            best = i;
    }
    rotate(p.begin(), p.begin() + best, p.end());
}
vector<P> minkowski(vector<P> a, vector<P> b){
    reorder(a); reorder(b);
    int na = sz(a), nb = sz(b);
    vector<P> res;

    a.push_back(a[0]); a.push_back(a[1]);
    b.push_back(b[0]); b.push_back(b[1]);

    int i = 0, j = 0;
    while(i < na or j < nb){
        res.push_back(a[i]+b[j]);
        ll k = (b[j+1]-b[j]).cross(a[i+1]-a[i]);
        if(k >= 0 and j < nb) j++;
        if(k <= 0 and i < na) i++;
    }
    return res;
}
