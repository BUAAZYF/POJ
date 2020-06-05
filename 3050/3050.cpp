#include <cstdio>
#include <set>

using namespace std;

const int MAX = 5;
int nx, ny;
int grid[MAX][MAX];
set<int> nums;
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

bool checkrange(int x, int y) {
    return x >= 0 && x < MAX && y >= 0 && y < MAX;
}

void dfs(int x, int y, int step, int num) {
    if (step == MAX) {
        nums.insert(num);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (checkrange(nx, ny)) dfs(nx, ny, step + 1, num * 10 + grid[nx][ny]);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            scanf("%d", &grid[i][j]);
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            dfs(i, j, 0, grid[i][j]);
    printf("%d\n", nums.size());

    return 0;
}