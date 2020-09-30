#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAX = 10005;
int n, k;
double cable[MAX];

bool check(double x) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) cnt += (cable[i] / x);
    return cnt >= k;
}

int main() {
    while (scanf("%d%d", &n, &k) != EOF && n) {
        double l = 0, r = -1, ans = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%lf", &cable[i]);
            r = max(r, cable[i]);
        }
        int L = 0, R = r * 100;
        while (L <= R) {
            int mid = L + (R - L) / 2;
            if (check((double)mid / 100)) {
                ans = mid;
                L = mid + 1;
            } else R = mid - 1;
        }
        ans /= 100;
        if (ans < 0.01) printf("0.00\n");
        else printf("%.2f\n", ans);
    }

    return 0;
}