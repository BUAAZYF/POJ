#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100000;
int uni[MAX + 1];
int diff[MAX + 1];

int find(int x) {
    if (x == uni[x])
        return x;
    else
        return uni[x] = find(uni[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    x > y ? uni[x] = y : uni[y] = x;
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    freopen("in.txt", "r", stdin);
    int T, N, M, x, y;
    char op;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d\n", &N, &M);
        for (int i = 1; i <= N; ++i) uni[i] = i;
        memset(diff, 0, (N + 1) * sizeof(int));
        for (int i = 0; i < M; ++i) {
            scanf("%c %d %d\n", &op, &x, &y);
            if (op == 'A') {
                if (N == 2) {
                    if (x != y)
                        printf("In different gangs.\n");
                    else
                        printf("In the same gang.\n");
                } else {
                    if (x == y || same(x, y))
                        printf("In the same gang.\n");
                    else if ((diff[y] != 0 && same(x, diff[y])) || (diff[x] != 0 && same(y, diff[x])))
                        printf("In different gangs.\n");
                    else
                        printf("Not sure yet.\n");
                }
            } else {
                if (diff[x] != 0) merge(diff[x], y);
                if (diff[y] != 0) merge(diff[y], x);
                diff[x] = y;
                diff[y] = x;
            }
        }
    }

    return 0;
}