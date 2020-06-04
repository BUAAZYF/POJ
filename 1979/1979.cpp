#include <cstdio>
#include <queue>

using namespace std;

const int MAX = 25;
int w, h;
int x, y, ans;
char room[MAX][MAX];
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, 1, -1};

void dfs(int x, int y) {
    if (x < 0 || x >= h || y < 0 || y >= w || room[x][y] == '#') return;
    ++ans;
    room[x][y] = '#';
    for (int i = 0; i < 4; ++i) dfs(x + dx[i], y + dy[i]);
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d\n", &w, &h) != EOF and w != 0) {
        for (int i = 0; i < h; ++i) {
            scanf("%s", &room[i]);
            for (int j = 0; j < w; ++j) {
                if (room[i][j] == '@') {
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        ans = 0;
        dfs(x, y);
        printf("%d\n", ans);
    }

    return 0;
}