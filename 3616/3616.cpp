#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1005;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

inline int min(int a, int b) {
    return a <= b ? a : b;
}

struct interval {
    int start;
    int end;
    long efficiency;
    friend bool operator<(const interval& a, const interval& b) {
        return a.start < b.start || a.start == b.start && a.end < b.end;
    }
} intervals[MAXN];

int N, M, R;
long ans, dp[MAXN];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &N, &M, &R);
    for (int i = 0; i < M; ++i) scanf("%d%d%ld", &intervals[i].start, &intervals[i].end, &intervals[i].efficiency);
    sort(intervals, intervals + M);
    ans = 0;
    for (int i = 0; i < M; ++i) {
        dp[i] = 0;
        for (int j = i - 1; j >= 0; --j) {
            if (intervals[j].end + R > intervals[i].start) continue;
            dp[i] = max(dp[i], dp[j]);
        }
        dp[i] += intervals[i].efficiency;
        ans = max(ans, dp[i]);
    }
    printf("%ld\n", ans);

    return 0;
}