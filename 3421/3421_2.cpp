#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 21;
ll fac[N], fm;
int n, sum;

void init_fac(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i;
}

int main() {
    init_fac(N - 1);
    int m = 0;
    while (scanf("%d", &n) != EOF) {
        fm = 1;
        sum = 0;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) {
                int s = 0;
                while (n % i == 0) {
                    ++s;
                    n /= i;
                }
                fm *= fac[s];
                sum += s;
            }
        if (n > 1) ++sum;
        printf("%d %lld\n", sum, fac[sum] / fm);
    }

    return 0;
}