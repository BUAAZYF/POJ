#include <cstdio>
#include <vector>

using namespace std;

int n, add, ans;
vector<int> pre, cur;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    pre.resize(1);
    scanf("%d", &pre[0]);
    for (int i = 2; i <= n; ++i) {
        cur.resize(i);
        for (int j = 0; j < i; ++j) {
            scanf("%d", &cur[j]);
            add = 0;
            if (j - 1 >= 0) add = pre[j - 1];
            if (j < pre.size()) add = max(add, pre[j]);
            cur[j] += add;
        }
        pre = cur;
    }
    ans = 0;
    for (int i = 0; i < n; ++i) ans = max(ans, pre[i]);
    printf("%d\n", ans);

    return 0;
}