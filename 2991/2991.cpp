#include <cmath>
#include <cstdio>

using namespace std;

const int MAX = 10005;
const double PI = 3.14159265358979323846;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, C, idx, angle, widths[MAX], prev[MAX];
struct crane {
    double x, y;
    int angle;
} cranes[MAX * 4];
double sintable[361], costable[361];

void calangle() {
    double arc;
    for (int i = 0; i <= 360; ++i) {
        arc = i / 180.0 * PI;
        sintable[i] = sin(arc);
        costable[i] = cos(arc);
    }
}

void build(int v, int tl, int tr) {
    cranes[v].x = cranes[v].angle = 0;
    if (tl == tr) {
        cranes[v].y = widths[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        cranes[v].y = cranes[v * 2].y + cranes[v * 2 + 1].y;
    }
}

void update(int v, int tl, int tr, int pos, int angle) {
    if (pos < tl || tl >= tr) return;
    int tm = (tl + tr) / 2;
    if (pos <= tm) update(v * 2, tl, tm, pos, angle);
    else update(v * 2 + 1, tm + 1, tr, pos, angle);
    if (pos <= tm) cranes[v].angle = (cranes[v].angle + angle + 360) % 360;
    double s = sintable[cranes[v].angle], c = costable[cranes[v].angle];
    cranes[v].x = cranes[2 * v].x + (c * cranes[2 * v + 1].x - s * cranes[2 * v + 1].y);
    cranes[v].y = cranes[2 * v].y + (s * cranes[2 * v + 1].x + c * cranes[2 * v + 1].y);
}

int main() {
    calangle();
    while (scanf("%d%d", &N, &C) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d", &widths[i]);
            prev[i] = 180;
        }
        build(1, 0, N - 1);
        for (int i = 0; i < C; ++i) {
            scanf("%d%d", &idx, &angle);
            --idx;
            update(1, 0, N - 1, idx, angle - prev[idx]);
            prev[idx] = angle;
            printf("%.2f %.2f\n", cranes[1].x, cranes[1].y);
        }
        printf("\n");
    }

    return 0;
}