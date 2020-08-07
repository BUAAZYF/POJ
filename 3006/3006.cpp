#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 1000005;

int a, d, n;
bool notprime[MAX + 1];

void precomputeprime() {
    notprime[1] = true;
    for (int i = 2; i < MAX; ++i) {
        if (notprime[i]) continue;
        for (int j = i * 2; j < MAX; j += i) notprime[j] = true;
    }
}

int main() {
    precomputeprime();
    while (scanf("%d%d%d", &a, &d, &n) && a) {
        while (n > 0) {
            while (notprime[a]) a += d;
            --n;
            a += d;
        }
        printf("%d\n", a - d);
    }
    return 0;
}