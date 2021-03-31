#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 55;
const int MAXV = 2600;
const int INF = 0x3f3f3f3f;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int T, N, M, nx, ny, Z[MAXN][MAXN];
int match[MAXV], lx[MAXV], ly[MAXV], slack[MAXV], w[MAXV][MAXV];
bool visx[MAXV], visy[MAXV];

bool dfs(int x) {
    visx[x] = true;
    for (int y = 1; y <= ny; ++y) {
        if (visy[y]) continue;
        int delta = lx[x] + ly[y] - w[x][y];
        if (delta == 0) {
            visy[y] = true;
            if (match[y] == -1 || dfs(match[y])) {
                match[y] = x;
                return true;
            }
        } else if (slack[y] > delta) slack[y] = delta;
    }
    return false;
}

int KM() {
    memset(match, -1, sizeof(match));
    memset(ly, false, sizeof(ly));
    for (int i = 1; i <= nx; ++i) lx[i] = -INF;
    for (int i = 1; i <= nx; ++i)
        for (int j = 1; j <= ny; ++j) lx[i] = max(lx[i], w[i][j]);
    for (int x = 1; x <= nx; ++x) {
        for (int i = 1; i <= ny; ++i) slack[i] = INF;
        while (true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if (dfs(x)) break;
            int d = INF;
            for (int i = 1; i <= ny; ++i)
                if (!visy[i] && d > slack[i]) d = slack[i];
            for (int i = 1; i <= nx; ++i)
                if (visx[i]) lx[i] -= d;
            for (int i = 1; i <= ny; ++i)
                if (visy[i]) ly[i] += d;
                else slack[i] -= d;
        }
    }
    int res = 0;
    for (int i = 1; i <= ny; ++i)
        if (match[i] != -1) res += w[match[i]][i];
    return res;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        nx = N, ny = N * M;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= M; ++j) scanf("%d", &Z[i][j]);
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= M; ++j)
                for(int k = 1; k <= N; ++k) w[i][(j - 1) * N + k] = -k * Z[i][j];
        printf("%0.6f\n", double(-KM()) / N);
    }

    return 0;
}