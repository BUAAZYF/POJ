#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 20005;

int n, dis[MAX], cnt[MAX];
ll dissum, cntleft, disleft, ans;
struct cow {
    int val, pos;
    bool friend operator<(const cow c1, const cow c2) {
        return c1.val < c2.val;
    }
} cows[MAX];

inline void adddis(int x) {
    for (int i = x; i < MAX; i += (i & -i)) dis[i] += x;
}

inline void addcnt(int x) {
    for (int i = x; i < MAX; i += (i & -i)) ++cnt[i];
}

inline ll query(int* bit, int idx) {
    ll s = 0;
    for (int i = idx; i > 0; i -= (i & -i)) s += bit[i];
    return s;
}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d%d", &cows[i].val, &cows[i].pos);
        fill(cnt, cnt + MAX, 0);
        fill(dis, dis + MAX, 0);
        sort(cows, cows + n);
        ans = dissum = 0;
        for (int i = 0; i < n; ++i) {
            cntleft = query(cnt, cows[i].pos);
            disleft = query(dis, cows[i].pos);
            ans += (cntleft * cows[i].pos - disleft + dissum - disleft - (i - cntleft) * cows[i].pos) * cows[i].val;
            dissum += cows[i].pos;
            addcnt(cows[i].pos);
            adddis(cows[i].pos);
        }
        printf("%lld\n", ans);
    }

    return 0;
}