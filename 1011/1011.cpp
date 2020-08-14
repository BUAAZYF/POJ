#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>

using namespace std;

const int MAX = 70;

int n, lensum, ans;
int sticks[MAX];
bool used[MAX];

bool dfs(int curlen, int len, int left, int start) {
    if (left == 0) return true;
    if (curlen == len) curlen = start = 0;
    int i = start;
    while (i < n && (used[i] || curlen + sticks[i] > len)) ++i;
    int last = -1;
    for (int j = i; j < n; ++j) {
        if (used[j] || j >= 1 && sticks[j] == last) continue;
        used[j] = true;
        if (dfs(curlen + sticks[j], len, left - sticks[j], j + 1)) return true;
        used[j] = false;
        if (curlen == 0) return false;
        last = sticks[j];
    }
    return false;
}

bool formsticks(int len) {
    memset(used, false, sizeof(used));
    return dfs(0, len, lensum, 0);
}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        lensum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &sticks[i]);
            lensum += sticks[i];
        }
        sort(sticks, sticks + n, greater<int>());
        ans = 0;
        for (int i = sticks[0]; i <= lensum / 2; ++i) {
            if (lensum % i == 0 && formsticks(i)) {
                ans = i;
                break;
            }
        }
        if (ans == 0) ans = lensum;
        printf("%d\n", ans);
    }

    return 0;
}