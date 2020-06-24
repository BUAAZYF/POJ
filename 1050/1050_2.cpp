#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 105;
const int INF = 0x3f3f3f3f;

short inline max(short a, short b) {
    return a >= b ? a : b;
}
int n, rowsum, ans;
int matrix[MAX][MAX];
int partsum[MAX][MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &matrix[i][j]);
    memset(partsum, 0, MAX * MAX * sizeof(int));
    ans = matrix[0][0];
    for (int i = 1; i <= n; ++i) {
        rowsum = 0;
        for (int j = 1; j <= n; ++j) {
            rowsum += matrix[i][j];
            partsum[i][j] = partsum[i - 1][j] + rowsum;
        }
    }
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int y1 = 1; y1 <= n; ++y1) {
            for (int x2 = x1; x2 <= n; ++x2) {
                for (int y2 = y1; y2 <= n; ++y2) {
                    ans = max(ans, partsum[x2][y2] - partsum[x2][y1 - 1] - partsum[x1 - 1][y2] + partsum[x1 - 1][y1 - 1]);
                }
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}