#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 5005;

int t, n, ans, l, w;
Pr sticks[MAX];
bool used[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d%d", &sticks[i].first, &sticks[i].second);
        memset(used, false, sizeof(used));
        ans = 0;
        sort(sticks, sticks + n);
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            used[i] = true;
            l = sticks[i].first;
            w = sticks[i].second;
            for (int j = i + 1; j < n; ++j) {
                if (used[j]) continue;
                if (l <= sticks[j].first && w <= sticks[j].second) {
                    l = sticks[j].first;
                    w = sticks[j].second;
                    used[j] = true;
                }
            }
            ++ans;
        }
        printf("%d\n", ans);
    }

    return 0;
}