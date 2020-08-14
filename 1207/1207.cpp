#include <cstdio>
#include <cstring>

using namespace std;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

const int MAX = 10001;
int i, j, ans;
int cycles[MAX];

int calcycles(int x) {
    if (x <= MAX && cycles[x] != 0) return cycles[x];
    int res;
    if (x & 1) res = calcycles(3 * x + 1) + 1;
    else res = calcycles(x >> 1) + 1;
    if (x <= MAX) cycles[x] = res;
    return res;
}

int main() {
    memset(cycles, 0, sizeof(cycles));
    cycles[1] = 1;
    while (scanf("%d%d", &i, &j) != EOF) {
        ans = 0;
        for (int k = min(i, j); k <= max(i, j); ++k) ans = max(ans, calcycles(k));
        printf("%d %d %d\n", i, j, ans);
    }

    return 0;
}