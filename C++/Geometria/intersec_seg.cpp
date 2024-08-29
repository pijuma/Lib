#include <bits/stdc++.h>
using namespace std;

#define int long long

struct point{
    double x, y;
    // construtor
    point(double x=0, double y=0){
        this->x = x;
        this->y = y;
    }
    
    // operadores
    point operator+(const point& P){
        return point(x+P.x, y+P.y);
    }
    point operator-(const point& P){
        return point(x-P.x, y-P.y);
    }
    point operator*(const double& t){
        return point(t*x, t*y);
    }
    double operator*(const point& P){
        return P.x*x+P.y*y;
    }
    double operator^(const point& P){
        return x*P.y-y*P.x;
    }
};

double dist(point a, point b){
    return sqrt((a-b)*(a-b));
}

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    
    point p[4];
    int t; cin>>t;
    while(t--){
        int x, y;
        cin>>x>>y; p[0] = point(x, y);
        cin>>x>>y; p[2] = point(x, y);
        cin>>x>>y; p[1] = point(x, y);
        cin>>x>>y; p[3] = point(x, y);
        
        vector<int> area;
        for(int i=0; i<4; i++){
            point u = p[(i+3)%4]-p[i];
            point v = p[(i+1)%4]-p[i];
            area.push_back(u^v);
        }
        
        int sig = 0;
        bool ans = true;
        bool all_zeros = true;
        for(double a : area){
            if(a>0){
                all_zeros = false;
                if(sig==0) sig = 1;
                if(sig<0) ans = false;   
            }
            if(a<0){
                all_zeros = false;
                if(sig==0) sig = -1;
                if(sig>0) ans = false;
            }
        }
        
        if(all_zeros){
            double len = 0;
            for(int i=0; i<4; i++)
                for(int j=0; j<i; j++)
                    len = max(len, dist(p[i], p[j]));
            if(dist(p[0], p[2])+dist(p[1], p[3]) < len)
                ans = false;
        }
        
        if(ans) cout<<"YES\n";
        else cout<<"NO\n";
    }
    
    return 0;
}
