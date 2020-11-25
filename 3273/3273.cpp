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

int N, M, cost[MAX], ans;

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        int low = 0, high = 0, mid, cnt, cur;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &cost[i]);
            low = max(low, cost[i]);
            high += cost[i];
        }
        ans = high;
        while (low <= high) {
            mid = (low + high) >> 1;
            cur = cnt = 0;
            for (int i = 0; i < N; ++i) {
                if (cur + cost[i] > mid) {
                    ++cnt;
                    cur = cost[i];
                } else cur += cost[i];
            }
            if (cur != 0) ++cnt;
            
            if (cnt <= M) {
                ans = min(ans, mid);
                high = mid - 1;
            } else low = mid + 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}