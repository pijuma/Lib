struct point{
    double x, y;
    // construtor
    point(double x=0, double y=0){
        this->x = x;
        this->y = y;
    }
    
    // operadores
    point operator+(const point& P){
        point R;
        R.x = x + P.x;
        R.y = y + P.y;
        return R;
    }
    point operator-(const point& P){
        point R;
        R.x = x - P.x;
        R.y = y - P.y;
        return R;
    }
    point operator*(const double& t){
        point R;
        R.x = t*x;
        R.y = t*y;
        return R;
    }
};

struct circle{
    point center;
    double radius;
    // construtor
    circle(point center=point(0, 0), double radius=0){
        this->center = center;
        this->radius = radius;
    }
};

double dist(point& A, point& B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

bool is_inside(point& P, circle& c){
    return dist(P, c.center)<=c.radius;
}

circle circumcircle(point& A, point& B, point& C){
    point P = B-A;
    point Q = C-A;
    
    double b = P.x*P.x + P.y*P.y;
    double c = Q.x*Q.x + Q.y*Q.y;
    double d = P.x*Q.y - P.y*Q.x;
    
    point center = point((Q.y*b - P.y*c)/(2*d), (P.x*c - Q.x*b)/(2*d));
    center = center+A;
    
    double radius = dist(A, center);
    
    return circle(center, radius);
}

circle circumcircle(point& A, point& B){
    point center = (A+B)*(0.5);
    double radius = dist(A, B)/2;
    return circle(center, radius);
}

circle welzl_trivial(vector<point>& dots){
    assert(dots.size()<=3);
    
    if(dots.empty()) return circle(point(0, 0), 0);
    if(dots.size()==1) return circle(dots[0], 0);
    if(dots.size()==2) return circumcircle(dots[0], dots[1]);
    
    circle c;
    c = circumcircle(dots[1], dots[2]);
    if(is_inside(dots[0], c)) return c;
    
    c = circumcircle(dots[2], dots[0]);
    if(is_inside(dots[1], c)) return c;
    
    c = circumcircle(dots[0], dots[1]);
    if(is_inside(dots[2], c)) return c;
    
    return circumcircle(dots[0], dots[1], dots[2]);
}

circle welzl_helper(vector<point>& dots, vector<point> bound, int n){
    if(n==0 or bound.size()==3)
        return welzl_trivial(bound);
        
    int id = rand() % n;
    point p = dots[id];
    
    swap(dots[id], dots[n-1]);
    circle c = welzl_helper(dots, bound, n-1);
    
    if(is_inside(p, c)) return c;
    
    bound.push_back(p);
    return welzl_helper(dots, bound, n-1);
}

circle welzl(const vector<point>& dots){
    vector<point> dots_copy = dots;
    random_shuffle(dots_copy.begin(), dots_copy.end());
    return welzl_helper(dots_copy, {}, dots_copy.size());
}
