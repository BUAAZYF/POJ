#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 50005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int L, N, M, pos[MAX], ans;

int main() {
    while (scanf("%d%d%d", &L, &N, &M) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &pos[i]);
        pos[N++] = L;
        sort(pos, pos + N);
        ans = 0;
        int low = 1, high = L, mid, left, remain, jumpdis;
        while (low <= high) {
            mid = (low + high) >> 1;
            remain = M;
            left = 0;
            for (int i = 0; i < N; ++i) {
                if (pos[i] - left >= mid) left = pos[i];
                else --remain;
            }
            if (remain >= 0) {
                ans = max(ans, mid);
                low = mid + 1;
            } else high = mid - 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}