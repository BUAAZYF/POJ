#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 27;
const int DIRECTION = 8;

int t, p, q;
bool board[MAXN][MAXN];
int path[MAXN * 2];
int dx[DIRECTION] = {-1, 1, -2, 2, -2, 2, -1, 1};
int dy[DIRECTION] = {-2, -2, -1, -1, 1, 1, 2, 2};

bool checkvalid(int x, int y) {
    return x >= 1 && x <= p && y >= 1 && y <= q && !board[x][y];
}

bool dfs(int x, int y, int cnt) {
    if (cnt == p * q) {
        path[(cnt - 1) * 2] = x;
        path[(cnt - 1) * 2 + 1] = y;
        return true;
    }
    int nx, ny;
    for (int i = 0; i < DIRECTION; ++i) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (checkvalid(nx, ny)) {
            board[nx][ny] = true;
            if (dfs(nx, ny, cnt + 1)) {
                path[(cnt - 1) * 2] = x;
                path[(cnt - 1) * 2 + 1] = y;
                return true;
            }
            board[nx][ny] = false;
        }
    }
    return false;
}
int main() {
    scanf("%d", &t);
    for (int c = 1; c <= t; ++c) {
        scanf("%d%d", &p, &q);
        memset(board, 0, sizeof(board));
        memset(path, false, sizeof(path));
        printf("Scenario #%d:\n", c);
        board[1][1] = true;
        if (dfs(1, 1, 1)) {
            for (int i = 0; i < p * q; ++i) printf("%c%d", char(path[i * 2 + 1] + 'A' - 1), path[i * 2]);
        } else {
            printf("impossible");
        }
        printf("\n\n");
    }

    return 0;
}