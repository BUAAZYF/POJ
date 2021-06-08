#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 15;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int n, x1, y1, x2, y2, s1, s2;
bool connect[MAX][MAX];

struct pt {
    int x, y;
    pt() {}
    pt(int _x, int _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    int cross(const pt& p) const { return x * p.y - y * p.x; }
    int cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
};

struct seg {
    pt p1, p2;
    seg() {}
    seg(int x1, int y1, int x2, int y2) {
        p1 = pt(x1, y1);
        p2 = pt(x2, y2);
    }
} segs[MAX];

int sgn(const int& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter(int a, int b, int c, int d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0) return inter(a.x, b.x, c.x, d.x) && inter(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

bool check_inter(seg& s1, seg& s2) {
    return check_inter(s1.p1, s1.p2, s2.p1, s2.p2);
}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            segs[i] = seg(x1, y1, x2, y2);
        }
        memset(&connect[0][0], false, MAX * MAX * sizeof(bool));
        for (int i = 1; i <= n; ++i) {
            connect[i][i] = true;
            for (int j = i + 1; j <= n; ++j)
                connect[i][j] = connect[j][i] = check_inter(segs[i], segs[j]);
        }
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    connect[i][j] |= connect[i][k] & connect[k][j];
        while (scanf("%d%d", &s1, &s2) != EOF && s1 + s2)
            printf("%s\n", connect[s1][s2] ? "CONNECTED" : "NOT CONNECTED");
    }

    return 0;
}