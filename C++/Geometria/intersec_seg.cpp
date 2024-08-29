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
 
bool intersect(point a, point b, point c, point d){
    point p[4] = {a, c, b, d};
    
    int sig = 0;
    bool ans = true;
    bool all_zeros = true;
    for(int i=0; i<4; i++){
        point u = p[(i+3)%4]-p[i];
        point v = p[(i+1)%4]-p[i];
        double a = u^v;
        
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
    
    return ans;
}
 
bool in_segment(point a, point b, point c){ // a em bc
    return dist(a, b)+dist(a, c)-dist(b, c)<1e-9;
}
 
int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    
    return 0;
}
