#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 55;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

int N, M, roomcnt, largestroom;
int walls[MAX][MAX];
bool visited[MAX][MAX];

int directons[4] = {1, 2, 4, 8};
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || visited[x][y]) return 0;
    visited[x][y] = true;
    int cnt = 1;
    for (int i = 0; i < 4; ++i) {
        if ((walls[x][y] & directons[i]) == 0)
            cnt += dfs(x + dx[i], y + dy[i]); 
    }
    return cnt;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            scanf("%d", &walls[i][j]);
    memset(visited, false, sizeof(visited));
    roomcnt = largestroom = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            if (!visited[i][j]) {
                ++roomcnt;
                largestroom = max(largestroom, dfs(i, j));
            }
        }
    printf("%d\n%d\n", roomcnt, largestroom);

    return 0;
}