#include <cstdio>
#include <cstring>

using namespace std;

const int ROW = 5;
const int COL = 6;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int n, tile[ROW][COL], opt[ROW][COL], flip[ROW][COL];
const int dx[5] = {-1, 1, 0, 0, 0};
const int dy[5] = {0, 0, 0, -1, 1};

int access(int x, int y) {
    int cur = tile[x][y], nx, ny;
    for (int i = 0; i < 5; ++i) {
        nx = x + dx[i], ny = y + dy[i];
        if (0 <= nx && nx < ROW && 0 <= ny && ny < COL) cur += flip[nx][ny];
    }
    return cur % 2;
}

int cal() {
    for (int i = 1; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            if (access(i - 1, j) != 0) flip[i][j] = 1;
    for (int j = 0; j < COL; ++j)
        if (access(ROW - 1, j) != 0) return -1;
    int ans = 0;
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j) ans += flip[i][j];
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int t = 1; t <= n; ++t) {
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j) scanf("%d", &tile[i][j]);
        for (int i = 0; i < 1 << COL; ++i) {
            memset(flip, 0, sizeof(flip));
            for (int j = 0; j < COL; ++j) flip[0][COL - 1 - j] = (i >> j) & 1;
            if (cal() >= 0) {
                memcpy(opt, flip, sizeof(flip));
                break;
            }
        }
        printf("PUZZLE #%d\n", t);
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL - 1; ++j) printf("%d ", opt[i][j]);
            printf("%d\n", opt[i][COL - 1]);
        }
    }

    return 0;
}