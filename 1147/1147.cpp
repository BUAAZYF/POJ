#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 3005;

int inline min(int x, int y) { return x <= y ? x : y; }

int N, digits[MAX], ranks[MAX], tots[2], ans[MAX];

int main() {
    while (scanf("%d", &N) != EOF) {
        memset(ranks, 0, sizeof(ranks));
        memset(tots, 0, sizeof(tots));
        for (int i = 0; i < N; ++i) {
            scanf("%d", &digits[i]);
            ranks[i] = tots[digits[i]];
            ++tots[digits[i]];
        }
        int idx = 0;
        for (int i = 0; i < N; ++i) {
            ans[N - 1 - i] = digits[idx];
            idx = (digits[idx] == 1 ? tots[0] : 0) + ranks[idx];
        }
        for (int i = 0; i < N; ++i) printf("%d%c", ans[i], i == N - 1 ? '\n' : ' ');
    }

    return 0;
}