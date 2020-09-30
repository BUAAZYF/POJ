#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 1005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, x, y, ans;
vector<int> from[MAX], to[MAX];
bool connect[MAX][MAX];

int main() {
    scanf("%d%d", &n, &m);
    memset(connect, false, sizeof(connect));
    while (m--) {
        scanf("%d%d", &x, &y);
        connect[x][y] = true;
        from[y].push_back(x);
        to[x].push_back(y);
    }
    ans = 0;
    for (int k = 1; k <= n; ++k) {
        for (int i = 0; i < from[k].size(); ++i) {
            for (int j = 0; j < to[k].size(); ++j) {
                x = from[k][i];
                y = to[k][j];
                if (!connect[x][y]) {
                    connect[x][y] = true;
                    from[y].push_back(x);
                    to[x].push_back(y);
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j && connect[i][j]) ++ans;
    printf("%d\n", n * (n - 1) / 2 - ans);

    return 0;
}