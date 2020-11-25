#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 4005;

int n, len, ans;
int A[MAX], B[MAX], C[MAX], D[MAX];
int cnt[MAX * MAX];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
    len = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cnt[len++] = A[i] + B[j];
    ans = 0;
    sort(cnt, cnt + n * n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            ans += upper_bound(cnt, cnt + n * n, -C[i] - D[j]) - lower_bound(cnt, cnt + n * n, -C[i] - D[j]);
    printf("%d\n", ans);

    return 0;
}
