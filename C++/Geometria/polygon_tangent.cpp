typedef Point<long long> P; //usando ponto do kactl
vector<P> poly;

int extreme(const function<bool(P, P)> &cmp) {
    auto isExtreme = [&](int i, bool& curDir) -> bool {
        curDir = cmp(poly[(i + 1) % n], poly[i]);
        return !cmp(poly[(i + n - 1) % n], poly[i]) && !curDir;
    };
    bool lastDir, curDir;
    if(isExtreme(0, lastDir)) return 0;
    int lo = 0, hi = n; 
    while(lo + 1 < hi) {
        int m = (lo + hi) >> 1;
        if(isExtreme(m, curDir)) return m;
        bool relDir = cmp(poly[m], poly[lo]);
        if((!lastDir && curDir) || (lastDir == curDir && relDir == curDir)) {
            lo = m;
            lastDir = curDir;
        } else hi = m;
    }
    return lo;
}
ll area2(P a, P b, P c) { // two times signed area of triangle abc
	return (b - a).cross(c - a);
}
bool left(P a, P b, P c) {
	return area2(a, b, c) > 0; // counterclockwise
}
bool right(P a, P b, P c) {
	return area2(a, b, c) < 0; // clockwise
}
pair<int, int> tangent(P q) { // O(log n) for convex polygon in ccw orientation
    // Finds the indices of the two tangents to an external point q
    auto leftTangent = [&](P r, P s) -> bool {
        return right(q, r, s);
    };
    auto rightTangent = [&](P r, P s) -> bool {
        return left(q, r, s);
    };
    return {extreme(leftTangent), extreme(rightTangent)};
}
