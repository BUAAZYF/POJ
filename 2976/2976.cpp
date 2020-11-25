#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 1005;
const double EPS = 0.00001;

double inline max(double a, double b) {
    return a >= b ? a : b;
}

int n, k;
ll a[MAX], b[MAX];
double left[MAX], low, high, mid, cur, ans;

int main() {
    while (scanf("%d%d", &n, &k) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
        for (int i = 0; i < n; ++i) scanf("%lld", &b[i]);
        ans = 0;
        low = 0, high = 1;
        while (low + EPS <= high) {
            mid = (high + low) / 2;
            for (int i = 0; i < n; ++i) left[i] = a[i] - mid * b[i];
            sort(left, left + n);
            cur = 0;
            for (int i = 0; i < n - k; ++i) cur += left[n - 1 - i];
            if (cur >= 0) {
                if (mid > ans) ans = mid;
                low = mid;
            } else high = mid;
        }
        printf("%d\n", (int)round(ans * 100));
    }

    return 0;
}