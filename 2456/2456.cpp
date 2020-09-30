#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 100005;

int n, m, low, high, mid, ans;
int stalls[MAX];

int inline max(int a, int b) {
    return a >= b ? a : b;
}

bool check(int x) {
    int cnt = 1, last = 0;
    for (int i = 0; i < n; ++i) {
        if (stalls[i] - stalls[last] >= x) {
            ++cnt;
            last = i;
        }
    }
    return cnt >= m;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d", &stalls[i]);
        sort(stalls, stalls + n);
        low = 0, high = stalls[n - 1] - stalls[0];
        ans = 0;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = max(ans, mid);
                low = mid + 1;
            } else high = mid - 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}