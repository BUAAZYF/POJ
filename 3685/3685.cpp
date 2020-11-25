#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;

ll inline min(ll a, ll b) {
    return a <= b ? a : b;
}

ll inline max(ll a, ll b) {
    return a >= b ? a : b;
}

ll t, n, m, low, high, mid, lc, sc, b, c, ans;
double tmp;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        low = n * n + 1 - 100000 * n + 100000 + n;
        high = max(n * n + 1 + 100000 * n - 100000 + n, n * n * 3);
        ans = high;
        while (low <= high) {
            lc = sc = 0;
            mid = (low + high) / 2;
            for (ll j = 1; j <= n; ++j) {
                b = 100000 + j;
                c = j * j - 100000 * j - mid;
                tmp = (-b + sqrt(b * b - 4 * c)) / 2;
                if (tmp < 1) continue;
                lc += min((ll)tmp, n);
                if (tmp <= n && (double)((ll)tmp) == tmp) {
                    --lc;
                    ++sc;
                }
            }
            if (lc < m && lc + sc >= m) {
                ans = mid;
                break;
            } else if (lc + sc < m) low = mid + 1;
            else high = mid - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}