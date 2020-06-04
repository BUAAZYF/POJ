#include <cstdio>

using namespace std;

const int MAX = 100;

int n, m, ans;
char filed[MAX][MAX + 1];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || filed[x][y] == '.') return;
    filed[x][y] = '.';
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
            dfs(x + dx, y + dy);
}
int main() {
    // freopen("in.txt", "r", stdin);
    ans = 0;
    scanf("%d%d\n", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%s", &filed[i]);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (filed[i][j] == 'W') {
                ++ans;
                dfs(i, j);
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}