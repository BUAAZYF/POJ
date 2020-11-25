#include <cmath>
#include <cstdio>

using namespace std;

const int MAX = 100005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, k, a[MAX], low, high, mid, ans;

int main() {
    while (scanf("%d", &n) != EOF) {
        low = 1, high = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            high = max(high, a[i]);
        }
        scanf("%d", &k);
        if (k == 1) {
            printf("%d\n", high);
            continue;
        }
        long long cnt;
        while (low <= high) {
            mid = (high - low) / 2 + low;
            cnt = 0;
            for (int i = 0; i < n; ++i)
                if (a[i] > mid) cnt += (long long)ceil(double(a[i] - mid) / (k - 1));
            if (cnt <= mid) {
                ans = mid;
                high = mid - 1;
            } else low = mid + 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}