#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 100005;

ll inline min(ll a, ll b) {
    return a <= b ? a : b;
}

int n, cnt, lc, sc;
ll a[MAX], low, high, mid, ans;

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
        cnt = n * (n - 1) / 2;
        cnt = (cnt + 1) / 2;
        sort(a, a + n);
        low = a[n - 1], high = a[n - 1] - a[0];
        for (int i = 0; i < n - 1; ++i) low = min(low, a[i + 1] - a[i]);
        while (low <= high) {
            mid = (low + high) >> 1;
            lc = sc = 0;
            for (int i = 0; i < n - 1; ++i) {
                lc += lower_bound(a + i + 1, a + n, a[i] + mid) - (a + i + 1);
                sc += upper_bound(a + i + 1, a + n, a[i] + mid) - (a + i + 1);
            }
            if (lc < cnt && sc >= cnt) {
                ans = mid;
                break;
            } else if (sc < cnt) low = mid + 1;
            else high = mid - 1;
        }
        printf("%lld\n", ans);
    }

    return 0;
}