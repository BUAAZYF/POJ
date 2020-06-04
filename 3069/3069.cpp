#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 1005;

int r, n;
int positions[MAX];

int solve() {
    sort(positions, positions + n);
    int left = 0, idx = 0;
    int ans = 0;
    while (left < n) {
        while (idx < n && positions[idx] <= r + positions[left]) ++idx;
        --idx;
        ans += 1;
        left = idx;
        while (left < n && positions[left] <= r + positions[idx]) ++left;
    }
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    while (scanf("%d %d", &r, &n) != EOF and r != -1) {
        for (int i = 0; i < n; ++i) scanf("%d", &positions[i]);
        printf("%d\n", solve());
    }

    return 0;
}