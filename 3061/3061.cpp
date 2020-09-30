#include <cstdio>

using namespace std;

const int MAX = 100005;

int T, N, S, acc, last, ans;
int arr[MAX];

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &S);
        ans = MAX;
        for (int i = 0; i < N; ++i) scanf("%d", &arr[i]);
        acc = 0, last = -1;
        for (int i = 0; i < N; ++i) {
            if (arr[i] >= S) {
                ans = 1;
                break;
            } else if (last == -1) {
                acc += arr[i];
                last = i;
            } else {
                acc += arr[i];
                if (acc >= S) {
                    ans = min(i - last + 1, ans);
                    while (acc >= S && last <= i) {
                        acc -= arr[last];
                        ++last;
                        if (acc >= S) ans = min(i - last + 1, ans);
                    }
                    if (last > i) {
                        last = -1;
                        acc = 0;
                    }
                }
            }
        }
        printf("%d\n", ans == MAX ? 0 : ans);
    }

    return 0;
}