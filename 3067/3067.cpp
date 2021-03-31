#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;
typedef long long ll;

const int MAX = 1005;
const int MAXN = 1000005;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int T, N, M, K;
ll ans, tree[MAX];
Pr cities[MAXN];

void add(int x, int v) {
    while (x < MAX) {
        tree[x] += v;
        x += x & -x;
    }
}

ll getsum(int x) {
    ll res = 0;
    while (x > 0) {
        res += tree[x];
        x -= x & -x;
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &N, &M, &K);
        for (int i = 0; i < K; ++i) scanf("%d%d", &cities[i].first, &cities[i].second);
        sort(cities, cities + K);
        ans = 0;
        memset(tree, 0, sizeof(tree));
        for (int i = 0; i < K; ++i) {
            ans += i - getsum(cities[i].second);
            add(cities[i].second, 1);
        }
        printf("Test case %d: %lld\n", t, ans);
    }
    return 0;
}