#include <cstdio>

using namespace std;

const int MAX = 10005;

int n, k;
long a[MAX];

int main() {
    while (scanf("%d%d", &n, &k) && n != -1) {
        for(int i = n; i >= 0; --i) scanf("%d", &a[i]);
        for(int i = 0; i <= n - k; ++i) {
            if (a[i] == 0) continue;
            a[i + k] -= a[i];
        }
        if (n == 0 || k == 0) {
            printf("0\n");
            continue;
        }
        if (k > n) {
            for(int i = n; i > 0; --i) printf("%d ", a[i]);
            printf("%d\n", a[0]);
            continue;
        }
        int high = -1;
        for(int i = n - k + 1; i < n; ++i) {
            if (high == -1 && a[i] == 0) continue;
            high = i;
            break;
        }
        printf("%d", a[n]);
        if (high != -1){
            --n;
            while (n >= high) printf(" %d", a[n--]);
        }
        putchar('\n');
    }

    return 0;
}