#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

typedef pair<double, int> Pr;

const int MAX = 100005;
const double EPS = 0.000001;

double inline max(double a, double b) {
    return a >= b ? a : b;
}

int n, k, v[MAX], w[MAX], keep[MAX];
double low, high, mid, cur, ans;
Pr left[MAX];

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    low = 0, high = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &v[i], &w[i]);
        high = max(high, v[i]);
    }
    for (int i = 0; i < k; ++i) keep[i] = i + 1;
    ans = 0;
    while (low + EPS <= high) {
        mid = (high + low) / 2;
        for (int i = 0; i < n; ++i) left[i] = make_pair(v[i] - mid * w[i], i + 1);
        sort(left, left + n);
        cur = 0;
        for (int i = 0; i < k; ++i) cur += left[n - 1 - i].first;
        if (cur >= 0) {
            if (mid > ans) {
                ans = mid;
                for (int i = 0; i < k; ++i) keep[i] = left[n - 1 - i].second;
            }
            low = mid;
        } else high = mid;
    }
    sort(keep, keep + k);
    for (int i = 0; i < k - 1; ++i) printf("%d ", keep[i]);
    printf("%d\n", keep[k - 1]);

    return 0;
}