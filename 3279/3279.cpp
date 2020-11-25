#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 17;

int M, N, ans;
int tile[MAX][MAX], opt[MAX][MAX], flip[MAX][MAX];
const int dx[5] = {-1, 1, 0, 0, 0};
const int dy[5] = {0, 0, 0, -1, 1};

int access(int x, int y) {
    int cur = tile[x][y], nx, ny;
    for (int i = 0; i < 5; ++i) {
        nx = x + dx[i], ny = y + dy[i];
        if (0 <= nx && nx < M && 0 <= ny && ny < N) cur += flip[nx][ny];
    }
    return cur % 2;
}

int cal() {
    for (int i = 1; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (access(i - 1, j) != 0) flip[i][j] = 1;
    for (int j = 0; j < N; ++j)
        if (access(M - 1, j) != 0) return -1;
    int ans = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) ans += flip[i][j];
    return ans;
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) scanf("%d", &tile[i][j]);
    ans = -1;
    for (int i = 0; i < 1 << N; ++i) {
        memset(flip, 0, sizeof(flip));
        for (int j = 0; j < N; ++j) flip[0][N - 1 - j] = (i >> j) & 1;
        int cur = cal();
        if (cur >= 0 && (ans < 0 || ans > cur)) {
            ans = cur;
            memcpy(opt, flip, sizeof(flip));
        }
    }
    if (ans == -1)
        printf("IMPOSSIBLE\n");
    else {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N - 1; ++j) printf("%d ", opt[i][j]);
            printf("%d\n", opt[i][N - 1]);
        }
    }

    return 0;
}
