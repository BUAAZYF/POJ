#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 100005;
const int INF = 0x3f3f3f3f;

int inline intabs(int a) {
    return a >= 0 ? a : -a;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, k, t, cur, L, R, ans, mindis;
int a[MAX];
Pr presum[MAX];

int main() {
    while (scanf("%d%d", &n, &k) != EOF && n) {
        cur = 0;
        presum[0] = make_pair(0, 0);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            cur += a[i];
            presum[i] = make_pair(cur, i);
        }
        sort(presum, presum + n + 1);
        while (k--) {
            scanf("%d", &t);
            L = R = 0;
            int i = 0, j = 1;
            mindis = INF;
            while (j <= n) {
                cur = presum[j].first - presum[i].first;
                if (intabs(cur - t) < mindis) {
                    mindis = intabs(cur - t);
                    ans = cur;
                    L = presum[i].second;
                    R = presum[j].second;
                }
                if (ans == t) break;
                if (cur > t) ++i;
                else ++j;
                if (i == j) ++j;
            }
            if (R < L) swap(L, R);
            printf("%d %d %d\n", ans, L + 1, R);
        }
    }

    return 0;
};