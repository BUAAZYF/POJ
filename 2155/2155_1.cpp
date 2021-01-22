#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 1005;

char op;
int X, N, T, x1, y1, x2, y2;
bool bit[MAX][MAX];

void add_y(int x, int y) {
    for (int j = y; j <= N; j += (j & -j)) bit[x][j] = !bit[x][j];
}

void add_x(int x, int y1, int y2) {
    for (int i = x; i <= N; i += (i & -i)) {
        add_y(i, y1);
        add_y(i, y2 + 1);
    }
}

void range_add(int x1, int x2, int y1, int y2) {
    add_x(x1, y1, y2);
    add_x(x2 + 1, y1, y2);
}

int point_query(int x, int y) {
    bool ans = false;
    for (int i = x; i > 0; i -= (i & -i))
        for (int j = y; j > 0; j -= (j & -j))
            if (bit[i][j]) ans = !ans;
    return ans;
}

int main() {
    scanf("%d", &X);
    while (X--) {
        scanf("%d%d\n", &N, &T);
        memset(bit, false, sizeof(bit));
        while (T--) {
            op = getchar();
            if (op == 'C') {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                range_add(x1, x2, y1, y2);
            } else {
                scanf("%d%d", &x1, &y1);
                printf("%d\n", point_query(x1, y1));
            }
            getchar();
        }
        putchar('\n');
    }

    return 0;
}