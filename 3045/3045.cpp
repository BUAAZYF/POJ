#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 50005;

ll inline max(ll a, ll b) {
    return a >= b ? a : b;
}

int n;
ll ans, W;
struct cow {
    ll w, s;
    bool friend operator<(const cow& c1, const cow& c2) {
        return c1.w + c1.s > c2.w + c2.s || c1.w + c1.s == c2.w + c2.s && c1.s > c2.s;
    }
} cows[MAX];

int main() {
    while (scanf("%d", &n) != EOF) {
        W = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld%lld", &cows[i].w, &cows[i].s);
            W += cows[i].w;
        }
        sort(cows, cows + n);
        ans = W - (cows[0].w + cows[0].s);
        W -= cows[0].w;
        for (int i = 1; i < n; ++i) {
            ans = max(ans, W - (cows[i].w + cows[i].s));
            W -= cows[i].w;
        }
        printf("%lld\n", ans);
    }

    return 0;
}