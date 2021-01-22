#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 500005;
const int MAXC = 12;

int N, K, nums[MAX], divide_cnt[MAX], bit[MAX], tree[4 * MAX];
char names[MAX][MAXC];

inline void add(int idx) {
    for (int i = idx; i < MAX; i += (i & -i))
        if (divide_cnt[idx] > divide_cnt[bit[i]]) bit[i] = idx;
}

inline int query(int idx) {
    int s = 0;
    for (int i = idx; i > 0; i -= (i & -i))
        if (divide_cnt[s] <= divide_cnt[bit[i]]) s = bit[i];
    return s;
}

void build(int v, int tl, int tr) {
    if (tl == tr) tree[v] = 1;
    else {
        int tm = (tl + tr) >> 1;
        build(v << 1, tl, tm);
        build((v << 1) + 1, tm + 1, tr);
        tree[v] = tree[v << 1] + tree[(v << 1) + 1];
    }
}

void update(int v, int tl, int tr, int pos) {
    if (tl == tr) tree[v] = 0;
    else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm) update(v << 1, tl, tm, pos);
        else update((v << 1) + 1, tm + 1, tr, pos);
        --tree[v];
    }
}

int query_kth(int v, int tl, int tr, int k) {
    if (k > tree[v]) return -1;
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2;
    if (tree[v << 1] >= k) return query_kth(v << 1, tl, tm, k);
    else return query_kth((v << 1) + 1, tm + 1, tr, k - tree[v << 1]);
}

int main() {
    memset(divide_cnt, 0, sizeof(divide_cnt));
    memset(bit, 0, sizeof(bit));
    divide_cnt[1] = 1;
    for (int i = 2; i < MAX; ++i) {
        divide_cnt[i] += 2;
        for (int j = i << 1; j < MAX; j += i) ++divide_cnt[j];
    }
    for (int i = 1; i < MAX; ++i) add(i);
    while (scanf("%d%d", &N, &K) != EOF && N) {
        for (int i = 0; i < N; ++i) scanf("%s %d\n", &names[i], &nums[i]);
        if (N == 1) {
            printf("%s %d\n", names[0], 1);
            continue;
        }
        build(1, 0, N - 1);
        int curpos = K - 1, maxpos = query(N), k = K;
        for (int i = 1, cnt = N - 1; i < maxpos; ++i, --cnt) {
            update(1, 0, N - 1, curpos);
            if (nums[curpos] > 0) k = ((nums[curpos] + k - 1) % cnt + cnt) % cnt;
            else k = ((nums[curpos] + k) % cnt + cnt) % cnt;
            if (k == 0) k = cnt;
            curpos = query_kth(1, 0, N - 1, k);
        }
        printf("%s %d\n", names[curpos], divide_cnt[maxpos]);
    }

    return 0;
}