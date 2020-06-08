#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>

using namespace std;

const int MAX = 1005;

int n, d, x, y, ans, cnt, i, pre;
bool cansolve;
pair<double, double> range[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    cnt = 1;
    while (scanf("%d%d", &n, &d) != EOF && n != 0) {
        cansolve = true;
        i = 0;
        for (int k = 0; k < n; ++k) {
            scanf("%d%d", &x, &y);
            if (y > d)
                cansolve = false;
            else if (cansolve && y >= 0) {
                range[i].first = x - sqrt(d * d - pow((double)y, 2));
                range[i].second = x + sqrt(d * d - pow((double)y, 2));
                ++i;
            }
        }
        if (cansolve) {
            n = i;
            sort(range, range + n);
            ans = 1, pre = 0;
            for (i = 1; i < n; ++i) {
                if (range[i].first <= range[pre].second) {
                    pre = range[i].second <= range[pre].second ? i : pre;
                    continue;
                }
                ++ans;
                pre = i;
            }
        }
        printf("Case %d: %d\n", cnt, cansolve ? ans : -1);
        ++cnt;
    }

    return 0;
}