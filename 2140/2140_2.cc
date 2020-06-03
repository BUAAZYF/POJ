#include <cstdio>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    while (n & 1 == 0) n >>= 1;
    int res = 1, d = 3;
    while (d * d <= n) {
        int e = 0;
        while (n % d == 0) {
            n /= d;
            ++e;
        }
        res *= e + 1;
        d += 2;
    }
    if (n > 1) res *= 2;

    printf("%d\n", res);
    return 0;
}