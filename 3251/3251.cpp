#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 201;

char map[MAX][MAX];
int n, i, j, x, y, p, q, ans;

bool inline check(int a, int b, int c, int d) {
    a >= 0 && b >= 0 && c >= 0 && d >= 0;
}

int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        getchar();
        for (j = 1; j <= n; ++j) scanf("%c", &map[i][j]);
    }
    for (x = 1; x <= n; ++x)
        for (y = 1; y <= n; ++y)
            if (map[x][y] != 'B')
                for (i = n; i >= 1; --i)
                    for (j = n; j >= y; --j) {
                        p = i - x;
                        q = j - y;
                        if (p * p + q * q <= ans) continue;
                        if (map[i][j] == 'B' || ((map[i][j] == map[x][y]) && (map[x][y] != 'J'))) continue;
                        if (check(x - q, i - q, y + p, j + p) && map[x - q][y + p] == 'J' && map[i - q][j + p] == 'J' || check(y - p, j - p, i + q, x + q) && map[x + q][y - p] == 'J' && map[i + q][j - p] == 'J')
                            ans = p * p + q * q;
                    }
    printf("%d", ans);
    return 0;
}