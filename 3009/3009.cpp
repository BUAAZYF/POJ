#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 25;
int w, h;
int sx, sy, gx, gy, ans;
int board[MAX][MAX];
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, 1, -1};

inline bool checkrange(int nx, int ny) {
    return nx >= 0 && nx < h && ny >= 0 && ny < w;
}

void dfs(int x, int y, int step) {
    if (step >= ans) return;
    int cnt, nx, ny;
    for (int i = 0; i < 4; ++i) {
        nx = x + dx[i];
        ny = y + dy[i];
        cnt = 0;
        while (checkrange(nx, ny) && board[nx][ny] == 0) {
            cnt += 1;
            nx += dx[i];
            ny += dy[i];
        }
        if (!checkrange(nx, ny)) continue;
        if (board[nx][ny] == 3)
            ans = min(ans, step + 1);
        else if (cnt > 0) {
            board[nx][ny] = 0;
            dfs(nx - dx[i], ny - dy[i], step + 1);
            board[nx][ny] = 1;
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d\n", &w, &h) != EOF and w != 0) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                scanf("%d", &board[i][j]);
                if (board[i][j] == 2) {
                    sx = i;
                    sy = j;
                    board[i][j] = 0;
                } else if (board[i][j] == 3) {
                    gx = i;
                    gy = j;
                }
            }
        }
        ans = 11;
        dfs(sx, sy, 0);
        printf("%d\n", ans == 11 ? -1 : ans);
    }

    return 0;
}