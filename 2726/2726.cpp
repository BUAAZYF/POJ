#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 10000;

typedef pair<int, int> Pr;

int n, pre, ans;
Pr hotels[MAX];

int main() {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d%d", &hotels[i].first, &hotels[i].second);
        sort(hotels, hotels + n);
        pre = 0;
        ans = 1;
        for (int i = 1; i < n; ++i) {
            if (hotels[i].second < hotels[pre].second) {
                ++ans;
                pre = i;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}