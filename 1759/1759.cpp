#include <cstdio>

using namespace std;

const int MAXN = 1000;
const int INF = 0x3f3f3f3f;

double inline min(double a, double b) {
    return a <= b ? a : b;
}

int N;
double A, xn, pre2, pre1, ans;

int main() {
    while (scanf("%d%lf", &N, &A) != EOF) {
        if (N == 3) {
            printf("0.00\n");
            continue;
        }
        ans = INF;
        for (int n = 1; n <= N - 2; ++n) {
            xn = (A + (n - 1) * (n - 2) - 2 - 2 * n * (n - 1)) / (n + 1);
            if (xn <= 0) break;
            pre2 = xn, pre1 = 0, xn = 0;
            for (int i = 0; i < N - n - 2; ++i) {
                xn = 2 * pre1 - pre2 + 2;
                if (xn < 0 || (ans != INF && ans > xn)) break;
                pre2 = pre1;
                pre1 = xn;
            }
            if (xn >= 0) ans = min(ans, xn);
        }
        printf("%.2f\n", ans);
    }
    return 0;
}