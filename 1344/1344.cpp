#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 205;

int n, mat[MAX][MAX];
bool visited[MAX];

bool check(int a, int b, int &sa) {
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && i != a && i != b) {
            if (flag) {
                sa = mat[a][i] - (mat[a][i] + mat[b][i] - mat[a][b]) / 2;
                flag = false;
            } else if (sa != mat[a][i] - (mat[a][i] + mat[b][i] - mat[a][b]) / 2)
                return false;
        }
    }
    return true;
}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        memset(visited, false, sizeof(visited));
        for (int i = 0; i < n; ++i) {
            mat[i][i] = 0;
            for (int j = i + 1; j < n; ++j) {
                scanf("%d", &mat[i][j]);
                mat[j][i] = mat[i][j];
            }
        }
        int ans = 0, sa, a, b;
        while (true) {
            bool flag = false;
            for (a = 0; a < n; ++a) {
                if (visited[a]) continue;
                for (b = a + 1; b < n; ++b) {
                    if (visited[b]) continue;
                    if (check(a, b, sa)) {
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
            if (!flag) break;
            ans += mat[a][b];
            visited[a] = visited[b] = true;
            for (int j = 0; j < n; ++j)
                if (!visited[j]) mat[j][n] = mat[n][j] = mat[j][a] - sa;
            ++n;
        }
        printf("%d\n", ans);
    }
    return 0;
}