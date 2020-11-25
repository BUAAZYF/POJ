#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAX = 105;
const double G = 10.0;

int C, N, H, R, T;
double height[MAX];

double cal(int T) {
    if (T < 0) return H;
    double t = sqrt(2 * H / G);
    int k = int(T / t);
    double d;
    if (k % 2 == 0) d = T - k * t;
    else  d = k * t + t - T;
    return H - G * d * d / 2;
}

int main() {
    scanf("%d", &C);
    while (C--) {
        scanf("%d%d%d%d", &N, &H, &R, &T);
        for (int i = 0; i < N; ++i) height[i] = cal(T - i);
        sort(height, height + N);
        for (int i = 0; i < N; ++i) printf("%.2f%c", height[i] + 2 * R * i / 100.0, i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
