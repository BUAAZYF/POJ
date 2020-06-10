#include <cstdio>

using namespace std;

const int MAX = 10005;

struct {
    int cost;
    int yogurt;
} plans[MAX];

int n, s, produce_week;
long long ans;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &s);
    ans = 0;
    for (int i = 0; i < n; ++i) scanf("%d%d", &plans[i].cost, &plans[i].yogurt);
    for (int i = 0; i < n; ++i) {
        produce_week = i;
        for (int j = i - 1; j >= 0; --j) {
            if (plans[produce_week].cost > plans[j].cost + (produce_week - j) * s)
                produce_week = j;
        }
        ans += (plans[produce_week].cost + (i - produce_week) * s) * plans[i].yogurt;
    }
    printf("%lld\n", ans);

    return 0;
}