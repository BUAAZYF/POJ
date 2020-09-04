#include <cstdio>

using namespace std;

long L, M, start, end;

int main() {
    while (scanf("%ld%ld", &L, &M) != EOF && L) {
        ++L;
        for (int i = 0; i < M; ++i) {
            scanf("%ld%ld", &start, &end);
            L -= (end - start + 1);
        }
        printf("%ld\n", L);
    }

    return 0;
}