#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100005;
const int MAXP = 25005;
const int MAXS = 30;

int N, K, S, ans_cnt, ans[MAXS];
int s[MAXN + MAXP], bit[MAXS], cnt1[MAXP], cnt2[MAXP], nxt[MAXN + MAXP];

void add(int idx, int v) {
    for (; idx <= S; idx += idx & -idx) bit[idx] += v;
}

int query(int idx) {
    int ret = 0;
    for (; idx > 0; idx -= idx & -idx) ret += bit[idx];
    return ret;
}

void build_bit() {
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < K; ++i) {
        add(s[i], 1);
        cnt1[i] = query(s[i]);
        cnt2[i] = query(s[i] - 1);
    }
}

void prefix_function(int* s, int* nxt, int n) {
    ans_cnt = 0;
    memset(bit, 0, sizeof(bit));
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    int i = -1, j = 0;
    while (j < n) {
        if (i == -1 || (query(s[j]) == cnt1[i] && query(s[j] - 1) == cnt2[i])) {
            nxt[++j] = ++i;
            if (j < n) add(s[j], 1);
        } else {
            for (int k = j - i; k < j - nxt[i]; ++k) add(s[k], -1);
            i = nxt[i];
        }
        if (i == K) {
            ans[ans_cnt++] = j - 2 * K;
            for (int k = j - i; k < j - nxt[i]; ++k) add(s[k], -1);
            i = nxt[i];
        }
    }
}

int main() {
    while (scanf("%d%d%d", &N, &K, &S) != EOF) {
        s[K] = MAXS - 1;
        for (int i = 0; i < N; ++i) scanf("%d", &s[i + K + 1]);
        for (int i = 0; i < K; ++i) scanf("%d", &s[i]);
        build_bit();
        prefix_function(s, nxt, N + K + 1);
        printf("%d\n", ans_cnt);
        for (int i = 0; i < ans_cnt; ++i) printf("%d\n", ans[i]);
    }

    return 0;
}