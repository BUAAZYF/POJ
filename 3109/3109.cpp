#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 100005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, bit[MAX], mx[MAX];
bool sc[MAX];
long long ans;
struct point {
    int x, y;
} points[MAX];

void add(int idx, int v) {
    for (; idx <= N; idx += idx & -idx) bit[idx] += v;
}

int sum(int idx) {
    int ret = 0;
    for (; idx > 0; idx -= idx & -idx) ret += bit[idx];
    return ret;
}

bool cmpx(const point& a, const point& b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cmpy(const point& a, const point& b) {
    return a.y < b.y || a.y == b.y && a.x < b.x;
}

int main() {
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 0; i < N; ++i) scanf("%d%d", &points[i].x, &points[i].y);
        sort(points, points + N, cmpx);
        int val = 1, temp;
        for (int i = 0; i < N; ++i) {
            temp = points[i].x;
            points[i].x = val;
            if (temp != points[i + 1].x) ++val;
        }
        sort(points, points + N, cmpy);
        val = 1;
        for (int i = 0; i < N; ++i) {
            temp = points[i].y;
            points[i].y = val;
            if (temp != points[i + 1].y) ++val;
        }
        fill(mx, mx + MAX, 0);
        fill(sc, sc + MAX, false);
        for (int i = 0; i < N; ++i) mx[points[i].x] = max(mx[points[i].x], points[i].y);
        ans = 0;
        fill(bit, bit + MAX, 0);
        for (int i = 0; i < N - 1; ++i) {
            int x = points[i].x, y = points[i].y, nx = points[i + 1].x, ny = points[i + 1].y;
            if (!sc[x] && y < mx[x]) {
                sc[x] = true;
                add(x, 1);
            }
            if (y == ny && nx > x + 1) ans += sum(nx - 1) - sum(x);
            if (sc[x] && y == mx[x]) {
                sc[x] = false;
                add(x, -1);
            }
        }
        ans += N;
        printf("%lld\n", ans);
    }

    return 0;
}