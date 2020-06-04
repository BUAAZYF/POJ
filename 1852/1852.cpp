#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    int T, length, n, x, mintime, maxtime;
    scanf("%d", &T);
    while (T-- > 0) {
        mintime = 0;
        maxtime = 0;
        scanf("%d%d", &length, &n);
        while (n-- > 0) {
            scanf("%d", &x);
            mintime = max(mintime, min(length - x, x));
            maxtime = max(maxtime, max(length - x, x));
        }
        printf("%d %d\n", mintime, maxtime);
    }

    return 0;
}