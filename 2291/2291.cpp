#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 1005;

double inline max(int a, int b) {
    return a >= b ? a : b;
}

int t, n, ans;
int rops[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d\n", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &rops[i]);
        sort(rops, rops + n);
        ans = 0;
        for(int i = 0; i < n; ++i) ans = max(ans, rops[i] * ( n - i));
        printf("%d\n", ans);
    }
    return 0;
}