#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 305;
const int TIMELIMIT = MAX * MAX;

int m, x, y, t, nx, ny;
int board[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, 1, -1};

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &m);
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            board[i][j] = TIMELIMIT;
        }
    }
    while (m-- > 0) {
        scanf("%d%d%d", &x, &y, &t);
        board[x][y] = min(board[x][y], t);
        for (int k = 0; k < 4; ++k) {
            nx = x + dx[k];
            ny = y + dy[k];
            if (nx >= 0 && ny >= 0) board[nx][ny] = min(board[nx][ny], t);
        }
    }
    vector<pair<int, int> > cur, nxt;
    int ctime = 0;
    cur.push_back(make_pair(0, 0));
    visited[0][0] = true;
    while (!cur.empty()) {
        nxt.clear();
        for (int i = 0; i < cur.size(); ++i) {
            x = cur[i].first;
            y = cur[i].second;
            if (board[x][y] == TIMELIMIT) {
                printf("%d\n", ctime);
                return 0;
            }
            for (int k = 0; k < 4; ++k) {
                nx = x + dx[k];
                ny = y + dy[k];
                if (nx >= 0 && ny >= 0 && !visited[nx][ny] && board[nx][ny] > ctime + 1) {
                    nxt.push_back(make_pair(nx, ny));
                    visited[nx][ny] = true;
                }
            }
        }
        swap(cur, nxt);
        ++ctime;
    }

    printf("-1\n");

    return 0;
}