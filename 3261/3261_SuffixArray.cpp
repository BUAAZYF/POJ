#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int MAX = 20005;
const int INF = 1000005;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int N, K, ans;
int milk[MAX], sa[MAX], rk[MAX], oldrk[MAX], id[MAX], px[MAX], cnt[INF], ht[MAX];
multiset<int> t;

bool cmp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

int main() {
    while (scanf("%d%d", &N, &K) != EOF) {
        --K;
        memset(cnt, 0, sizeof(cnt));
        int m = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &milk[i]);
            m = max(m, milk[i]);
        }
        for (int i = 1; i <= N; ++i) ++cnt[rk[i] = milk[i]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = N; i >= 1; --i) sa[cnt[rk[i]]--] = i;
        for (int w = 1, i, p; w < N; w <<= 1, m = p) {
            for (p = 0, i = N; i > N - w; --i) id[++p] = i;
            for (i = 1; i <= N; ++i)
                if (sa[i] > w) id[++p] = sa[i] - w;
            memset(cnt, 0, sizeof(cnt));
            for (i = 1; i <= N; ++i) ++cnt[px[i] = rk[id[i]]];
            for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (i = N; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
            memcpy(oldrk, rk, sizeof(rk));
            for (p = 0, i = 1; i <= N; ++i)
                rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
        }
        memset(ht, 0, sizeof(ht));
        for (int i = 1, j = 0; i <= N; ++i) {
            if (j) --j;
            while (milk[i + j] == milk[sa[rk[i] - 1] + j]) ++j;
            ht[rk[i]] = j;
        }
        ans = 0;
        t.clear();
        for (int i = 1; i <= N; ++i) {
            t.insert(ht[i]);
            if (i > K) t.erase(t.find(ht[i - K]));
            ans = max(ans, *t.begin());
        }
        printf("%d\n", ans);
    }

    return 0;
}