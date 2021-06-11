#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXV = 105;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int N, M, x, y, p;
double mat[MAXV][MAXV];

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &N) != EOF && N) {
        scanf("%d", &M);
        fill(&mat[0][0], &mat[0][0] + MAXV * MAXV, 0);
        while (M--) {
            scanf("%d%d%d", &x, &y, &p);
            mat[x][y] = mat[y][x] = p / 100.0;
        }
        for (int k = 1; k <= N; ++k)
            for (int i = 1; i <= N; ++i)
                for (int j = 1; j <= N; ++j)
                    mat[i][j] = max(mat[i][j], mat[i][k] * mat[k][j]);
        printf("%.6f percent\n", 100 * mat[1][N]);
        }

    return 0;
}