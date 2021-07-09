#include <cstdio>

using namespace std;

int N;

int main() {
    while (scanf("%d", &N) != EOF) {
        int ans = 0, cur;
        while (N--) {
            scanf("%d", &cur);
            ans ^= cur;
        }
        printf("%s\n", ans == 0 ? "No" : "Yes");
    }
    return 0;
}