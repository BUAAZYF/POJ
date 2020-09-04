#include <cstdio>
#include <map>

using namespace std;

const int MAX = 31250000;

int a[5], powtable[105], cur, ans;
short cnt[MAX * 2 + 1];

void init() {
    for (int i = 0; i <= 50; ++i) {
        powtable[50 + i] = i * i * i;
        powtable[50 - i] = -powtable[50 + i];
    }
}

int main() {
    init();
    for (int i = 0; i < 5; ++i) scanf("%d", &a[i]);
    for (int i = -50; i <= 50; ++i) {
        if (i == 0) continue;
        for (int j = -50; j <= 50; ++j) {
            if (j == 0) continue;
            for (int k = -50; k <= 50; ++k) {
                if (k == 0) continue;
                cur = a[0] * powtable[i + 50] + a[1] * powtable[j + 50]  + a[2] * powtable[k + 50];
                ++cnt[cur + MAX];
            }
        }
    }
    ans = 0;
    for (int i = -50; i <= 50; ++i) {
        if (i == 0) continue;
        for (int j = -50; j <= 50; ++j) {
            if (j == 0) continue;
            cur = -a[3] * powtable[i + 50] - a[4] * powtable[j + 50];
            ans += cnt[cur + MAX];
        }
    }
    printf("%d\n", ans);

    return 0;
}