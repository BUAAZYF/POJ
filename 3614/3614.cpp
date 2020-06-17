#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

const int MAXC = 2505;
const int MAXL = 2505;

typedef pair<int, int> Pr;

int C, L, spf, cover, ans;
Pr cows[MAXC];
int lotions[MAXL];

bool inline cmp(const Pr& a, const Pr& b) {
    return a.second < b.second || a.second == b.second && a.first < b.first;
}

int main() {
    scanf("%d%d", &C, &L);
    for (int i = 0; i < C; ++i) scanf("%d%d", &cows[i].first, &cows[i].second);
    sort(cows, cows + C, cmp);
    memset(lotions, 0, L + 1);
    for (int i = 0; i < L; ++i) {
        scanf("%d%d", &spf, &cover);
        lotions[spf] += cover;
    }
    ans = 0;
    for (int i = 0; i < C; ++i) {
        for (int j = cows[i].first; j <= cows[i].second; ++j) {
            if (lotions[j] > 0) {
                ++ans;
                --lotions[j];
                break;
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}