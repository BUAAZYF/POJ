#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

short inline max(short a, short b) {
    return a >= b ? a : b;
}

struct Point {
    double x, y;
};

double dist(Point& a, Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    // freopen("in.txt", "r", stdin);
    vector<Point> coord;
    Point p;
    while (scanf("%lf%lf", &p.x, &p.y) != EOF) coord.push_back(p);
    int ans = 0;
    for (int i = 0; i < coord.size(); ++i) {
        int c = 0;
        p = coord[i];
        for (int j = 0; j < coord.size(); ++j)
            if (dist(coord[j], p) <= 2.5 + 1e-6) ++c;
        ans = max(ans, c);
        for (int j = i + 1; j < coord.size() - 1; ++j) {
            double q = dist(coord[i], coord[j]);
            if (q <= 5 + 1e-6) {
                double fact = sqrt(6.25 - pow(q, 2) / 4 + 1e-6);
                p.x = (coord[i].x + coord[j].x) / 2 + fact * (coord[i].y - coord[j].y) / q;
                p.y = (coord[i].y + coord[j].y) / 2 + fact * (coord[j].x - coord[i].x) / q;
                c = 0;
                for (int k = 0; k < coord.size(); ++k)
                    if (dist(coord[k], p) <= 2.5 + 1e-6) ++c;
                ans = max(ans, c);
                p.x = (coord[i].x + coord[j].x) / 2 - fact * (coord[i].y - coord[j].y) / q;
                p.y = (coord[i].y + coord[j].y) / 2 - fact * (coord[j].x - coord[i].x) / q;
                c = 0;
                for (int k = 0; k < coord.size(); ++k)
                    if (dist(coord[k], p) <= 2.5 + 1e-6) ++c;
                ans = max(ans, c);
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}